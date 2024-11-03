#include <dos.h>
#include <conio.h>
#include <graphics.h>
#include <stdio.h>

union REGS in, out;

void detect_mouse() {
    in.x.ax = 0; // Initialize mouse
    int86(0x33, &in, &out);
    
    // Check if mouse was initialized successfully
    if (out.x.ax == 0) {
        printf("Mouse initialization failed.\n");
    } else {
        printf("Mouse initialized successfully.\n");
    }
}

void show_mouse_graphics() {
    int gdriver = DETECT, gmode;
    
    // Initialize graphics mode
    initgraph(&gdriver, &gmode, "c:\\turboc3\\bgi");
    
    if (gdriver == DETECT) {
        printf("Graphics driver not found.\n");
        return;
    }

    // Enable mouse
    in.x.ax = 1; // Show mouse cursor
    int86(0x33, &in, &out);

    // Wait for user input before closing
    getch();
    
    // Close graphics mode
    closegraph();
}

int main() {
    detect_mouse(); // Detect the mouse

    show_mouse_graphics(); // Show graphics

    return 0;
}