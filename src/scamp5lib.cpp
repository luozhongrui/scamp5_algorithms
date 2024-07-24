#include <scamp5.hpp>

using namespace SCAMP5_PE;


// struct areg_t{
// 	const uint16_t index;
//     const char*name;
//     operator const aref_t&() const{
//         return *((const aref_t*)this);
//     }
// };


extern "C" {
    /*build in function*/
    __declspec(dllexport) vs_handle my_vs_gui_add_display(const char* text, uint8_t row, uint8_t col, int size=1, const char* style=NULL) {
        return vs_gui_add_display(text, row, col, size, style);
    }

     __declspec(dllexport) void my_scamp5_output_image(AREG reg, vs_handle display) {
        scamp5_output_image(reg, display);
    }

     __declspec(dllexport) void vsInit() {
        vs_init();
    }

    __declspec(dllexport) void vsGuiSetInfo() {
        vs_gui_set_info(VS_M0_PROJECT_INFO_STRING);
    }

    __declspec(dllexport) void vsFrameLoopControl() {
        vs_frame_loop_control();
    }

    /*custom function*/
    __declspec(dllexport) void getImage(AREG x){
        scamp5_kernel_begin();
        get_image(x);
        scamp5_kernel_end();
    }

    __declspec(dllexport) void add(AREG z, AREG x, AREG y) {
        scamp5_kernel_begin();
        add(z, x, y);
        scamp5_kernel_end();
    }

    __declspec(dllexport) void sub(AREG z, AREG x, AREG y) {
        scamp5_kernel_begin();
        sub(z, x, y);
        scamp5_kernel_end();
    }

    __declspec(dllexport) void moveDir(AREG y, AREG x, const news_t dir) {
        scamp5_kernel_begin();
        movx(y, x, dir);
        scamp5_kernel_end();
    }

    __declspec(dllexport) void move2Dir(AREG y, AREG x, const news_t dir0, const news_t dir1) {
        scamp5_kernel_begin();
        mov2x(y, x, dir0, dir1);
        scamp5_kernel_end();
    }

    __declspec(dllexport) void initializeRegisters() {
        scamp5_in(A, 127);
        scamp5_in(B, 127);
        scamp5_in(C, 127);
    }

    __declspec(dllexport) void updateRegistersWithF(AREG F) {
        scamp5_kernel_begin();
        sub(E, F, A);
        where(E);  // F > A
        NOT(R0, FLAG); // Record F <= A immediately after F > A condition is evaluated
        sub(E, F, B);
        where(E);  // F > B
        NOT(R1, FLAG); // Record F <= B immediately after F > B condition is evaluated
        sub(E, F, C);
        where(E);  // F > C
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

    __declspec(dllexport) void medianFilter(AREG x) {
        initializeRegisters();
        moveDir(x, x, north);
        updateRegistersWithF(F);
        move2Dir(x, x, south, south);
        updateRegistersWithF(F);
        move2Dir(x, x, north, west);
        updateRegistersWithF(F);
        move2Dir(x, x, east, east);
        updateRegistersWithF(F);
        moveDir(x, x, west);
        updateRegistersWithF(F);
    }

}
