#include <dos.h>
#include <graphics.h>
union REGS in, out;

void showmouse_graphics() {
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "c :\\turboc3\\bgi");
	in.x.ax = 1;
	int86(0X33, &in, &out);
	getch();
	closegraph();
}

void detecta_mouse() {
	in.x.ax = 0;

	int86(0X33, &in, &out);
	//Invoca a interrupção

	if (out.x.ax == 0)
		printf("\nMouse falhou a inicializacao");
	else
		printf("\nMouse foi inicializado com sucesso.");
}
int main() {
	detecta_mouse();

	showmouse_graphics();

	getch();
	return 0;
}