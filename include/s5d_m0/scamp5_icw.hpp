/*************************************************************************
 * SCAMP Vision Chip Development System Library
 *------------------------------------------------------------------------
 * Copyright (c) 2020 The University of Manchester. All Rights Reserved.
 *
 *************************************************************************/

#ifndef SCAMP5_ICW_HPP
#define SCAMP5_ICW_HPP

#include <cstdint>
#include <initializer_list>

#ifndef _DOXYGEN_

#define SCAMP5_CLOCK_ANALOG		0
#define SCAMP5_CLOCK_DIGITAL	1
#define SCAMP5_CLOCK_DNEWS		2
#define SCAMP5_CLOCK_PROP		3
#define SCAMP5_CLOCK_AER		4
#define SCAMP5_CLOCK_DOUT		5
#define SCAMP5_CLOCK_FAST		6


namespace SCAMP5_ICW_BITS{

const uint8_t selsq = 0;
const uint8_t selpix = 1;
const uint8_t rstpix = 2;
const uint8_t seldiffe = 3;
const uint8_t seldiffs = 4;
const uint8_t s_in = 5;
const uint8_t rana = 6;
const uint8_t sels = 7;
const uint8_t _bit8 = 8;
const uint8_t sele = 9;
const uint8_t selx = 10;
const uint8_t rid = 11;
const uint8_t seln = 12;
const uint8_t W1 = 13;
const uint8_t W2 = 14;
const uint8_t W3 = 15;
const uint8_t W4 = 16;
const uint8_t W5 = 17;
const uint8_t W6 = 18;
const uint8_t W7 = 19;
const uint8_t wrf = 20;
const uint8_t SEL1 = 21;
const uint8_t SEL2 = 22;
const uint8_t SEL3 = 23;
const uint8_t SEL4 = 24;
const uint8_t SEL5 = 25;
const uint8_t SEL6 = 26;
const uint8_t SEL7 = 27;
const uint8_t setf = 28;
const uint8_t selw = 29;
const uint8_t pupd = 30;
const uint8_t fbus = 31;
const uint8_t RR1 = 32;
const uint8_t RR2 = 33;
const uint8_t RR3 = 34;
const uint8_t RR4 = 35;
const uint8_t RR5 = 36;
const uint8_t RR6 = 37;
const uint8_t RR7 = 38;
const uint8_t RR8 = 39;
const uint8_t RR9 = 40;
const uint8_t RR10 = 41;
const uint8_t RR11 = 42;
const uint8_t RR12 = 43;
const uint8_t LR1 = 44;
const uint8_t LR2 = 45;
const uint8_t LR3 = 46;
const uint8_t LR4 = 47;
const uint8_t LR5 = 48;
const uint8_t LR6 = 49;
const uint8_t LR7 = 50;
const uint8_t LR8 = 51;
const uint8_t LR9 = 52;
const uint8_t LR10 = 53;
const uint8_t LR11 = 54;
const uint8_t LR12 = 55;
const uint8_t lfl = 56;
const uint8_t rfl = 57;
const uint8_t nbit = 58;
const uint8_t nb = 59;
const uint8_t plwb = 60;
const uint8_t plrb = 61;
const uint8_t bit = 62;
const uint8_t bitmode = 63;
const uint8_t wr = 64;
const uint8_t ana = 65;
const uint8_t dig8 = 66;
const uint8_t g_start = 67;
const uint8_t g_stop = 68;
const uint8_t col_out = 69;
const uint8_t dir = 70;
const uint8_t row_out = 71;
const uint8_t s0_left = 72;
const uint8_t s1_left = 73;
const uint8_t rst_start = 74;
const uint8_t rst_stop = 75;
const uint8_t s0_bot = 76;
const uint8_t s1_bot = 77;
const uint8_t pgdb = 78;
const uint8_t pgdbobus = 79;

};

#endif


struct aref_t{
    uint32_t W_bits;
    uint32_t sel_bits;
};


struct areg_t{
    uint32_t W_bits;
    uint32_t sel_bits;
    operator const aref_t&() const{
        return *((const aref_t*)this);
    }
};


