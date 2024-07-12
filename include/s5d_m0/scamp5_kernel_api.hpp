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

#ifndef SCAMP5_KERNEL_API_HPP
#define SCAMP5_KERNEL_API_HPP


#include <functional>
#include <scamp5_icw.hpp>


/*!
This is the object that represent a program that runs on each of the PE.
*/
class scamp5_kernel{


protected:

    static const size_t ICW_STACK_CAP = 1024;

    // use native data to not execute the constructor of 'scamp5_icw'
    static uint32_t icw_stack_mem[ICW_STACK_CAP][5];
    static uint16_t icw_stack_top;
    static scamp5_kernel* active_context;
    static scamp5_icw overflow_icw;

    static inline scamp5_icw& icw_stack(size_t index){
        return index[(scamp5_icw*)icw_stack_mem];
    }

    scamp5_icw* icw_start;
    uint16_t icw_counter;

    inline bool stack_check(){
    	return (icw_stack_top + icw_counter) >= ICW_STACK_CAP;
    }

public:

    static void init_icw_stack();
    static void print_debug_info();

    inline static scamp5_kernel*top(){
        return active_context;
    }

    bool highspeed;
    bool move_to_heap;
    bool is_rom;

    scamp5_kernel(){
        init_icw_stack();
        icw_start = NULL;
        icw_counter = 0;
        highspeed = false;
        move_to_heap = false;
        is_rom = false;
    }

    scamp5_kernel(const uint32_t (*icw)[5],size_t n){
        init_icw_stack();
        icw_start = (scamp5_icw*)icw;
        icw_counter = n;
        highspeed = false;
        move_to_heap = false;
    	is_rom = true;
    }

    scamp5_kernel(std::function<void(void)> kernel_func){
        init_icw_stack();
        icw_start = NULL;
        icw_counter = 0;
        highspeed = false;
        move_to_heap = false;
        is_rom = false;
        this->recording_start();
        kernel_func();
        this->recording_stop();
    }

    ~scamp5_kernel(){
    	if(is_rom){
    		return;
    	}else
    	if(move_to_heap){
    		delete[] icw_start;
    	}else{
			icw_stack_top -= icw_counter;
			while(icw_counter--){
				icw_start[icw_counter].clear_bits();
			}
    	}
    }

    void recording_start();
    void recording_stop();

    inline scamp5_kernel&operator()(std::function<void(void)> kernel_func){
        if(this->null()){
            this->recording_start();
            kernel_func();
            this->recording_stop();
        }
        return *this;
    }

    inline int null(){
        return (icw_start==NULL);
    }

    inline scamp5_icw& icw(){
    	if(stack_check()){
    		return overflow_icw;
    	}
        return icw_start[icw_counter];
    }

    inline void push(){
    	if(stack_check()){
    		return;
    	}
        icw_counter++;
    }

    inline scamp5_icw& push_icw(){
    	if(stack_check()){
    		return overflow_icw;
    	}
        return icw_start[icw_counter++];
    }

    inline void push_icw(scamp5_icw const& icw){
    	if(stack_check()){
    		return;
    	}
        icw_start[icw_counter++] = icw;
    }


    void operator()();

    /*!
        @brief execute a kernel predefined as an ::scamp5_kernel object
    */
    friend void scamp5_launch_kernel(scamp5_kernel&o){
    	o();
    }

};


class scamp5_kernel_printable:public scamp5_kernel{

public:

	const char*file;
	int line;

	scamp5_kernel_printable(const char*f,int l){
		file = f;
		line = l;
	}

	void print_const_kernel_source();

	void recording_stop(){
		scamp5_kernel::recording_stop();
		print_const_kernel_source();
	}

};


#ifdef __LPC43XX__

#define scamp5_kernel_begin() {\
		using namespace SCAMP5_ICW_BITS;\
		using namespace scamp5_kernel_api;\
		static scamp5_kernel __sk;\
		if(__sk.null()){\
			__sk.recording_start();

#define scamp5_kernel_end() __sk.recording_stop();\
		}\
		scamp5_launch_kernel(__sk);\
	}


#define scamp5_dynamic_kernel_begin() {\
		using namespace SCAMP5_ICW_BITS;\
		using namespace scamp5_kernel_api;\
		scamp5_kernel __sk;\
		__sk.recording_start();

#define scamp5_dynamic_kernel_end() __sk.recording_stop();\
		scamp5_launch_kernel(__sk);\
	}


