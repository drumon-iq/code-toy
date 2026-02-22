#include <stdio.h>
#include "../raylib/src/raylib.h"
#include "main.h"

#define MAX_TRACK 120 //5 seconds of line history

struct bouncing_ball {
    Vector2 pos;
    Vector2 vel;
    Color color;
    float rad;
};

struct bouncing_ball boola = {
    {100, 100},
    {3, 10},
    RED,
    20.0};

Vector2 ball_track[MAX_TRACK] = {0};
int points = 0;

void
doBouncingBall()
{
    ball_track[points] = boola.pos;
    points++;

    if (points == MAX_TRACK) points = 0;

    for (int i=0; i<points; i++) {
	if (i == 0)
	    continue;
	DrawLineV(ball_track[i-1], ball_track[i], GRAY);
    }

    DrawCircleV(boola.pos, boola.rad, boola.color);

    if(boola.vel.y<10) boola.vel.y += 1;

    //Y axis
    if (boola.pos.y < WIN_H-(boola.rad/2)) boola.pos.y += boola.vel.y;
    else { 
	boola.vel.y *= -1;
	boola.pos.y = WIN_H-(boola.rad/2)-1;
    }

    if (boola.pos.y > 0+(boola.rad/2)) boola.pos.y += boola.vel.y;
    else {
	boola.vel.y *= -1;
	boola.pos.y = 1;
    }

    // X axis
    if (boola.pos.x < WIN_W-(boola.rad/2)) boola.pos.x += boola.vel.x;
    else {
	boola.vel.x *= -1;
	boola.pos.x = WIN_W-(boola.rad/2)-1;
    }

    if (boola.pos.x > 0) boola.pos.x += boola.vel.x;
    else {
	boola.vel.x *= -1;
	boola.pos.x = 1;
    }
}
