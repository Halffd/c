#include <dos.h>
#include <conio.h>
#include <stdio.h>

void detectMouse() {
	union REGS in, out;

	// Initialize mouse
	in.x.ax = 0;// Request to initialize mouse
	int86(0x33, &in, &out);

	// Check if mouse is installed
	if (out.x.ax == 0) {
		printf("Mouse not installed.\n");
		return;
	}

	printf("Mouse installed. Move the mouse or click the left button.\n");

	while (!kbhit()) {// While no key is pressed
		int x, y;

		in.x.ax = 3;// Get mouse position and button status
		int86(0x33, &in, &out);

		if (out.x.bx & 1) {// If left button is pressed
			x = out.x.cx;  // X coordinate
			y = out.x.dx;  // Y coordinate
			printf("\nPosition || X: %d, Y: %d", x, y);
		}

		delay(200);// Delay to reduce output frequency
	}

	printf("\nExiting...\n");
}

int main() {
	detectMouse();
	return 0;
}