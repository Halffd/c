#include <dos.h>
#include <stdlib.h>
#include <stdio.h>

union REGS in, out;

void detecta_mouse() {
	in.x.ax = 0;

	int86(0X33, &in, &out);//Invoca a interrupção
	if (out.x.ax == 0)
		printf("\nMouse falhou a inicializacao");
	else
		printf("\nMouse foi inicializado com sucesso.");
}
int main() {
	detecta_mouse();

	getchar();

	return 0;
}