#define scamp5_kernel_begin_print() {\
		using namespace SCAMP5_ICW_BITS;\
		using namespace scamp5_kernel_api;\
		static scamp5_kernel_printable __sk(__FILE__,__LINE__);\
		if(__sk.null()){\
			__sk.recording_start();


#else

/*!
	\brief entering a scamp5 kernel section

*/
void scamp5_kernel_begin();


/*!
	\brief finishing a scamp5 kernel section

*/
void scamp5_kernel_end();


/*!
	\brief entering a scamp5 kernel section that contains variables

*/
void scamp5_dynamic_kernel_begin();


/*!
	\brief finishing a scamp5 kernel section that contains variables

*/
void scamp5_kernel_begin_print();


/*!
	\brief entering a scamp5 kernel section and print the compiled instructions to the host

*/
void scamp5_kernel_printable();

#endif


/*!
	\brief execute an ::all() instruction without create a kernel

*/
void scamp5_kernel_all();


/*!
	\brief execute instructions to refresh all DREGs without create a kernel

*/
void scamp5_kernel_refresh_dreg();


/*!
	all functions under this namespace can only be used inside a SCAMP kernel
*/
namespace scamp5_kernel_api{


inline void icw(uint8_t clock,const std::initializer_list<uint8_t>& bits){
    scamp5_kernel::top()->push_icw(scamp5_icw(clock,bits));
}


inline void allow_highspeed(bool k){
	if(!k){
		scamp5_kernel::top()->highspeed = false;
	}
}


inline void move_to_heap(bool k){
	scamp5_kernel::top()->move_to_heap = k;
}

#ifdef _DOXYGEN_
};
#endif


/* Single-instruction Operations */

inline void nop(){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().nop();
}


/*!
 * @brief 	reset PIX
 *
 */
inline void rpix(){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().rpix();
}


/*!
 * @brief 	a := 0 + error
 *
 */
inline void bus( AREG a ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus(a);
}


/*!
 * @brief 	a := -a0 + error
 *
 */
inline void bus( AREG a, ASRC a0 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus(a,a0);
}


/*!
 * @brief 	a := -(a0 + a1) + error
 *
 */
inline void bus( AREG a, ASRC a0, ASRC a1 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus(a,a0,a1);
}


/*!
 * @brief 	a := -(a0 + a1 + a2) + error
 *
 */
inline void bus( AREG a, ASRC a0, ASRC a1, ASRC a2 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus(a,a0,a1,a2);
}


/*!
 * @brief 	a := -(a0 + a1 + a2 + a3) + error
 *
 */
inline void bus( AREG a, ASRC a0, ASRC a1, ASRC a2, ASRC a3 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus(a,a0,a1,a2,a3);
}


/*!
 * @brief 	a,b := 0 + error
 *
 */
inline void bus2( AREG a, AREG b ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus2(a,b);
}


/*!
 * @brief 	a,b := -0.5*a0 + error + noise
 *
 */
inline void bus2( AREG a, AREG b, ASRC a0 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus2(a,b,a0);
}


/*!
 * @brief 	a,b := -0.5*(a0 + a1) + error + noise
 *
 */
inline void bus2( AREG a, AREG b, ASRC a0, ASRC a1 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus2(a,b,a0,a1);
}


/*!
 * @brief 	a,b,c := -0.33*a0 + error + noise
 *
 */
inline void bus3( AREG a, AREG b, AREG c, ASRC a0 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().bus3(a,b,c,a0);
}


inline void bus( const std::initializer_list<const areg_t>& dst, const std::initializer_list<const aref_t>& src ){
    scamp5_kernel::top()->highspeed = false;
	for(auto&a:dst){
		scamp5_kernel::top()->icw().set_sel(a);
		scamp5_kernel::top()->icw().set_W(a);
	}
	for(auto&a:src){
		scamp5_kernel::top()->icw().set_sel(a);
	}
	scamp5_kernel::top()->push();
}



inline void sq( ASRC a0 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().sq(a0);
}


inline void sq( ASRC a0, ASRC a1 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().sq(a0,a1);
}


/*!
 * @brief 	need to be used once ahead of a blur instruction
 *
 */
inline void blurset(){
    scamp5_kernel::top()->push_icw().blurset();
}


/*!
 * @brief 	analog asynchronized blur
 *
 */
inline void blur( AREG a, ASRC a0 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().blur(a,a0);
}


/*!
 * @brief 	analog asynchronized blur, horizontal only
 *
 */
inline void blurh( AREG a, ASRC a0 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().blurh(a,a0);
}


/*!
 * @brief 	analog asynchronized blur, vertical only
 *
 */
inline void blurv( AREG a, ASRC a0 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().blurv(a,a0);
}


/*!
 * @brief 	FLAG := a > 0
 *
 */
inline void where( ASRC a ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().where(a);
}


/*!
 * @brief 	FLAG := (a0 + a1) > 0
 *
 */
inline void where( ASRC a0, ASRC a1 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().where(a0,a1);
}


/*!
 * @brief 	FLAG := (a0 + a1 + a2) > 0
 *
 */
inline void where( ASRC a0, ASRC a1, ASRC a2 ){
    scamp5_kernel::top()->highspeed = false;
    scamp5_kernel::top()->push_icw().where(a0,a1,a2);
}


/*!
 * @brief 	FLAG := 1
 *
 */
inline void all(){
    scamp5_kernel::top()->push_icw().all();
}


/*!
 * @brief 	FLAG := d
 *
 */
inline void WHERE( DSRC d ){
    scamp5_kernel::top()->push_icw().WHERE(d);
}


/*!
 * @brief 	FLAG := d0 OR d1
 *
 */
inline void WHERE( DSRC d0, DSRC d1 ){
    scamp5_kernel::top()->push_icw().WHERE(d0,d1);
}


/*!
 * @brief 	FLAG := d0 OR d1 OR d2
 *
 */
inline void WHERE( DSRC d0, DSRC d1, DSRC d2 ){
    scamp5_kernel::top()->push_icw().WHERE(d0,d1,d2);
}


/*!
 * @brief 	FLAG := 1, same as ::all
 *
 */
inline void ALL(){
    scamp5_kernel::top()->push_icw().all();
}


/*!
 * @brief 	d0 := 1
 *
 */
inline void SET( DREG d0 ){
    scamp5_kernel::top()->push_icw().SET(d0);
}


/*!
 * @brief 	d0, d1 := 1
 *
 */
inline void SET( DREG d0, DREG d1 ){
    scamp5_kernel::top()->push_icw().SET(d0,d1);
}


/*!
 * @brief 	d0, d1, d2 := 1
 *
 */
inline void SET( DREG d0, DREG d1, DREG d2 ){
    scamp5_kernel::top()->push_icw().SET(d0,d1,d2);
}


/*!
 * @brief 	d0, d1, d2, d3 := 1
 *
 */
inline void SET( DREG d0, DREG d1, DREG d2, DREG d3 ){
    scamp5_kernel::top()->push_icw().SET(d0,d1,d2,d3);
}


/*!
 * @brief 	d0 := 0
 *
 */
inline void CLR( DREG d0 ){
    scamp5_kernel::top()->push_icw().CLR(d0);
}


/*!
 * @brief 	d0, d1 := 0
 *
 */
inline void CLR( DREG d0, DREG d1 ){
    scamp5_kernel::top()->push_icw().CLR(d0,d1);
}


/*!
 * @brief 	d0, d1, d2 := 0
 *
 */
inline void CLR( DREG d0, DREG d1, DREG d2 ){
    scamp5_kernel::top()->push_icw().CLR(d0,d1,d2);
}


/*!
 * @brief 	d0, d1, d2, d3 := 0
 *
 */
inline void CLR( DREG d0, DREG d1, DREG d2, DREG d3 ){
    scamp5_kernel::top()->push_icw().CLR(d0,d1,d2,d3);
}


/*!
 * @brief 	d := d0
 *
 */
inline void MOV( DREG d, DSRC d0 ){
    scamp5_kernel::top()->push_icw().MOV(d,d0);
}


/*!
 * @brief 	d := d0 OR d1
 *
 */
inline void OR( DREG d, DSRC d0, DSRC d1 ){
    scamp5_kernel::top()->push_icw().OR(d,d0,d1);
}


/*!
 * @brief 	d := d0 OR d1 OR d2
 *
 */
inline void OR( DREG d, DSRC d0, DSRC d1, DSRC d2 ){
    scamp5_kernel::top()->push_icw().OR(d,d0,d1,d2);
}


/*!
 * @brief 	d := d0 OR d1 OR d2 OR d3
 *
 */
inline void OR( DREG d, DSRC d0, DSRC d1, DSRC d2, DSRC d3 ){
    scamp5_kernel::top()->push_icw().OR(d,d0,d1,d2,d3);
}


/*!
 * @brief 	d := NOT d0
 *
 */
inline void NOT( DREG d, DSRC d0 ){
    scamp5_kernel::top()->push_icw().NOT(d,d0);
}


/*!
 * @brief 	d := NOT(d0 OR d1)
 *
 */
inline void NOR( DREG d, DSRC d0, DSRC d1 ){
    scamp5_kernel::top()->push_icw().NOR(d,d0,d1);
}


/*!
 * @brief 	d := NOT(d0 OR d1 OR d2)
 *
 */
inline void NOR( DREG d, DSRC d0, DSRC d1, DSRC d2 ){
    scamp5_kernel::top()->push_icw().NOR(d,d0,d1,d2);
}


/*!
 * @brief 	d := NOT(d0 OR d1 OR d2 OR d3)
 *
 */
inline void NOR( DREG d, DSRC d0, DSRC d1, DSRC d2, DSRC d3 ){
    scamp5_kernel::top()->push_icw().NOR(d,d0,d1,d2,d3);
}


/*!
 * @brief 	d := d0_dir, direction selected by R1, R2, R3, R4
 *
 */
inline void DNEWS0( DREG d, DSRC d0 ){
    scamp5_kernel::top()->push_icw().DNEWS0(d,d0);
}


/*!
 * @brief 	d := d0_dir, direction selected by R1, R2, R3, R4
 *
 */
inline void DNEWS1( DREG d, DSRC d0 ){
    scamp5_kernel::top()->push_icw().DNEWS1(d,d0);
}


#ifndef _DOXYGEN_
};
#endif


/*
--------------------------------------------------------------------------------
*/


#ifdef S5D_M0_PRIVATE

void scamp5_kernel_init();

#endif


#endif
