/*************************************************************************
 * SCAMP Vision Chip Development System Library
 *------------------------------------------------------------------------
 * Copyright (c) 2020 The University of Manchester. All Rights Reserved.
 *
 *************************************************************************/

/*!

\file

\ingroup VS_SCAMP5_MODULE

\author Jianing Chen

*/

#ifndef SCAMP5_KERNEL_API_MACRO_DIGITAL_HPP
#define SCAMP5_KERNEL_API_MACRO_DIGITAL_HPP


#include "scamp5_kernel_api.hpp"

#ifndef _DOXYGEN_
namespace scamp5_kernel_api{
#endif

using namespace SCAMP5_PE;


/*!
 * @brief 	logic operation Rl := NOT Rl
 *
 */
inline void NOT( DREG Rl ){

	scamp5_kernel::top()->icw().bit.clk0 = 1;
	scamp5_kernel::top()->icw().bit.plrb = 1;
	scamp5_kernel::top()->icw().bit.nbit = 1;
	scamp5_kernel::top()->icw().set_RR(Rl);
    scamp5_kernel::top()->push();

	scamp5_kernel::top()->icw().bit.clk0 = 1;
	scamp5_kernel::top()->icw().bit.nbit = 1;
	scamp5_kernel::top()->icw().set_LR(Rl);
    scamp5_kernel::top()->push();

}


/*!
 * @brief 	logic operation Rl := Rl OR Rx
 *
 */
inline void OR( DREG Rl, DSRC Rx ){

	scamp5_kernel::top()->icw().bit.clk0 = 1;
	scamp5_kernel::top()->icw().bit.plrb = 1;
	scamp5_kernel::top()->icw().bit.bit = 1;
	scamp5_kernel::top()->icw().bit.bitmode = 1;
	scamp5_kernel::top()->icw().set_RR(Rl);
	scamp5_kernel::top()->icw().set_RR(Rx);
    scamp5_kernel::top()->push();

	scamp5_kernel::top()->icw().bit.clk0 = 1;
	scamp5_kernel::top()->icw().bit.bit = 1;
	scamp5_kernel::top()->icw().bit.bitmode = 1;
	scamp5_kernel::top()->icw().set_LR(Rl);
    scamp5_kernel::top()->push();

}


/*!
 * @brief 	logic operation Rl := Rl NOR Rx
 *
 */
inline void NOR( DREG Rl, DSRC Rx ){

	scamp5_kernel::top()->icw().bit.clk0 = 1;
	scamp5_kernel::top()->icw().bit.plrb = 1;
	scamp5_kernel::top()->icw().bit.nbit = 1;
	scamp5_kernel::top()->icw().set_RR(Rl);
	scamp5_kernel::top()->icw().set_RR(Rx);
    scamp5_kernel::top()->push();

	scamp5_kernel::top()->icw().bit.clk0 = 1;
	scamp5_kernel::top()->icw().bit.nbit = 1;
	scamp5_kernel::top()->icw().set_LR(Rl);
    scamp5_kernel::top()->push();

}


/*!
 * @brief 	digital neighbour OR, Ra := Rx_dir1 OR Rx_dir2 ...; (also modify R1 R2 R3 R4).
 *
 */
inline void DNEWS( DREG Ra, DSRC Rx, const int dir, const bool boundary = 0 ){

	scamp5_kernel::top()->push_icw().CLR(R1,R2,R3,R4);

    // set multiple dreg (upto 4) can be done via one icw
    if(dir&south){
    	scamp5_kernel::top()->icw().SET(R1);
    }
    if(dir&west){
    	scamp5_kernel::top()->icw().SET(R2);
    }
    if(dir&north){
    	scamp5_kernel::top()->icw().SET(R3);
    }
    if(dir&east){
    	scamp5_kernel::top()->icw().SET(R4);
    }
    scamp5_kernel::top()->push();

    if(boundary){
    	scamp5_kernel::top()->push_icw().DNEWS1(Ra,Rx);
    }else{
    	scamp5_kernel::top()->push_icw().DNEWS0(Ra,Rx);
    }
}


/*!
 * @brief 	async-propagation on R12, masked by R0
 *
 */
inline void PROP0(){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().PROP_R();
    scamp5_kernel::top()->push_icw().PROP_0();
}


/*!
 * @brief 	async-propagation on R12, masked by R0 when bourndaries are considered '1'
 *
 */
inline void PROP1(){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().PROP_R();
    scamp5_kernel::top()->push_icw().PROP_1();
}


/*!
 * @brief 	Ra := Rx AND Ry; R0 = NOT Ry; R12 = NOT RX
 *
 */
inline void AND( DREG Ra, DSRC Rx, DSRC Ry ){
    scamp5_kernel::top()->push_icw().SET(R0);
    scamp5_kernel::top()->push_icw().NOT(R12,Rx);
    scamp5_kernel::top()->push_icw().NOT(R0,Ry);
    scamp5_kernel::top()->push_icw().NOR(Ra,R0,R12);
}


/*!
 * @brief 	Ra := Rx NAND Ry; R0 = NOT Ry; R12 = NOT RX
 *
 */
inline void NAND( DREG Ra, DSRC Rx, DSRC Ry ){
    scamp5_kernel::top()->push_icw().SET(R0);
    scamp5_kernel::top()->push_icw().NOT(R12,Rx);
    scamp5_kernel::top()->push_icw().NOT(R0,Ry);
    scamp5_kernel::top()->push_icw().OR(Ra,R0,R12);
}


/*!
 * @brief 	Ra := Rb AND Rx; Rb := NOT Rx; R0 = NOT Rb
 *
 */
inline void ANDX( DREG Ra, DREG Rb, DSRC Rx ){
    scamp5_kernel::top()->push_icw().NOT(R0,Rb);
    scamp5_kernel::top()->push_icw().NOT(Rb,Rx);
    scamp5_kernel::top()->push_icw().NOR(Ra,R0,Rb);
}


/*!
 * @brief 	Ra := Rx NAND Ry; Rb := NOT Rx; R0 = NOT Rb
 *
 */
inline void NANDX( DREG Ra, DREG Rb, DSRC Rx ){
    scamp5_kernel::top()->push_icw().NOT(R0,Rb);
    scamp5_kernel::top()->push_icw().NOT(Rb,Rx);
    scamp5_kernel::top()->push_icw().OR(Ra,R0,Rb);
}


/*!
 * @brief 	Rl := Rx IMP Ry
 *
 * Truth Table:
 * 	Rx	Ry	  Rl
 * 	0   0	  1
 * 	0   1	  0
 * 	1   0	  1
 * 	1   1	  1
 *
 */
inline void IMP( DREG Rl, DSRC Rx, DSRC Ry ){
    scamp5_kernel::top()->push_icw().NOT(R0,Ry);
    scamp5_kernel::top()->push_icw().OR(Rl,Rx,R0);
}


/*!
 * @brief 	Rl := Rx NIMP Ry
 *
 * Truth Table:
 * 	Rx	Ry	  Rl
 * 	0   0	  0
 * 	0   1	  1
 * 	1   0	  0
 * 	1   1	  0
 *
 */
inline void NIMP( DREG Rl, DSRC Rx, DSRC Ry ){
    scamp5_kernel::top()->push_icw().NOT(R0,Ry);
    scamp5_kernel::top()->push_icw().NOR(Rl,Rx,R0);
}


/*!
 * @brief 	Rl := Rx XOR Ry, Rx := *
 *
 */
inline void XORX( DREG Rl, DREG Rx, DSRC Ry ){
    scamp5_kernel::top()->push_icw().NOT(R0,Ry);
    scamp5_kernel::top()->push_icw().NOR(Rl,Rx,R0);
    scamp5_kernel::top()->push_icw().NOT(R0,Rx);
    scamp5_kernel::top()->push_icw().NOR(Rx,Ry,R0);
    OR(Rl,Rx);
}


/*!
 * @brief 	Rl := Ry IF Rx = 1, Rl := Rz IF Rx = 0.
 */
inline void MUX( DREG Rl, DSRC Rx, DSRC Ry, DSRC Rz ){
    scamp5_kernel::top()->push_icw().SET(R0);
    scamp5_kernel::top()->push_icw().MOV(R12,Rz);
    scamp5_kernel::top()->push_icw().MOV(R0,Rx);
    scamp5_kernel::top()->push_icw().MOV(R12,Ry);
    scamp5_kernel::top()->push_icw().MOV(Rl,R12);
}


/*!
 * @brief 	Rl := 0 IF Rx = 1, Rl := Rl IF Rx = 0.
 */
inline void CLR_IF( DREG Rl, DSRC Rx ){
	scamp5_kernel::top()->push_icw().NOT(R0,Rl);
	scamp5_kernel::top()->push_icw().NOR(Rl,R0,Rx);
}


/*!
 * @brief 	refresh a DREG to prevent decay after a long time (e.g. > 1.5 seconds) without any operations
 */
inline void REFRESH( DREG Rl ){
    scamp5_kernel::top()->push_icw().REFRESH_R(Rl);
    scamp5_kernel::top()->push_icw().REFRESH_L(Rl);
}

#ifndef _DOXYGEN_
};
#endif

#endif
