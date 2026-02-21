#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../raylib/src/raylib.h"

#define WIN_W 800
#define WIN_H 650
#define TEXTSIZE 20
#define TEXTOFFSET 35

int debug = 0;

struct text_block {
    int textsize;
    int count;
    int scroll;
    int lineC;
    char *text;
};

int main (int argc, char** argv)
{
    char buf;
    FILE *file;
    Vector2 mousepos;
    Vector2 ballpos;
    int hidetext = 0;
    int lineclick = -1;

    struct text_block textB = {
	128, 0, 0, 0,
	(char *) malloc(sizeof(char) * textB.textsize)};

    file = fopen("main.c", "r");
    if (file == NULL)
	return -1;

    while ((buf = fgetc(file)) != EOF) {
	if (textB.count == textB.textsize-1) {
	    textB.textsize += 128;
	    textB.text = (char *) realloc(textB.text, sizeof(char) * textB.textsize);
	}
	if (buf == '\n') textB.lineC++;
	textB.text[textB.count] = buf;
	textB.count++;
    }
    textB.text[textB.count] = '\0';
    if (debug) {
	printf("%s",textB.text);
	printf("%d characters in file", textB.count);
    }

    InitWindow(WIN_W, WIN_H, "[coder]");
    SetTargetFPS(30);

    while (!WindowShouldClose()) {
	char info_text[256] = {0};
	char line_text[64] = {0};
	char mouse_text[128] = {0};
	char lineclick_text[64] = {0};
	mousepos = GetMousePosition();

	snprintf(lineclick_text, 63, "clicked on %d", lineclick);
	snprintf(mouse_text, 127, "mx: %.1f, my: %.1f ", mousepos.x, mousepos.y);
	snprintf(line_text, 63, "lines: %d ", textB.lineC);
	strncat(info_text, line_text, 255);
	strncat(info_text, mouse_text, 255);
	if (lineclick != -1)
	    strncat(info_text, lineclick_text, 255);

	if (IsKeyDown(KEY_DOWN)) {
	    if(!hidetext && textB.scroll < textB.lineC*TEXTSIZE) textB.scroll += TEXTSIZE;
	}
	else if (IsKeyDown(KEY_UP))
	    if(!hidetext && textB.scroll > 0) textB.scroll -= TEXTSIZE;

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
	    if(mousepos.x >= 5 && mousepos.y >= 5 && mousepos.x <= 25 && mousepos.y <= 25)
		hidetext = !hidetext;
	    else {
		if (mousepos.y > 30.0) {
		    lineclick = (mousepos.y + textB.scroll-TEXTOFFSET)/(TEXTSIZE+2);
		    ballpos.x = mousepos.x;
		    ballpos.y = mousepos.y;
		}
		else
		    lineclick = -1;
	    }
	}

	BeginDrawing();

	ClearBackground(RAYWHITE);

	if (lineclick != -1) {
	    DrawRectangle(0, TEXTOFFSET+(lineclick*(TEXTSIZE+2))-textB.scroll,WIN_W,TEXTSIZE,LIGHTGRAY);
	    DrawCircleV(ballpos, 10.0, RED);
	}

	//Source code text
	if (!hidetext)
	    DrawText(textB.text, 10, TEXTOFFSET - textB.scroll, TEXTSIZE, BLACK);

	DrawRectangle(0,0, WIN_W, 30, GRAY);
	DrawRectangle(5,5, 20, 20, RAYWHITE);
	DrawText(info_text, 35, 5, TEXTSIZE, RAYWHITE);

	EndDrawing();
    }

    CloseWindow();
    free(textB.text);

    return 0;
}
