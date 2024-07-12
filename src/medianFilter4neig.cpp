#include <scamp5.hpp>
#include <vs_random.hpp>
#include <vector>
using namespace SCAMP5_PE;

/*
A, B, C
*/

inline void getImage(AREG x){
    // capture a half-scale image in A
    scamp5_kernel_begin();
        get_image(x);
    scamp5_kernel_end();
}


inline void comp2A(AREG input, AREG flag){
    scamp5_kernel_begin();
    sub(flag, input, A);
    where(flag); // input > A
        NOT(R0, FLAG);
        mov(C, B);
        mov(B, input);
    all();
    WHERE(R0); // input < A
        mov(C, B);
        mov(B, A);
        mov(A, input);  
    all();
    scamp5_kernel_end();
}

inline  void comp2B(AREG input, AREG flag){
    scamp5_kernel_begin();
    sub(flag, input, B);
    where(flag); // input > B
        NOT(R0, FLAG);
        mov(C, input);
    all();
    WHERE(R0); // input < B
        mov(C, B);
        mov(B, input);
    all();
    scamp5_kernel_end();
}


inline void comp2C(AREG input, AREG flag){
    scamp5_kernel_begin();
    sub(flag, C, input);
    where(flag);
        mov(C, input);
    all();
    scamp5_kernel_end();
}



inline void move(AREG y, AREG x){
    scamp5_kernel_begin();
    mov(y, x);
    scamp5_kernel_end();
}
inline void moveDir(AREG y, AREG x, const news_t dir){
    scamp5_kernel_begin();
    movx(y, x, dir);
    scamp5_kernel_end();
}
inline  void moveDir(AREG y, AREG x, const news_t dir0, const news_t dir1){
    scamp5_kernel_begin();
    mov2x(y, x, dir0, dir1);
    scamp5_kernel_end();
}

inline  void inital(int value){
    scamp5_in(A, value);
    scamp5_in(B, value);
    scamp5_in(C, value);
    }


int main(){
    vs_init();

    // Setup Host GUI
    auto display_1 = vs_gui_add_display("half-scale",0,0);
    auto display_2 = vs_gui_add_display("median-filting",0,1);

    vs_gui_set_info(VS_M0_PROJECT_INFO_STRING);

    while(1){
        vs_frame_loop_control();
        getImage(F);
        // addNoise();
        scamp5_output_image(F, display_1);
        
        // sorting A B C D
        inital(127);

        moveDir(F, F, north);
        comp2A(F, E);
        comp2B(F, E);
        comp2C(F, E);

        moveDir(F, F, south, west);
        comp2A(F, E);
        comp2B(F, E);
        comp2C(F, E);

        moveDir(F, F, south, east);
        comp2A(F, E);
        comp2B(F, E);
        comp2C(F, E);

        moveDir(F, F, north, east);
        comp2A(F, E);
        comp2B(F, E);
        comp2C(F, E);
        moveDir(F, F, west);
        comp2A(F, E);
        comp2B(F, E);
        comp2C(F, E);

       
    
        // readout register image and send to host GUI for display
        scamp5_output_image(C, display_2);
    }
    return 0;
}