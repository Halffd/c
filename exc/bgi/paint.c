#include <graphics.h>

#include <dos.h>

union REGS in, out;

void detecta_mouse()

{

  in.x.ax = 0;

  int86(0X33, &in, &out); // Invoca a interrupção

  if (out.x.ax == 0)

    printf("\nMouse falhou a inicializacao");

  else

    printf("\nMouse foi inicializado com sucesso.");
}

void mostra_mouse()

{

  i.x.ax = 1;

  int86(0x33, &i, &o);
}

void esconde_mouse()

{

  i.x.ax = 2;

  int86(0x33, &i, &o);
}

void obtem_pos_mouse(int *x, int *y, int *button)

{

  i.x.ax = 3;

  int86(0x33, &i, &o);

  *x = o.x.cx;

  *y = o.x.dx;

  *button = o.x.bx & 1;
}

void main()
{
  int gdriver = DETECT, gmode, errorcode, button, x1, y1, x2, y2;

  initgraph(&gdriver, &gmode, "c:\\tc\\bgi");

  detecta_mouse();

  outtextxy(230, 400, "Pressione qualquer Tecla para sair…");

  while (!kbhit())

  {

    mostra_mouse();

    obtem_pos_mouse(&x1, &y1, &button); // Obtém a posição do mouse

    // Todo o tempo

    x2 = x1;

    y2 = y1;

    while (button == 1) // Botão esquerdo pressionado

    {

      esconde_mouse(); // Esconde o ponteiro quando inicia o desenho

      line(x1, y1, x2, y2);
          x1 = x2;

      y1 = y2;

      obtem_pos_mouse(&x2, &y2, &button); // Continua obtendo a
      // posição do mouse
    }
  }
}