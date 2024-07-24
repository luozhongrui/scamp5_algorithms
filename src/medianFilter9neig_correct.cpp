#include <scamp5.hpp>
#include <vs_random.hpp>
using namespace SCAMP5_PE;

inline void getImage(AREG x){
    scamp5_kernel_begin();
        get_image(x);
    scamp5_kernel_end();
}

inline void moveDir(AREG y, AREG x, const news_t dir){
    scamp5_kernel_begin();
    movx(y, x, dir);
    scamp5_kernel_end();
}

inline void moveDir(AREG y, AREG x, const news_t dir0, const news_t dir1){
    scamp5_kernel_begin();
    mov2x(y, x, dir0, dir1);
    scamp5_kernel_end();
}

inline void initializeRegisters() {
    scamp5_in(A, 127);
    scamp5_in(B, 127);
    scamp5_in(C, 127);
    scamp5_in(D, 127);
    scamp5_in(E, 127);
}

inline void updateRegistersWithF(AREG F) {
    scamp5_kernel_begin();
    sub(F, F, A);
    where(F);  // F > A
        NOT(R0, FLAG); // Record F <= A immediately after F > A condition is evaluated
        add(F, F, A);
        sub(F, F, B);
        where(F);  // F > B
            NOT(R1, FLAG); // Record F <= B immediately after F > B condition is evaluated
            add(F, F, B);
            sub(F, F, C);
            where(F);  // F > C
                NOT(R2, FLAG); // Record F <= C immediately after F > C condition is evaluated
                add(F, F, C);
                sub(F, F, D);
                where(F);
                    NOT(R3, FLAG);
                    add(F, F, D);
                    sub(F, F, E);
                    where(F);
                        NOT(R4, FLAG);
                        add(F, F, E);
     all();

    NOT(R5, R0); // R0
    NOT(R6, R1); // R1
    NOT(R7, R2); // R2
    NOT(R8, R3); //R3
    MOV(R9, R0);


    // restore F;
    AND(R10, R4, R8);
    WHERE(R10);
        add(F, F, E);
    all();
    AND(R10, R3, R7);
    WHERE(R10);
        add(F, F, D);
     all();
    AND(R10, R2, R6);
    WHERE(R10);
        add(F, F, C);
     all();
    
    AND(R10, R1, R5);
    WHERE(R10);
        add(F, F, B);
     all();
    WHERE(R9);
        add(F, F, A);
    all();



    WHERE(R4); // F < E;
        mov(E, F);
    all();

    WHERE(R3); // F < D
        mov(E, D);
        mov(D, F); 
    all();

    WHERE(R2); // F < C
        mov(E, D);
        mov(D, C); 
        mov(C, F);
    all();

    WHERE(R1); // F < B
        mov(E, D);
        mov(D, C); 
        mov(C, B);
        mov(B, F);
    all();

    WHERE(R9); // F < A
        mov(E, D);
        mov(D, C); 
        mov(C, B);
        mov(B, A);
        mov(A, F);
    all();
           
    scamp5_kernel_end();
}




int main(){
    vs_init();

    // Setup Host GUI
    auto display_1 = vs_gui_add_display("Input Image", 0, 0);
    auto display_2 = vs_gui_add_display("Median Value", 0, 1);

    vs_gui_set_info(VS_M0_PROJECT_INFO_STRING);

    while(1){
        vs_frame_loop_control();
        getImage(F);

        scamp5_output_image(F, display_1);

        initializeRegisters();

        moveDir(F, F, north, west);
        updateRegistersWithF(F);

        moveDir(F, F, east);
        updateRegistersWithF(F);

        moveDir(F, F, east);
        updateRegistersWithF(F);

        moveDir(F, F, south);
        updateRegistersWithF(F);

        moveDir(F, F, south);
        updateRegistersWithF(F);

        moveDir(F, F, west);
        updateRegistersWithF(F);

        moveDir(F, F, west);
        updateRegistersWithF(F);

        moveDir(F, F, north);
        updateRegistersWithF(F);

         moveDir(F, F, east);
        updateRegistersWithF(F);

        // Output the median value
        scamp5_output_image(E, display_2);
    }
    return 0;
}
