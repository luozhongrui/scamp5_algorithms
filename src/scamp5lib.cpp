#include <scamp5.hpp>

using namespace SCAMP5_PE;

void median(AREG x);
void sobel_edge(AREG x);
void laplacian_edge(AREG x);

extern "C" {
    /*build in function*/
    __declspec(dllexport) void load_value(AREG x, int8_t val){
        scamp5_in(x, val);
    }

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

    __declspec(dllexport) void analog_where(AREG x){
        scamp5_kernel_begin();
        where(x);
        scamp5_kernel_end();
    }

    __declspec(dllexport) void digit_where(DREG x){
        scamp5_kernel_begin();
        WHERE(x);
        scamp5_kernel_end();
    }

    /*custom function*/
    __declspec(dllexport) void getImage(AREG x){
        scamp5_kernel_begin();
        get_image(x);
        scamp5_kernel_end();
    }

    __declspec(dllexport) void c_add(AREG z, AREG x, AREG y) {
        scamp5_kernel_begin();
        add(z, x, y);
        scamp5_kernel_end();
    }

    __declspec(dllexport) void c_sub(AREG z, AREG x, AREG y) {
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

    __declspec(dllexport) void c_gt(AREG x, AREG y){
        scamp5_kernel_begin();
        sub(x, x, y);
        where(x);
        scamp5_kernel_end();
    }

    __declspec(dllexport) void c_lt(AREG x, AREG y){
        scamp5_kernel_begin();
        sub(y, y, x);
        where(y);
        scamp5_kernel_end();
    }

    __declspec(dllexport) void c_all(){
        scamp5_kernel_begin();
        all();
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
        median(x);
    }
    __declspec(dllexport) void sobel_filter(AREG x) {
        sobel_edge(x);
    }
    __declspec(dllexport) void laplacian_filter(AREG x) {
        laplacian_edge(x);
    }

}

void median(AREG x){
        initializeRegisters();
        moveDir(x, x, north);
        updateRegistersWithF(x);
        move2Dir(x, x, south, south);
        updateRegistersWithF(x);
        move2Dir(x, x, north, west);
        updateRegistersWithF(x);
        move2Dir(x, x, east, east);
        updateRegistersWithF(x);
        moveDir(x, x, west);
        updateRegistersWithF(x);
}


void sobel_edge(AREG x){
    // Sobel Edge Algorithm (need 4 AREG)
    scamp5_kernel_begin();
    // vertical edge
    movx(A,x,north);
    movx(B,x,south);
    add(A,A,B);
    add(A,A,x);
    add(A,A,x);

    movx(B,A,east);
    movx(A,A,west);

    sub(B,B,A);// B = B - A
    abs(D,B);// D is the vertical edge

    // horizontal edge
    movx(A,x,east);
    movx(B,x,west);
    add(A,A,B);
    add(A,A,x);
    add(A,A,x);

    movx(B,A,south);
    movx(A,A,north);

    sub(B,B,A);// B = B - A
    abs(A,B);// A is the horizontal edge

    add(E,A,D);// put final result in E
    scamp5_kernel_end();
}


void laplacian_edge(AREG x){
    // Laplacian Edge Algorthm (need 3 AREG)
        scamp5_kernel_begin();
			res(A);// A = 0
			subx(B,x,north,x);// B = C_north - C
			add(A,A,B);// A = A + B

			subx(B,x,east,x);// B = C_east - C
			add(A,A,B);// A = A + B

			subx(B,x,west,x);// B = C_west - C
			add(A,A,B);// A = A + B

			subx(B,x,south,x);// B = C_south - C
			add(A,A,B);// A = A + B

			abs(E,A);// F = |A| (final result)
		scamp5_kernel_end();
}
