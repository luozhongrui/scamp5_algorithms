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

#ifndef SCAMP5_KERNEL_API_MACRO_HPP
#define SCAMP5_KERNEL_API_MACRO_HPP


#include "scamp5_kernel_api.hpp"


#ifndef _DOXYGEN_
namespace scamp5_kernel_api{
#endif

using namespace SCAMP5_PE;


// Zero
//------------------------------------------------------------------------------

/*!
 * @brief 	a := 0
 *
 */
inline void res(AREG a){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus(SCAMP5_MACRO_T_AREG);
    scamp5_kernel::top()->push_icw().bus(a,SCAMP5_MACRO_T_AREG);
}

/*!
 * @brief 	a := 0, b := 0
 *
 */
inline void res(AREG a,AREG b){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus(SCAMP5_MACRO_T_AREG);
    scamp5_kernel::top()->push_icw().bus(a,SCAMP5_MACRO_T_AREG);
    scamp5_kernel::top()->push_icw().bus(b,SCAMP5_MACRO_T_AREG);
}



// Basic Arithmetics
//------------------------------------------------------------------------------

/*!
 * @brief	y := x0
 *
 */
inline void mov( AREG y, ASRC x0 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus(SCAMP5_MACRO_T_AREG,x0);
    scamp5_kernel::top()->push_icw().bus(y,SCAMP5_MACRO_T_AREG);
}

/*!
 * @brief	y := x0 + x1
 *
 */
inline void add( AREG y, ASRC x0, ASRC x1 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus(SCAMP5_MACRO_T_AREG,x0,x1);
    scamp5_kernel::top()->push_icw().bus(y,SCAMP5_MACRO_T_AREG);
}

/*!
 * @brief	y := x0 + x1 + x2
 *
 */
inline void add( AREG y, ASRC x0, ASRC x1, ASRC x2 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus(SCAMP5_MACRO_T_AREG,x0,x1,x2);
    scamp5_kernel::top()->push_icw().bus(y,SCAMP5_MACRO_T_AREG);
}

/*!
 * @brief	y := x0 - x1
 *
 */
inline void sub( AREG y, ASRC x0, ASRC x1 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus(SCAMP5_MACRO_T_AREG,x0);
    scamp5_kernel::top()->push_icw().bus(y,SCAMP5_MACRO_T_AREG,x1);
}

/*!
 * @brief	y := -x0
 *
 */
inline void neg( AREG y, ASRC x0 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus(SCAMP5_MACRO_T_AREG);
    scamp5_kernel::top()->push_icw().bus(y,SCAMP5_MACRO_T_AREG,x0);
}

/*!
 * @brief	y := |x0|
 *
 */
inline void abs( AREG y, ASRC x0 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus(SCAMP5_MACRO_T_AREG);
    scamp5_kernel::top()->push_icw().bus(y,SCAMP5_MACRO_T_AREG,x0);
    scamp5_kernel::top()->push_icw().bus(SCAMP5_MACRO_T_AREG,x0);
    scamp5_kernel::top()->push_icw().where(x0);
    scamp5_kernel::top()->push_icw().bus(y,SCAMP5_MACRO_T_AREG);
    scamp5_kernel::top()->push_icw().all();
}


// Division
//------------------------------------------------------------------------------

/*!
 * @brief	y0 := 0.5*x0 + error
 *
 */
inline void divq( AREG y0, ASRC x0 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus2(y0,SCAMP5_MACRO_T_AREG,x0);
    scamp5_kernel::top()->push_icw().bus(y0,SCAMP5_MACRO_T_AREG);
}


/*!
 * @brief	y0 := 0.5*y2; y1 := -0.5*y2 + error, y2 := y2 + error
 *
 */
inline void div( AREG y0, AREG y1, AREG y2 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus2(y0,y1,y2);
    scamp5_kernel::top()->push_icw().bus(SCAMP5_MACRO_T_AREG,y2,y1);
    scamp5_kernel::top()->push_icw().bus(y2,SCAMP5_MACRO_T_AREG,y0);
    scamp5_kernel::top()->push_icw().bus2(y0,y1,y2);
    scamp5_kernel::top()->push_icw().bus(y0,y1);
}


/*!
 * @brief	y0 := 0.5*x0; y1 := -0.5*x0 + error, y2 := x0 + error
 *
 */
inline void div( AREG y0, AREG y1, AREG y2, ASRC x0 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus2(y0,y1,x0);
    scamp5_kernel::top()->push_icw().bus(SCAMP5_MACRO_T_AREG,x0,y1);
    scamp5_kernel::top()->push_icw().bus(y2,SCAMP5_MACRO_T_AREG,y0);
    scamp5_kernel::top()->push_icw().bus2(y0,y1,y2);
    scamp5_kernel::top()->push_icw().bus(y0,y1);
}


/*!
 * @brief	y0 := 0.5*y0; y1 := -0.5*y0 + error, y2 := -0.5*y0 + error
 *
 */
inline void diva( AREG y0, AREG y1, AREG y2 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus2(y1,y2,y0);
    scamp5_kernel::top()->push_icw().bus(SCAMP5_MACRO_T_AREG,y1,y0);
    scamp5_kernel::top()->push_icw().bus(y0,SCAMP5_MACRO_T_AREG,y2);
    scamp5_kernel::top()->push_icw().bus2(y1,y2,y0);
    scamp5_kernel::top()->push_icw().bus(y0,y1);
}



// Neighour Access
//------------------------------------------------------------------------------

/*!
 * @brief	y := x0_dir (note: naming of this function is deprecated)
 *
 */
inline void mov( AREG y, ASRC x0, const news_t dir ){
    scamp5_kernel::top()->highspeed = false;
    switch(dir){
    case east: scamp5_kernel::top()->push_icw().bus(XW,x0); break;
    case west: scamp5_kernel::top()->push_icw().bus(XE,x0); break;
    case north: scamp5_kernel::top()->push_icw().bus(XS,x0); break;
    case south: scamp5_kernel::top()->push_icw().bus(XN,x0); break;
    default: break;
    }
    scamp5_kernel::top()->push_icw().bus(y,NEWS);
}

/*!
 * @brief	y := x0_dir - x1 (note: naming of this function is deprecated)
 *
 */
inline void sub( AREG y, ASRC x0, const news_t dir, ASRC x1 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus(NEWS,x0);
    switch(dir){
    case east: scamp5_kernel::top()->push_icw().bus(y,XE,x1); break;
    case west: scamp5_kernel::top()->push_icw().bus(y,XW,x1); break;
    case north: scamp5_kernel::top()->push_icw().bus(y,XN,x1); break;
    case south: scamp5_kernel::top()->push_icw().bus(y,XS,x1); break;
    default: break;
    }
}


/*!
 * @brief	y := x0_dir
 *
 */

inline void movx( AREG y, ASRC x0, const news_t dir ){
    scamp5_kernel::top()->highspeed = false;
    switch(dir){
    case east: scamp5_kernel::top()->push_icw().bus(XW,x0); break;
    case west: scamp5_kernel::top()->push_icw().bus(XE,x0); break;
    case north: scamp5_kernel::top()->push_icw().bus(XS,x0); break;
    case south: scamp5_kernel::top()->push_icw().bus(XN,x0); break;
    default: break;
    }
    scamp5_kernel::top()->push_icw().bus(y,NEWS);
}


/*!
 * @brief	y := x0_dir_dir (note: this only works when FLAG is "all")
 *
 */

inline void mov2x( AREG y, ASRC x0, const news_t dir, const news_t dir2 ){
    scamp5_kernel::top()->highspeed = false;
    switch(dir){
    case east: scamp5_kernel::top()->push_icw().bus(XW,x0); break;
    case west: scamp5_kernel::top()->push_icw().bus(XE,x0); break;
    case north: scamp5_kernel::top()->push_icw().bus(XS,x0); break;
    case south: scamp5_kernel::top()->push_icw().bus(XN,x0); break;
    default: break;
    }
    switch(dir2){
    case east: scamp5_kernel::top()->push_icw().bus(y,XE); break;
    case west: scamp5_kernel::top()->push_icw().bus(y,XW); break;
    case north: scamp5_kernel::top()->push_icw().bus(y,XN); break;
    case south: scamp5_kernel::top()->push_icw().bus(y,XS); break;
    default: break;
    }
}


/*!
 * @brief	y := x0_dir + x1_dir
 *
 */
inline void addx( AREG y, ASRC x0, ASRC x1, const news_t dir ){
    scamp5_kernel::top()->highspeed = false;
    switch(dir){
    case east: scamp5_kernel::top()->push_icw().bus(XW,x0,x1); break;
    case west: scamp5_kernel::top()->push_icw().bus(XE,x0,x1); break;
    case north: scamp5_kernel::top()->push_icw().bus(XS,x0,x1); break;
    case south: scamp5_kernel::top()->push_icw().bus(XN,x0,x1); break;
    default: break;
    }
    scamp5_kernel::top()->push_icw().bus(y,NEWS);
}


/*!
 * @brief	y := x0_dir_dir2 + x1_dir_dir2
 *
 */
inline void add2x( AREG y, ASRC x0, ASRC x1, const news_t dir, const news_t dir2 ){
    scamp5_kernel::top()->highspeed = false;
    switch(dir){
    case east: scamp5_kernel::top()->push_icw().bus(XW,x0,x1); break;
    case west: scamp5_kernel::top()->push_icw().bus(XE,x0,x1); break;
    case north: scamp5_kernel::top()->push_icw().bus(XS,x0,x1); break;
    case south: scamp5_kernel::top()->push_icw().bus(XN,x0,x1); break;
    default: break;
    }
    switch(dir2){
    case east: scamp5_kernel::top()->push_icw().bus(y,XE); break;
    case west: scamp5_kernel::top()->push_icw().bus(y,XW); break;
    case north: scamp5_kernel::top()->push_icw().bus(y,XN); break;
    case south: scamp5_kernel::top()->push_icw().bus(y,XS); break;
    default: break;
    }
}


/*!
 * @brief	y := x0_dir - x1
 *
 */
inline void subx( AREG y, ASRC x0, const news_t dir, ASRC x1 ){
    scamp5_kernel::top()->highspeed = false;
    switch(dir){
    case east: scamp5_kernel::top()->push_icw().bus(XW,x0); break;
    case west: scamp5_kernel::top()->push_icw().bus(XE,x0); break;
    case north: scamp5_kernel::top()->push_icw().bus(XS,x0); break;
    case south: scamp5_kernel::top()->push_icw().bus(XN,x0); break;
    default: break;
    }
    scamp5_kernel::top()->push_icw().bus(y,NEWS,x1);
}


/*!
 * @brief	y := x0_dir_dir2 - x1
 *
 */
inline void sub2x( AREG y, ASRC x0, const news_t dir, const news_t dir2, ASRC x1 ){
    scamp5_kernel::top()->highspeed = false;
    switch(dir){
    case east: scamp5_kernel::top()->push_icw().bus(XW,x0); break;
    case west: scamp5_kernel::top()->push_icw().bus(XE,x0); break;
    case north: scamp5_kernel::top()->push_icw().bus(XS,x0); break;
    case south: scamp5_kernel::top()->push_icw().bus(XN,x0); break;
    default: break;
    }
    switch(dir2){
    case east: scamp5_kernel::top()->push_icw().bus(y,XE,x1); break;
    case west: scamp5_kernel::top()->push_icw().bus(y,XW,x1); break;
    case north: scamp5_kernel::top()->push_icw().bus(y,XN,x1); break;
    case south: scamp5_kernel::top()->push_icw().bus(y,XS,x1); break;
    default: break;
    }
}



// Image Capture
//------------------------------------------------------------------------------


/*!
 * @brief	y := half-range image, and reset PIX
 *
 */
inline void get_image( AREG y ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus(SCAMP5_MACRO_T_AREG,PIX);
    scamp5_kernel::top()->push_icw().rpix();
    scamp5_kernel::top()->push_icw().rpix();
    scamp5_kernel::top()->push_icw().nop();
    scamp5_kernel::top()->push_icw().bus(y,SCAMP5_MACRO_T_AREG,PIX);
}

/*!
 * @brief	y := full-range image, h := negative half-range image, and reset PIX
 *
 */
inline void get_image( AREG y, AREG h ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus(SCAMP5_MACRO_T_AREG,PIX);
    scamp5_kernel::top()->push_icw().bus(h,PIX);
    scamp5_kernel::top()->push_icw().rpix();
    scamp5_kernel::top()->push_icw().rpix();
    scamp5_kernel::top()->push_icw().nop();
    scamp5_kernel::top()->push_icw().bus(y,h,SCAMP5_MACRO_T_AREG,PIX);
}


/*!
 * @brief 	reset PIX
 *
 */
inline void respix(){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().rpix();
    scamp5_kernel::top()->push_icw().rpix();
    scamp5_kernel::top()->push_icw().nop();
}

/*!
 * @brief 	reset PIX, keep its reset level in y
 *
 */
inline void respix( AREG y ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().rpix();
    scamp5_kernel::top()->push_icw().rpix();
    scamp5_kernel::top()->push_icw().nop();
    scamp5_kernel::top()->push_icw().bus(SCAMP5_MACRO_T_AREG,PIX);
    scamp5_kernel::top()->push_icw().bus(y,SCAMP5_MACRO_T_AREG);
}

/*!
 * @brief	y := half-range image, supplying the reset level of PIX
 *
 */
inline void getpix( AREG y, AREG pix_res ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus(SCAMP5_MACRO_T_AREG,PIX);
    scamp5_kernel::top()->push_icw().bus(y,SCAMP5_MACRO_T_AREG,pix_res);
}

/*!
 * @brief	y := full-range, h := half-range image, supplying the reset level of PIX
 *
 */
inline void getpix( AREG y, AREG h, AREG pix_res ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus(h,PIX);
    scamp5_kernel::top()->push_icw().bus(SCAMP5_MACRO_T_AREG,PIX);
    scamp5_kernel::top()->push_icw().bus(y,h,SCAMP5_MACRO_T_AREG,pix_res);
}



// Image Blur
//------------------------------------------------------------------------------

/*!
 * @brief	blur x into y with constant number of iterations (x and y can be same AREG), require R1 and R2 to be set properly
 *
 */
inline void gauss( AREG y, ASRC x, const int iterations = 3 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().blurset();
    scamp5_kernel::top()->push_icw().blur(NEWS,x);
    scamp5_kernel::top()->push_icw().blur(y,NEWS);
    for(int i=1;i<iterations;i++){
        scamp5_kernel::top()->push_icw().blur(NEWS,y);
        scamp5_kernel::top()->push_icw().blur(y,NEWS);
    }
}


/*!
 * @brief	horizontally blur x into y with constant number of iterations (x and y can be same AREG), require R1 and R2 to be set properly
 *
 */
inline void gaussh( AREG y, ASRC x, const int iterations = 3 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().blurset();
    scamp5_kernel::top()->push_icw().blurh(NEWS,x);
    scamp5_kernel::top()->push_icw().blurh(y,NEWS);
    for(int i=1;i<iterations;i++){
        scamp5_kernel::top()->push_icw().blurh(NEWS,y);
        scamp5_kernel::top()->push_icw().blurh(y,NEWS);
    }
}


/*!
 * @brief	vertically blur x into y with constant number of iterations (x and y can be same AREG), require R1 and R2 to be set properly
 *
 */
inline void gaussv( AREG y, ASRC x, const int iterations = 3 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().blurset();
    scamp5_kernel::top()->push_icw().blurv(NEWS,x);
    scamp5_kernel::top()->push_icw().blurv(y,NEWS);
    for(int i=1;i<iterations;i++){
        scamp5_kernel::top()->push_icw().blurv(NEWS,y);
        scamp5_kernel::top()->push_icw().blurv(y,NEWS);
    }
}


/*!
 * @brief	blur x into y with constant number of iterations using neighbour mixing (x and y can be same AREG)
 *
 */
inline void newsblur( AREG y, ASRC x, const int iterations = 1 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus(NEWS,x);
    scamp5_kernel::top()->push_icw().bus(y,XE,XW,XN,XS);
    for(int i=1;i<iterations;i++){
        scamp5_kernel::top()->push_icw().bus(NEWS,y);
        scamp5_kernel::top()->push_icw().bus(y,XE,XW,XN,XS);
    }
}


/*!
 * @brief	horizontally blur x into y with constant number of iterations using neighbour mixing (x and y can be same AREG)
 *
 */
inline void newsblurh( AREG y, ASRC x, const int iterations = 1 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus(NEWS,x);
    scamp5_kernel::top()->push_icw().bus(y,XE,XW);
    for(int i=1;i<iterations;i++){
        scamp5_kernel::top()->push_icw().bus(NEWS,y);
        scamp5_kernel::top()->push_icw().bus(y,XE,XW);
    }
}


/*!
 * @brief	vertically blur x into y with constant number of iterations using neighbour mixing (x and y can be same AREG)
 *
 */
inline void newsblurv( AREG y, ASRC x, const int iterations = 1 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus(NEWS,x);
    scamp5_kernel::top()->push_icw().bus(y,XN,XS);
    for(int i=1;i<iterations;i++){
        scamp5_kernel::top()->push_icw().bus(NEWS,y);
        scamp5_kernel::top()->push_icw().bus(y,XN,XS);
    }
}


#ifndef _DOXYGEN_
};
#endif

#endif
