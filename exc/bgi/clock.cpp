#include <time.h>
#include "graphics.h"
#include "winbgim.h"
#define LEN 150

int main()
{
    char buf[LEN];
    time_t curtime;

    struct tm *loc_time;
    initwindow(400, 400);
    settextjustify(CENTER_TEXT, CENTER_TEXT);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);

    setcolor(RED);

    for (int i = 60; i >= 0; i--)

    {

        // obtém hora corrente do sistema

        curtime = time(NULL);

        // converte para o tempo local

        loc_time = localtime(&curtime);

        strftime(buf, LEN, "%I:%M:%S %p", loc_time);

        outtextxy(getmaxx() / 2, getmaxy() / 2, buf);

        delay(1000);

        if (i == 0)

            break;

        cleardevice();
    }

    getch();
}