struct dref_t{
    uint16_t RR_index;
    uint16_t RR_bits;
    uint16_t LR_index;
    uint16_t LR_bits;
};


struct dreg_t{
    uint16_t RR_index;
    uint16_t RR_bits;
    uint16_t LR_index;
    uint16_t LR_bits;
    operator const dref_t&() const{
        return *((const dref_t*)this);
    }
};


enum news_t { east = 1, west = 2, north = 4, south = 8, alldir = 15 };


namespace SCAMP5_PE{

// { W_bits, sel_bits }
const areg_t A =    { .W_bits = (1<<13), .sel_bits = (1<<21) };
const areg_t B =    { .W_bits = (1<<14), .sel_bits = (1<<22) };
const areg_t C =    { .W_bits = (1<<15), .sel_bits = (1<<23) };
const areg_t NEWS = { .W_bits = (1<<16), .sel_bits = (1<<24)|(1<<10) };
const areg_t D =    { .W_bits = (1<<17), .sel_bits = (1<<25) };
const areg_t E =    { .W_bits = (1<<18), .sel_bits = (1<<26) };
const areg_t F =    { .W_bits = (1<<19), .sel_bits = (1<<27) };

const areg_t XN = {.W_bits = (1<<16), .sel_bits = (1<<24)|(1<<7) };
const areg_t XE = { .W_bits = (1<<16), .sel_bits = (1<<24)|(1<<9) };
const areg_t XS = {.W_bits = (1<<16), .sel_bits = (1<<24)|(1<<12) };
const areg_t XW = { .W_bits = (1<<16), .sel_bits = (1<<24)|(1<<29) };

const aref_t PIX =  { .W_bits = (1<<8), .sel_bits = (1<<1) };
const aref_t IN =   { .W_bits = (1<<8), .sel_bits = (1<<5) };

// { RR_index, RR_bits, LR_index, LR_bits }

const dreg_t R1 =   { .RR_index = 2, .RR_bits = (1<<0), .LR_index = 2, .LR_bits = (1<<12) };
const dreg_t R2 =   { .RR_index = 2, .RR_bits = (1<<1), .LR_index = 2, .LR_bits = (1<<13) };
const dreg_t R3 =   { .RR_index = 2, .RR_bits = (1<<2), .LR_index = 2, .LR_bits = (1<<14) };
const dreg_t R4 =   { .RR_index = 2, .RR_bits = (1<<3), .LR_index = 2, .LR_bits = (1<<15) };
const dreg_t R5 =   { .RR_index = 2, .RR_bits = (1<<4), .LR_index = 3, .LR_bits = (1<<0) };
const dreg_t R6 =   { .RR_index = 2, .RR_bits = (1<<5), .LR_index = 3, .LR_bits = (1<<1) };
const dreg_t R7 =   { .RR_index = 2, .RR_bits = (1<<6), .LR_index = 3, .LR_bits = (1<<2) };
const dreg_t R8 =   { .RR_index = 2, .RR_bits = (1<<7), .LR_index = 3, .LR_bits = (1<<3) };
const dreg_t R9 =   { .RR_index = 2, .RR_bits = (1<<8), .LR_index = 3, .LR_bits = (1<<4) };
const dreg_t R10 =  { .RR_index = 2, .RR_bits = (1<<9), .LR_index = 3, .LR_bits = (1<<5) };
const dreg_t R11 =  { .RR_index = 2, .RR_bits = (1<<10), .LR_index = 3, .LR_bits = (1<<6) };
const dreg_t R12 =  { .RR_index = 2, .RR_bits = (1<<11), .LR_index = 3, .LR_bits = (1<<7) };
const dreg_t R0 =   { .RR_index = 3, .RR_bits = (1<<9), .LR_index = 3, .LR_bits = (1<<8) };

const dref_t FLAG = { .RR_index = 0, .RR_bits = (1<<6), .LR_index = 0, .LR_bits = (1<<8) };
const dref_t SELECT = { .RR_index = 4, .RR_bits = (1<<0), .LR_index = 0, .LR_bits = (1<<8) };
const dref_t RECT = { .RR_index = 4, .RR_bits = (1<<0)|(1<<8)|(1<<12), .LR_index = 0, .LR_bits = (1<<8) };

#define RS 	R1
#define RW 	R2
#define RN 	R3
#define RE 	R4
#define S0	R5
#define S1	R6
#define S2	R7
#define S3	R8
#define S4	R9
#define S5	R10
#define S6	R11
#define RP 	R12
#define RF 	R0

};


