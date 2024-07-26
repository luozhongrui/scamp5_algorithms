/*************************************************************************
 * SCAMP Vision Chip Development System Library
 *------------------------------------------------------------------------
 * Copyright (c) 2020 The University of Manchester. All Rights Reserved.
 *
 *************************************************************************/
/*
 * Scamp5d M0 Example 3 - Sobel Edge Detection
 *
 */

#include <scamp5.hpp>

using namespace SCAMP5_PE;


int main(){

	// Initialization
	vs_init();

	// Setup Host GUI
    auto display_1 = vs_gui_add_display("half-scale",0,0);
    auto display_2 = vs_gui_add_display("sobel edge",0,1);
    auto display_3 = vs_gui_add_display("laplacian edge",1,0);

	vs_gui_set_info(VS_M0_PROJECT_INFO_STRING);

	// Frame Loop
    while(1){
        vs_frame_loop_control();

        // capture a half-scale image in C
        scamp5_kernel_begin();
			get_image(C);
		scamp5_kernel_end();


		// Sobel Edge Algorithm (need 4 AREG)
        scamp5_kernel_begin();

            // vertical edge
            movx(A,C,north);
            movx(B,C,south);
            add(A,A,B);
            add(A,A,C);
            add(A,A,C);

            movx(B,A,east);
            movx(A,A,west);

            sub(B,B,A);// B = B - A
            abs(D,B);// D is the vertical edge

            // horizontal edge
            movx(A,C,east);
            movx(B,C,west);
            add(A,A,B);
            add(A,A,C);
            add(A,A,C);

            movx(B,A,south);
            movx(A,A,north);

            sub(B,B,A);// B = B - A
            abs(A,B);// A is the horizontal edge

            add(E,A,D);// put final result in E

		scamp5_kernel_end();


        // Laplacian Edge Algorthm (need 3 AREG)
        scamp5_kernel_begin();

			res(A);// A = 0

			subx(B,C,north,C);// B = C_north - C
			add(A,A,B);// A = A + B

			subx(B,C,east,C);// B = C_east - C
			add(A,A,B);// A = A + B

			subx(B,C,west,C);// B = C_west - C
			add(A,A,B);// A = A + B

			subx(B,C,south,C);// B = C_south - C
			add(A,A,B);// A = A + B

			abs(F,A);// F = |A| (final result)

		scamp5_kernel_end();


		// readout register image and send to host GUI for display
		if(vs_gui_is_on()){
			scamp5_output_image(C,display_1);
			scamp5_output_image(E,display_2);
			scamp5_output_image(F,display_3);
		}

    }

	return 0;
}
