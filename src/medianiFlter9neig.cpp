#include <scamp5.hpp>
#include <vs_random.hpp>
#include <vector>
using namespace SCAMP5_PE;

/*
A, B, C, D, E
*/
void getImage(AREG x){
    // capture a half-scale image in A
    scamp5_kernel_begin();
        get_image(x);
    scamp5_kernel_end();
}


inline void comp2A(AREG input){
    scamp5_kernel_begin();
    sub(A, A, input);
    where(A);  // A > input
        mov(E, D);
        mov(D, C);
        mov(C, B);
        add(B, A, input);
        mov(A, input);
        NOT(R0, FLAG);
    all();
    WHERE(R0); // A < input
        mov(E, D);
        mov(D, C);
        mov(C, B);
        mov(B, input);
        add(A, A, input);
    all();
    scamp5_kernel_end();
}

inline void comp2B(AREG input){
    scamp5_kernel_begin();
    sub(B, B, input);
    where(B); // B > input
        mov(E, D);
        mov(D, C);
        add(C, B, input);
        mov(B, input);
        NOT(R0, FLAG);
    all();
    WHERE(R0); // B < input
        mov(E, D);
        mov(D, C);
        mov(C, input);
        add(B, B, input);
    all();
    scamp5_kernel_end();
}


inline void comp2C(AREG input){
    scamp5_kernel_begin();
    sub(C, C, input);
    where(C); // in < C
        mov(E, D);
        add(D, C, input);
        mov(C, input);
        NOT(R0, FLAG);
    all();
    WHERE(R0); // in > C
        mov(E, D);
        mov(D, input);
        add(C, C, input);
    all();
    scamp5_kernel_end();
}


inline void comp2D(AREG input){
    scamp5_kernel_begin();
    sub(D, D, input);
    where(D);  // in < D
        add(E, D, input);
        mov(D, input);
        NOT(R0, FLAG);
    all();
    WHERE(R0);
        mov(E, input);
        add(D, D, input);
    all();
    scamp5_kernel_end();
}

inline void comp2E(AREG input){
    scamp5_kernel_begin();
    sub(E, E, input);
    where(E); // in < E
        mov(E, input);
        NOT(R0, FLAG);
    all();
    WHERE(R0);
        add(E, E, input);
    all();
    scamp5_kernel_end();
}

inline void move(AREG x, AREG y){
    scamp5_kernel_begin();
    mov(x, y);
    scamp5_kernel_end();
}
inline void moveDir(AREG x, AREG y, const news_t dir){
    scamp5_kernel_begin();
    movx(x, y, dir);
    scamp5_kernel_end();
}
inline void moveDir(AREG x, AREG y, const news_t dir0, const news_t dir1){
    scamp5_kernel_begin();
    mov2x(x, y, dir0, dir1);
    scamp5_kernel_end();
}

inline void inital(int value){
    scamp5_in(A, value);
    scamp5_in(B, value);
    scamp5_in(C, value);
    scamp5_in(D, value);
    scamp5_in(E, value);
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
        scamp5_output_image(F, display_1);
        
        // sorting A B C D E
        inital(127);
        moveDir(F, F, north, west);
        comp2A(F);
       
        moveDir(F, F, north);
        comp2A(F);
        comp2B(F);
      

        moveDir(F, F, west);
        comp2A(F);
        comp2B(F);
        comp2C(F);
     
        moveDir(F, F, east, east);
        comp2A(F);
        comp2B(F);
        comp2C(F);
        comp2D(F);

        moveDir(F, F, south);
        comp2A(F);
        comp2B(F);
        comp2C(F);
        comp2D(F);
        comp2E(F);

        moveDir(F, F, west, west);
        comp2A(F);
        comp2B(F);
        comp2C(F);
        comp2D(F);
        comp2E(F);

        moveDir(F, F, south);
        comp2A(F);
        comp2B(F);
        comp2C(F);
        comp2D(F);
        comp2E(F);

        moveDir(F, F, east);
        comp2A(F);
        comp2B(F);
        comp2C(F);
        comp2D(F);
        comp2E(F);
        
        moveDir(F, F, east);
        comp2A(F);
        comp2B(F);
        comp2C(F);
        comp2D(F);
        comp2E(F);
    
    
        // readout register image and send to host GUI for display
        scamp5_output_image(E, display_2);
    }
    return 0;
}