#define AREG areg_t const&
#define ASRC aref_t const&
#define DREG dreg_t const&
#define DSRC dref_t const&

#define SCAMP5_MACRO_T_AREG  SCAMP5_PE::NEWS
#define SCAMP5_MACRO_T_DREG  SCAMP5_PE::R0

struct s5d_port_icw_t{
    uint32_t word:16;
    uint32_t loc:3;
    uint32_t clk:3;
    uint32_t _n_a:10;
};


/*! 
    ICW is the machine code executed by the SCAMP-5 vision chip
*/
class scamp5_icw{

public:

//

    union{

        uint32_t port_data[5];
        s5d_port_icw_t port_bit[5];
        
        struct{

            /* uint32_t port_data[0] */
            uint32_t selsq:1;
            uint32_t selpix:1;
            uint32_t rstpix:1;
            uint32_t seldiffe:1;
            uint32_t seldiffs:1;
            uint32_t s_in:1;// sin
            uint32_t rana:1;
            uint32_t sels:1;// bit 7
            uint32_t _unk:1;
            uint32_t sele:1;
            uint32_t selx:1;
            uint32_t rid:1;
            uint32_t seln:1;
            uint32_t W1:1;
            uint32_t W2:1;
            uint32_t W3:1;// bit 15
            
            uint32_t loc0:3;
            uint32_t clk0:3;
            uint32_t _masked0:10;

            /* uint32_t port_data[1] */
            uint32_t W4:1;
            uint32_t W5:1;
            uint32_t W6:1;
            uint32_t W7:1;
            uint32_t wrf:1;
            uint32_t SEL1:1;
            uint32_t SEL2:1;
            uint32_t SEL3:1;// bit 23
            uint32_t SEL4:1;
            uint32_t SEL5:1;
            uint32_t SEL6:1;
            uint32_t SEL7:1;
            uint32_t setf:1;
            uint32_t selw:1;
            uint32_t pupd:1;
            uint32_t fbus:1;// bit 31, aka: float

            uint32_t loc1:3;
            uint32_t clk1:3;
            uint32_t _masked1:10;

            /* uint32_t port_data[2] */
            uint32_t RR1:1;
            uint32_t RR2:1;
            uint32_t RR3:1;
            uint32_t RR4:1;
            uint32_t RR5:1;
            uint32_t RR6:1;
            uint32_t RR7:1;
            uint32_t RR8:1;// bit 39
            uint32_t RR9:1;
            uint32_t RR10:1;
            uint32_t RR11:1;
            uint32_t RR12:1;
            uint32_t LR1:1;
            uint32_t LR2:1;
            uint32_t LR3:1;
            uint32_t LR4:1;// bit 47

            uint32_t loc2:3;
            uint32_t clk2:3;
            uint32_t _masked2:10;

            /* uint32_t port_data[3] */
            uint32_t LR5:1;
            uint32_t LR6:1;
            uint32_t LR7:1;
            uint32_t LR8:1;
            uint32_t LR9:1;
            uint32_t LR10:1;
            uint32_t LR11:1;
            uint32_t LR12:1;// bit 55
            uint32_t lfl:1;
            uint32_t rfl:1;
            uint32_t nbit:1;
            uint32_t nb:1;
            uint32_t plwb:1;
            uint32_t plrb:1;
            uint32_t bit:1;
            uint32_t bitmode:1;// bit 63

            uint32_t loc3:3;
            uint32_t clk3:3;
            uint32_t _masked3:10;

            /* uint32_t port_data[4] */
            uint32_t wr:1;
            uint32_t ana:1;
            uint32_t dig8:1;
            uint32_t g_start:1;
            uint32_t g_stop:1;
            uint32_t col_out:1;
            uint32_t dir:1;
            uint32_t row_out:1;// bit 71
            uint32_t s0_left:1;
            uint32_t s1_left:1;
            uint32_t rst_start:1;
            uint32_t rst_stop:1;
            uint32_t s0_bot:1;
            uint32_t s1_bot:1;
            uint32_t pgdb:1;
            uint32_t pgdbobus:1;// bit 79

