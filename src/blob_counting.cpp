/*************************************************************************
 * SCAMP Vision Chip Development System Library
 *------------------------------------------------------------------------
 * Copyright (c) 2020 The University of Manchester. All Rights Reserved.
 *
 *************************************************************************/
/*
 * Scamp5d M0 Example 9 - Blob Counting
 *
 * This example draws some circles on a DREG image, then read the bounding
 * box of each of them. This also demonstrate how to setup the GUI display
 * to change bounding box colors
 */

#include <scamp5.hpp>

using namespace SCAMP5_PE;


#define DEFAULT_FRAMERATE	60


int main(){
	vs_random rng;

	// Initialization
	vs_init();

	// Setup Host GUI

	vs_gui_set_info(VS_M0_PROJECT_INFO_STRING);

	// create a display style allowing different colors for different vector data
	VS_GUI_DISPLAY_STYLE(style_plot,R"JSON(
	{
		"vector_palette": "target_trail_groups",
		"vector_palette_groups": 8
	}
	)JSON");

    auto display_1 = vs_gui_add_display("input",0,0,1,style_plot);
    auto display_2 = vs_gui_add_display("result",0,1,1,style_plot);

    static volatile int readout_mode = 2;
    vs_gui_add_slider_latched("readout: ",0,4,readout_mode,&readout_mode);

    static volatile int ball_x = 25;
    static volatile int ball_y = 25;
    vs_gui_add_slider("ball_x: ",0,255,ball_x,&ball_x);
    vs_gui_add_slider("ball_y: ",0,255,ball_y,&ball_y);

	// Frame Loop
    while(1){
    	// sync with frame trigger timing and process interaction with host
    	vs_frame_loop_control();

		/*
		 * Draw Some Filled Circle
		 */
		uint8_t coords[4][2] = {
				{ball_y,ball_x},
				{85,73},
				{199,52},
				{130,222},
		};

		scamp5_draw_begin(R6);
		for(int i=0;i<4;i++){
			scamp5_draw_circle(coords[i][0],coords[i][1],15 + i*3);
		}
		scamp5_draw_negate();// negate b/w
		scamp5_draw_end();

		scamp5_draw_begin(R7);
		for(int i=0;i<4;i++){
			scamp5_draw_point(coords[i][0],coords[i][1]);
		}
		scamp5_draw_end();

		scamp5_flood(R7,R6,0);

        scamp5_kernel_begin();
        	MOV(R5,R7);
        	MOV(R6,R7);
		scamp5_kernel_end();

		if(readout_mode>=1){
			scamp5_output_image(R5,display_1);
		}


		/*
		 * Blob Extraction Algorithm
		 */

		size_t count = 0;
		uint8_t event_coords[8][2];

		while(scamp5_global_or(R6)){

			// get first '1' in R6 image
			scamp5_scan_events(R6,event_coords[count],1);

			// put the pixel into R7 and flood using R6 as mask
			scamp5_load_point(R7,event_coords[count][1],event_coords[count][0]);
			scamp5_flood(R7,R6,0);

			// R7 now contain the found blob only.

			// remove the blob from R6
	        scamp5_kernel_begin();
	        	CLR_IF(R6,R7);
			scamp5_kernel_end();

			if(readout_mode>=2){
				scamp5_output_boundingbox(R7,display_1);
			}

			if(readout_mode>=3){
				if((vs_loop_counter_get()/30)%4==count){
					scamp5_output_image(R7,display_2);
				}
			}

			count++;
			if(count>=8){
				break;
			}
		}

    }

	return 0;
}
