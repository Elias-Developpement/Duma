#ifndef DRAW_H
#define DRAW_H

#include "instances.h"
#include "map.h"
#include "hero.h"
#include "gui.h"
#include "animation.h"

void draw(void);
SDL_Surface* loadTileset(char *fileName);
SDL_Surface* loadImage(char *name);
void drawImage(SDL_Surface *image, int x, int y);
void drawTile(int x, int y, int index, int opacity);
void drawCurrentTile(void);
void drawGrid(void);
void drawCurrentEvent(void);
void delay(unsigned int frameLimit);

#endif // DRAW_H