            uint32_t loc4:3;
            uint32_t clk4:3;
            uint32_t _masked4:10;
            
        } bit;
    };
    
    scamp5_icw(){
        port_data[0] = 0x00000000UL;
        port_data[1] = 0x00010000UL;
        port_data[2] = 0x00020000UL;
        port_data[3] = 0x00030000UL;
        port_data[4] = 0x00040000UL;
    }

    scamp5_icw(uint8_t clock,const std::initializer_list<uint8_t>& bits){
        port_data[0] = 0x00000000UL;
        port_data[1] = 0x00010000UL;
        port_data[2] = 0x00020000UL;
        port_data[3] = 0x00030000UL;
        port_data[4] = 0x00040000UL;
		bit.clk0 = clock;
		for(auto&bit_pos:bits){
			port_data[bit_pos/16] |= 1<<(bit_pos%16);
		}
    }

    //--------

    inline scamp5_icw& clear_bits(){
        port_data[0] = 0x00000000UL;
        port_data[1] = 0x00010000UL;
        port_data[2] = 0x00020000UL;
        port_data[3] = 0x00030000UL;
        port_data[4] = 0x00040000UL;
        return *this;
    }

    inline scamp5_icw& set_bits(uint8_t clock,const std::initializer_list<uint8_t>& bits){
        bit.clk0 = clock;
    	for(auto&bit_pos:bits){
    	    port_data[bit_pos/16] |= 1<<(bit_pos%16);
    	}
        return *this;
    }

    inline scamp5_icw& set_sel(const areg_t &bitpos){
        port_bit[0].word |= (0x0000FFFFUL&bitpos.sel_bits);
        port_bit[1].word |= (0xFFFF0000UL&bitpos.sel_bits)>>16;
        return *this;
    }
    inline scamp5_icw& set_sel(const aref_t &bitpos){
        port_bit[0].word |= (0x0000FFFFUL&bitpos.sel_bits);
        port_bit[1].word |= (0xFFFF0000UL&bitpos.sel_bits)>>16;
        return *this;
    }
    
    inline scamp5_icw& set_W(const areg_t &bitpos){
        port_bit[0].word |= (0x0000FFFFUL&bitpos.W_bits);
        port_bit[1].word |= (0xFFFF0000UL&bitpos.W_bits)>>16;
        return *this;
    }
    
    inline scamp5_icw& set_RR(const dref_t &bitpos){
        port_bit[bitpos.RR_index].word |= bitpos.RR_bits;
        return *this;
    }
    
    inline scamp5_icw& set_RR(const dreg_t &bitpos){
        port_bit[bitpos.RR_index].word |= bitpos.RR_bits;
        return *this;
    }

    inline scamp5_icw& set_LR(const dreg_t &bitpos){
        port_bit[bitpos.LR_index].word |= bitpos.LR_bits;
        return *this;
    }

    // instructions

    inline scamp5_icw& nop(){
        clear_bits();
        return *this;
    }

    inline scamp5_icw& rpix(){
        bit.rstpix = 1;
        bit.selpix = 1;
        return *this;
    }

    inline scamp5_icw& aout( ASRC a ){
        set_sel(a);
        bit.ana = 1;
        return *this;
    }

    inline scamp5_icw& bus( const std::initializer_list<const areg_t>& dst, const std::initializer_list<const aref_t>& src ){
    	for(auto&a:dst){
            set_sel(a);
            set_W(a);
    	}
    	for(auto&a:src){
            set_sel(a);
    	}
        return *this;
    }

    inline scamp5_icw& bus( AREG a ){
        set_sel(a);
        set_W(a);
        return *this;
    }

    inline scamp5_icw& bus( AREG a, ASRC a0 ){
        set_sel(a);
        set_W(a);
        set_sel(a0);
        return *this;
    }
    
