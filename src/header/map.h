#ifndef MAP_H
#define MAP_H

#include "instances.h"
#include "hero.h"

void loadDungeon(void);
void drawDungeon(void);
void initDungeon(void);
void saveDungeon(void);
void setWall(int tileX, int tileY);

#endif // MAP_H
