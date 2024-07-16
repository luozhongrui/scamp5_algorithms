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
}

inline void updateRegistersWithF(AREG F) {
    scamp5_kernel_begin();
    sub(E, F, A);
    where(E);  // F > A
        NOT(R0, FLAG); // Record F <= A immediately after F > A condition is evaluated
        sub(E, F, B);
        where(E);  // F > B
            NOT(R1, FLAG); // Record F <= B immediately after F > B condition is evaluated
            sub(E, F, C);
            where(E);  // F > C
                // F is discarded
                NOT(R2, FLAG); // Record F <= C immediately after F > C condition is evaluated
            all();
            WHERE(R2);  // F <= C
                mov(C, F);  // Update C, keep A and B unchanged
            all();
       
        WHERE(R1);  // F <= B
            mov(C, B);
            mov(B, F);
        all();
  
    WHERE(R0);  // F <= A
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

        moveDir(F, F, north);
        updateRegistersWithF(F);

        moveDir(F, F, south, south);
        updateRegistersWithF(F);

        moveDir(F, F, north, west);
        updateRegistersWithF(F);

        moveDir(F, F, east, east);
        updateRegistersWithF(F);

        moveDir(F, F, west);
        updateRegistersWithF(F);

        // Output the median value
        scamp5_output_image(C, display_2);
    }
    return 0;
}