    inline scamp5_icw& bus( AREG a, ASRC a0, ASRC a1 ){
        set_sel(a);
        set_W(a);
        set_sel(a0);
        set_sel(a1);
        return *this;
    }
    
    inline scamp5_icw& bus( AREG a, ASRC a0, ASRC a1, ASRC a2 ){
        set_sel(a);
        set_W(a);
        set_sel(a0);
        set_sel(a1);
        set_sel(a2);
        return *this;
    }
    
    inline scamp5_icw& bus( AREG a, ASRC a0, ASRC a1, ASRC a2, ASRC a3 ){
        set_sel(a);
        set_W(a);
        set_sel(a0);
        set_sel(a1);
        set_sel(a2);
        set_sel(a3);
        return *this;
    }

    inline scamp5_icw& bus2( AREG a, AREG b ){
        set_sel(a);
        set_sel(b);
        set_W(a);
        set_W(b);
        return *this;
    }

    inline scamp5_icw& bus2( AREG a, AREG b, ASRC a0 ){
        set_sel(a);
        set_sel(b);
        set_W(a);
        set_W(b);
        set_sel(a0);
        return *this;
    }

    inline scamp5_icw& bus2( AREG a, AREG b, ASRC a0, ASRC a1 ){
        set_sel(a);
        set_sel(b);
        set_W(a);
        set_W(b);
        set_sel(a0);
        set_sel(a1);
        return *this;
    }

    inline scamp5_icw& bus3( AREG a, AREG b, AREG c, ASRC a0 ){
        set_sel(a);
        set_sel(b);
        set_sel(c);
        set_W(a);
        set_W(b);
        set_W(c);
        set_sel(a0);
        return *this;
    }

    inline scamp5_icw& blurset(){
        bit.clk0 = 1;
        set_RR(SCAMP5_PE::R1);
        set_RR(SCAMP5_PE::R2);
        return *this;
    }

    inline scamp5_icw& blur( AREG a, ASRC a0 ){
        set_sel(a0);
        set_W(a);
        set_sel(a);
        bit.seldiffe = 1;
        bit.seldiffs = 1;
        return *this;
    }

    inline scamp5_icw& blurh( AREG a, ASRC a0 ){
        set_sel(a0);
        set_W(a);
        set_sel(a);
        bit.seldiffe = 1;
        return *this;
    }

    inline scamp5_icw& blurv( AREG a, ASRC a0 ){
        set_sel(a0);
        set_W(a);
        set_sel(a);
        bit.seldiffs = 1;
        return *this;
    }

    inline scamp5_icw& sq( ASRC a0 ){
        set_sel(SCAMP5_PE::NEWS);
        set_W(SCAMP5_PE::NEWS);
        set_sel(a0);
        bit.selsq = 1;
        return *this;
    }

    inline scamp5_icw& sq( ASRC a0, ASRC a1 ){
        set_sel(SCAMP5_PE::NEWS);
        set_W(SCAMP5_PE::NEWS);
        set_sel(a0);
        set_sel(a1);
        bit.selsq = 1;
        return *this;
    }

    inline scamp5_icw& where( ASRC a ){
        bit.wrf = 1;
        set_sel(a);
        return *this;
    }

    inline scamp5_icw& where( ASRC a0, ASRC a1 ){
        bit.wrf = 1;
        set_sel(a0);
        set_sel(a1);
        return *this;
    }

    inline scamp5_icw& where( ASRC a0, ASRC a1, ASRC a2 ){
        bit.wrf = 1;
        set_sel(a0);
        set_sel(a1);
        set_sel(a2);
        return *this;
    }

    inline scamp5_icw& WHERE( DSRC d ){
        bit.clk0 = 1;
        bit.wrf = 1;
        bit.plrb = 1;
        bit.rid = 1;
        set_RR(d);
        return *this;
    }

    inline scamp5_icw& WHERE( DSRC d0, DSRC d1 ){
        bit.clk0 = 1;
        bit.wrf = 1;
        bit.plrb = 1;
        bit.rid = 1;
        set_RR(d0);
        set_RR(d1);
        return *this;
    }

