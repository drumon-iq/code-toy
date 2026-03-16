#include <stdio.h>
#include "main.h"
#include "../raylib/src/raylib.h"

#define AREA_W 700
#define AREA_H 600

char buf[8];
Vector2 l[20];

/*
 * WIN_W 800
 * WIN_H 650
 *
 * Inner square 700 * 600
*/
void
doGraphs()
{
    l[0].x=50;
    l[0].y=40+AREA_H;

    //horizontal lines
    for (int y=0; y<=AREA_H; y+=50) {
	snprintf(buf, 7, "%d", (AREA_H-y)/50);
	DrawLine(50, y+40, AREA_W+50, y+40, LIGHTGRAY);
	DrawText(buf, 20, y+25, 30, LIGHTGRAY);
    }
    //vertical lines
    for (int x=0; x<=AREA_W; x+=50) {
	snprintf(buf, 7, "%d", x/50);
	DrawLine(x+50, 40, x+50, 40+AREA_H, LIGHTGRAY);
	DrawText(buf, x+20, AREA_H+25, 30, LIGHTGRAY);
    }
    //boundaries
    //DrawRectangleLines(50, 40, AREA_W, AREA_H, BLACK);

    //function y=x
    for (int i=0; i<AREA_W; i++) {
	int x = 50 + i;
	int y = (AREA_H + 40) - i; // The math function
	if (y < 40) break;
	DrawPixel(x, y, SKYBLUE);
    }
    //function y=x²+2x
    for (int i=1; i<AREA_W; i++) {
	int x = 50*i + 50;
	int y = (AREA_H + 40) - (((i*i)+(2*i))*50); // The math function
	l[i].x = x;
	l[i].y = y;
	DrawLineV(l[i-1], l[i], BLUE);
	if (y < 40) break;
	if (x > AREA_W+50) break;
    }
}
