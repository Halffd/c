#include "INCLUDE\graphics.h"
#include "INCLUDE\conio.h"

int main()
{

    int gd = DETECT, gm, left = 100, top = 100, right = 200, bottom = 200, x = 300, y = 150, radius = 50;

    initgraph(&gd, &gm, "S:\\BGI");
    //initgraph(&gd, &gm, "S:\\TurboC++\\Disk\\TurboC3\\BGI");

    rectangle(left, top, right, bottom);

    circle(x, y, radius);

    bar(left + 300, top, right + 300, bottom);

    line(left - 10, top + 150, left + 410, top + 150);

    ellipse(x, y + 200, 0, 360, 100, 50);

    outtextxy(left + 100, top + 325, "Meu programa grafico");

    getch();

    closegraph();

    return 0;
}