    inline scamp5_icw& WHERE( DSRC d0, DSRC d1, DSRC d2 ){
        bit.clk0 = 1;
        bit.wrf = 1;
        bit.plrb = 1;
        bit.rid = 1;
        set_RR(d0);
        set_RR(d1);
        set_RR(d2);
        return *this;
    }

    inline scamp5_icw& all(){
        bit.setf = 1;
        // patch
        bit.plrb = 1;
        bit.rid = 1;
        return *this;
    }

    inline scamp5_icw& SET( DREG d ){
        bit.clk0 = 1;
        bit.s_in = 1;
        bit.plwb = 1;
        bit.plrb = 0;
        bit.bit = 0;
        bit.bitmode = 0;
        set_LR(d);
        return *this;
    }

    inline scamp5_icw& SET( DREG d0, DREG d1 ){
        bit.clk0 = 1;
        bit.s_in = 1;
        bit.plwb = 1;
        bit.plrb = 0;
        bit.bit = 0;
        bit.bitmode = 0;
        set_LR(d0);
        set_LR(d1);
        return *this;
    }

    inline scamp5_icw& SET( DREG d0, DREG d1, DREG d2 ){
        bit.clk0 = 1;
        bit.s_in = 1;
        bit.plwb = 1;
        bit.plrb = 0;
        bit.bit = 0;
        bit.bitmode = 0;
        set_LR(d0);
        set_LR(d1);
        set_LR(d2);
        return *this;
    }

    inline scamp5_icw& SET( DREG d0, DREG d1, DREG d2, DREG d3 ){
        bit.clk0 = 1;
        bit.s_in = 1;
        bit.plwb = 1;
        bit.plrb = 0;
        bit.bit = 0;
        bit.bitmode = 0;
        set_LR(d0);
        set_LR(d1);
        set_LR(d2);
        set_LR(d3);
        return *this;
    }

    inline scamp5_icw& CLR( DREG d ){
        bit.clk0 = 1;
        bit.s_in = 1;
        bit.plrb = 1;
        bit.bit = 1;
        bit.bitmode = 1;
        set_LR(d);
        return *this;
    }

    inline scamp5_icw& CLR( DREG d0, DREG d1 ){
        bit.clk0 = 1;
        bit.s_in = 1;
        bit.plrb = 1;
        bit.bit = 1;
        bit.bitmode = 1;
        set_LR(d0);
        set_LR(d1);
        return *this;
    }

    inline scamp5_icw& CLR( DREG d0, DREG d1, DREG d2 ){
        bit.clk0 = 1;
        bit.s_in = 1;
        bit.plrb = 1;
        bit.bit = 1;
        bit.bitmode = 1;
        set_LR(d0);
        set_LR(d1);
        set_LR(d2);
        return *this;
    }

    inline scamp5_icw& CLR( DREG d0, DREG d1, DREG d2, DREG d3 ){
        bit.clk0 = 1;
        bit.s_in = 1;
        bit.plrb = 1;
        bit.bit = 1;
        bit.bitmode = 1;
        set_LR(d0);
        set_LR(d1);
        set_LR(d2);
        set_LR(d3);
        return *this;
    }

    inline scamp5_icw& MOV( DREG d, DSRC d0 ){
        bit.clk0 = 1;
        bit.s_in = 1;
        bit.plrb = 1;
        bit.bit = 1;
        bit.bitmode = 1;
        set_LR(d);
        set_RR(d0);
        return *this;
    }

    inline scamp5_icw& OR( DREG d, DSRC d0, DSRC d1 ){
        bit.clk0 = 1;
        bit.s_in = 1;
        bit.plrb = 1;
        bit.bit = 1;
        bit.bitmode = 1;
        set_LR(d);
        set_RR(d0);
        set_RR(d1);
        return *this;
    }

    inline scamp5_icw& OR( DREG d, DSRC d0, DSRC d1, DSRC d2 ){
        bit.clk0 = 1;
        bit.s_in = 1;
        bit.plrb = 1;
        bit.bit = 1;
        bit.bitmode = 1;
        set_LR(d);
        set_RR(d0);
        set_RR(d1);
        set_RR(d2);
        return *this;
    }

