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


/*
     A < B
 */
 void sortAreg(AREG input, const news_t dir, AREG less, AREG bigger){
    scamp5_kernel_begin();        
        sub(bigger, input, dir, input);
        where(bigger);
            mov(bigger, input, dir);
            mov(less, input);
        all();
    scamp5_kernel_end();
}


void sortAreg(AREG input, const news_t dir0, const news_t dir1, AREG less, AREG bigger){
    scamp5_kernel_begin();
        sub2x(bigger, input, dir0, dir1, input);
        where(bigger);
            mov2x(bigger, input, dir0, dir1);
            mov(less, input);
        all();
    scamp5_kernel_end();
}


void comp2A(AREG input){
    scamp5_kernel_begin();
    sub(A, A, input);
    where(A);
        MOV(R0, FLAG);
        NOT(R1, R0);
        mov(E, D);
        mov(D, C);
        mov(C, B);
        add(B, A, input); // A = A - input + input
        mov(A, input);  
    all();
    WHERE(R1);
        add(A, A, input);
    all();
    CLR(R0, R1);
    scamp5_kernel_end();
}

void comp2B(AREG input){
    scamp5_kernel_begin();
    sub(input, input, A);
    where(input);
        mov(E, D);
        mov(D, C);
        mov(C, B);
        add(B, input, A);
    all();
    add(input, input, A);
    scamp5_kernel_end();
}


void comp2C(AREG input){
    scamp5_kernel_begin();
    sub(input, input, A);
        where(input);
            MOV(R0, FLAG);
            NOT(R1, R0); 
            add(input, input, A);
            sub(input, input, B);
            where(input);
                MOV(R2, FLAG);  // input + B
                NOT(R3, R2);
                // add(input, input, B);
                mov(E, D);
                mov(D, C);
                add(C, input, B);
            all();
            WHERE(R0);
                add(input, input, B);
            // all();
            WHERE(R1);
                add(input, input, A);
        all();
        CLR(R0, R1, R2);
        CLR(R3);
    scamp5_kernel_end();
}


void comp2D(AREG input){
    scamp5_kernel_begin();
    sub(input, input, A);
        where(input);
            MOV(R0, FLAG);
            NOT(R1, R0);
            add(input, input, A);
            sub(input, input, B);
            where(input);
                MOV(R2, FLAG);
                NOT(R3, R2);
                add(input, input, B);
                sub(input, input, C);
                    where(input);
                        // MOV(R4, FLAG);
                        // NOT(R5, R4);
                        // add(input, input, C);
                        mov(E, D);
                        add(D, input, C);
    all();
    WHERE(R2);
        add(input, input, C);
    // all();
    WHERE(R3);
        add(input, input, B);
    // all();
    WHERE(R1);
     add(input, input, A);
    all();
    CLR(R0, R1, R2);
    CLR(R3);
    scamp5_kernel_end();
}


void comp2E(AREG input){
    scamp5_kernel_begin();
    sub(input, input, A);
    where(input);
        MOV(R0, FLAG);
        NOT(R1, R0);
        add(input, input, A);
        sub(input, input, B);
        where(input);
            MOV(R2, FLAG);
            NOT(R3, R2);
            add(input, input, B);
            sub(input, input, C);
            where(input);
                MOV(R4, FLAG);
                NOT(R5, R4);
                add(input, input, C);
                sub(input, input, D);
                where(input);
                    // MOV(R0, FLAG);
                    // NOT(R4, R0);
                    // add(input, input, D);
                    add(E, input, D);
    all();
    WHERE(R4);
        add(input, input, D);
   
    WHERE(R5);
        add(input, input, C);
    
    WHERE(R3);
        add(input, input, B);
   
    WHERE(R1);
        add(input, input, A);
    all();
    CLR(R0, R1, R2);
    CLR(R3, R4, R5);
        
    scamp5_kernel_end();
}

void move(AREG x, AREG y){
    scamp5_kernel_begin();
    mov(x, y);
    scamp5_kernel_end();
}
void moveDir(AREG x, AREG y, const news_t dir){
    scamp5_kernel_begin();
    movx(x, y, dir);
    scamp5_kernel_end();
}
void moveDir(AREG x, AREG y, const news_t dir0, const news_t dir1){
    scamp5_kernel_begin();
    mov2x(x, y, dir0, dir1);
    scamp5_kernel_end();
}

void inital(int value){
    scamp5_in(A, value);
    scamp5_in(B, value);
    scamp5_in(C, value);
    scamp5_in(D, value);
    scamp5_in(E, value);
}


void addNoise(){
    auto rand = new vs_random();
    int ns0 = rand->get_int(0, 127);
    scamp5_in(A, ns0);
    ns0 = rand->get_int(0, 127);
    scamp5_in(B, ns0);
    ns0 = rand->get_int(0, 127);
    scamp5_in(C, ns0);
    scamp5_kernel_begin();
    add(F, F, A);
    subx(F, F, south, B);
    subx(F, F, east, C);
    scamp5_kernel_end();

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
        
        // sorting A B C D E
        inital(120);
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