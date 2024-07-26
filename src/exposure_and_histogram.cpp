/*************************************************************************
 * SCAMP Vision Chip Development System Library
 *------------------------------------------------------------------------
 * Copyright (c) 2020 The University of Manchester. All Rights Reserved.
 *
 *************************************************************************/
/*
 * Scamp5d M0 Example 7 - Exposure and Histogram
 *
 * This program implements a camera-like utility, where histogram display and
 * one-shot frame capture can be done. The one-shot frame capture can be
 * useful when the imaging quality under high frame rate needs to be inspected
 * since the continuous analog readout cannot reach a frame rate over 60 FPS.
 *
 */

#include <scamp5.hpp>

using namespace SCAMP5_PE;


#define DEFAULT_FRAMERATE	60


// Global Variables

std::array<int16_t,16> histogram;

int framerate;
int rps;
vs_stopwatch rps_timer;
volatile int readout_mode;
volatile int threshold;
volatile int show_exposure;
volatile int show_histogram;
volatile int one_shot;


int main(){

    /*
     * M0 Initialization
     */

	vs_init();


    /*
     * Setup Host User GUI
     */

	vs_gui_set_info(VS_M0_PROJECT_INFO_STRING);

    auto display_1 = vs_gui_add_display("aout",0,0);
    auto display_2 = vs_gui_add_display("dout",1,0);
    auto display_3 = vs_gui_add_display("one shot",0,1);
    auto display_4 = vs_gui_add_display("histogram",1,1);

    // setup graph over displays
    auto floor = vs_scamp5_get_parameter(SCAMP5_GLOBAL_SUM_64_FLOOR);
    auto ceiling = floor + vs_scamp5_get_parameter(SCAMP5_GLOBAL_SUM_64_SPAN);
    vs_gui_set_scope(display_1,floor,ceiling,256);// set up a scope-style graph for "display_1"
    vs_gui_set_barplot(display_4,-250,2500,6);// set up a barplot graph for "display_4"

	auto slider_readout = vs_gui_add_slider_latched("readout: ",0,3,0);
	auto slider_rps = vs_gui_add_slider_latched("readout rate: ",0,300,0);
    vs_gui_add_slider("threshold: ",-128,127,-30,&threshold);
    vs_gui_add_switch("plot exposure: ",false,&show_exposure);
    vs_gui_add_switch("plot histogram: ",false,&show_histogram);
    auto button_shot = vs_gui_add_button("one shot");

    // callback functions for the GUI items

    one_shot = 0;
    vs_on_gui_update(button_shot,[&](int32_t new_value){
    	one_shot = 1;
    });

    vs_on_gui_update(slider_rps,[&](int32_t new_value){
    	if(new_value > 0){
        	rps = new_value;
    	}else{
    		rps = 1000000;
            vs_post_text("continuous readout mode\n");
    	}
    });

    vs_on_gui_update(slider_readout,[&](int32_t new_value){
    	readout_mode = new_value;
		vs_post_text("readout mode: %d\n",readout_mode);
    });

	// customize the callback function for the frame rate slider on the GUI
    vs_on_gui_update(VS_GUI_FRAME_RATE,[&](int32_t new_value){
        framerate = new_value;
        if(framerate > 0){
            vs_frame_trigger_set(1,framerate);
            vs_enable_frame_trigger();
            vs_post_text("frame trigger: 1/%d\n",(int)framerate);
        }else{
            vs_disable_frame_trigger();
            vs_post_text("frame trigger disabled\n");
        }
    });

    vs_on_host_connect([&](){
        vs_gui_move_slider(VS_GUI_FRAME_RATE,DEFAULT_FRAMERATE);
        vs_led_on(VS_LED_2);
    });

    vs_on_host_disconnect([&](){
    	readout_mode = 0;
    	show_histogram = 0;
        vs_led_off(VS_LED_2);
    });


    /*
     * Frame Loop
     */

    // use VS_FRAME_TRIGGER_CONST_PIX to maintain PIX integration time same as frame-rate
    vs_configure_frame_trigger(VS_FRAME_TRIGGER_CONST_PIX,DEFAULT_FRAMERATE);

    rps_timer.reset();

    while(1){
    	// sync with frame trigger timing and process interaction with host
    	vs_frame_loop_control();

        // capture image with a gain
        int gain = vs_gui_read_slider(VS_GUI_FRAME_GAIN);
        scamp5_get_image(C,B,gain);

        // threshold image
        scamp5_in(E,threshold);
        scamp5_kernel_begin();
			where(C);
            MOV(R6,FLAG);
			all();
            sub(A,C,E);
            where(A);
            MOV(R5,FLAG);
            all();
		scamp5_kernel_end();

        // show exposure level of the entire image in a scope
		if(show_exposure){
			int32_t sum = scamp5_global_sum_64(C);
			vs_post_set_channel(display_1);
			vs_post_int32(&sum,1,1);
		}

        // histogram

		scamp5_kernel_begin();
			CLR(R2,R3,R4);
		scamp5_kernel_end();

		vs_stopwatch stopwatch;
		stopwatch.reset();
		// compute a 16-level histogram
		for(int i=0;i<16;i++){
			int level = 116 - i*16;
			if(level > -120){
				scamp5_load_in(level);// IN = level
				scamp5_kernel_begin();
					sub(A,C,IN);// A = C - IN
					where(A);
					MOV(R2,FLAG);// R2 is all pixels above the level
					all();
					XORX(R4,R3,R2);// R4 = R3 XOR R2, R3 = *
					MOV(R3,R2);// R3 = R2
				scamp5_kernel_end();
			}else{
				scamp5_kernel_begin();
					SET(R2);// last level is essentially all the remaining pixels
					XORX(R4,R3,R2);// R4 = R3 XOR R2, R3 = *
				scamp5_kernel_end();
			}
			histogram[15 - i] = scamp5_global_count(R4,A,1);// gives a value in [0,4095]
		}
		auto t_alg = stopwatch.get_usec();

		if(show_histogram){
			vs_post_set_channel(display_4);
			vs_post_int16(histogram.data(),1,histogram.size());
        }

        /*
         * One-shot readout can be used to display a image captured under high frame rate (e.g. higher than 100 FPS).
         */
        if(one_shot){
        	one_shot = 0;
        	scamp5_output_image(C,display_3);
        	scamp5_output_image(R5,display_2);
        	int gain_x = int(1)<<(gain - 1);
    		vs_post_text("[%d] shot @ 1/%d, %dx, t_alg=%d usec\n",(int)vs_loop_counter_get(),(int)framerate,(int)gain_x,(int)t_alg);
        }

		// stream images at the given readout rate if required
		if(rps_timer.get_usec()*rps > 1000000){
			rps_timer.reset();
	        if(readout_mode & 0x01){
	        	scamp5_output_image(R5,display_2);
	        }
	        if(readout_mode & 0x02){
	        	scamp5_output_image(C,display_1);
	        }
		}

    }

    return 0;
}