    inline scamp5_icw& OR( DREG d, DSRC d0, DSRC d1, DSRC d2, DSRC d3 ){
        bit.clk0 = 1;
        bit.s_in = 1;
        bit.plrb = 1;
        bit.bit = 1;
        bit.bitmode = 1;
        set_LR(d);
        set_RR(d0);
        set_RR(d1);
        set_RR(d2);
        set_RR(d3);
        return *this;
    }

    inline scamp5_icw& NOT( DREG d, DSRC d0 ){
        bit.clk0 = 1;
        bit.s_in = 1;
        bit.plwb = 1;
        bit.plrb = 1;
        bit.nbit = 1;
        bit.bitmode = 1;
        set_LR(d);
        set_RR(d0);
        return *this;
    }

    inline scamp5_icw& NOR( DREG d, DSRC d0, DSRC d1 ){
        bit.clk0 = 1;
        bit.s_in = 1;
        bit.plwb = 1;
        bit.plrb = 1;
        bit.nbit = 1;
        bit.bitmode = 1;
        set_LR(d);
        set_RR(d0);
        set_RR(d1);
        return *this;
    }

    inline scamp5_icw& NOR( DREG d, DSRC d0, DSRC d1, DSRC d2 ){
        bit.clk0 = 1;
        bit.s_in = 1;
        bit.plwb = 1;
        bit.plrb = 1;
        bit.nbit = 1;
        bit.bitmode = 1;
        set_LR(d);
        set_RR(d0);
        set_RR(d1);
        set_RR(d2);
        return *this;
    }

    inline scamp5_icw& NOR( DREG d, DSRC d0, DSRC d1, DSRC d2, DSRC d3 ){
        bit.clk0 = 1;
        bit.s_in = 1;
        bit.plwb = 1;
        bit.plrb = 1;
        bit.nbit = 1;
        bit.bitmode = 1;
        set_LR(d);
        set_RR(d0);
        set_RR(d1);
        set_RR(d2);
        set_RR(d3);
        return *this;
    }

    inline scamp5_icw& REFRESH_R( DREG d ){
        bit.clk0 = 1;
        bit.s_in = 1;
        bit.plrb = 1;
        bit.bit = 1;
        bit.bitmode = 1;
        set_RR(d);
        return *this;
    }

    inline scamp5_icw& REFRESH_L( DREG d ){
        bit.clk0 = 1;
        bit.s_in = 1;
        bit.bit = 1;
        bit.bitmode = 1;
        set_LR(d);
        return *this;
    }

    inline scamp5_icw& DNEWS0( DREG d, DSRC d0 ){
        bit.clk0 = 2;
        bit.s_in = 1;
        bit.rid = 1;
        bit.nb = 1;
        bit.plrb = 1;
        bit.bit = 1;
        bit.fbus = 1;
        set_LR(d);
        set_RR(d0);
        return *this;
    }

    inline scamp5_icw& DNEWS1( DREG d, DSRC d0 ){
        bit.clk0 = 2;
        bit.s_in = 1;
        bit.rid = 1;
        bit.nb = 1;
        bit.plrb = 1;
        bit.bit = 1;
        bit.pupd = 1;
        bit.fbus = 1;
        set_LR(d);
        set_RR(d0);
        return *this;
    }

    inline scamp5_icw& PROP_R(){
        bit.s_in = 1;
        bit.RR12 = 1;
        bit.plrb = 1;
        bit.bit = 1;
        bit.bitmode = 1;
        return *this;
    }

    inline scamp5_icw& PROP_0(){
        bit.clk0 = 3;
        bit.s_in = 1;
        bit.RR12 = 1;
        bit.LR12 = 1;
        bit.fbus = 1;
        bit.rid = 1;
        bit.nb = 1;
        return *this;
    }

    inline scamp5_icw& PROP_1(){
        bit.clk0 = 3;
        bit.s_in = 1;
        bit.RR12 = 1;
        bit.LR12 = 1;
        bit.fbus = 1;
        bit.rid = 1;
        bit.nb = 1;
        bit.pupd = 1;
        return *this;
    }

};


extern const uint32_t const_icw_reset[4][5];
extern const uint32_t const_icw_refresh[26][5];
extern const uint32_t const_icw_gstart_gstop[2][5];


#endif
