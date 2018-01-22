#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#define WINDOWS_X           800
#define WINDOWS_Y           640

#define MAP_MIN_X           25
#define MAP_MAX_X           100
#define MAP_MIN_Y           20
#define MAP_MAX_Y           100

#define DUNGEON_MAX_X       1000
#define DUNGEON_MAX_Y       1000

#define HERO_SPEED          22
#define ANIMATION_SPEED     2

#define COLLIDER_WIDTH      28
#define COLLIDER_HEIGHT     16
#define COLLIDER_TRUE       0
#define COLLIDER_FALSE      1

#define UP                  9
#define DOWN                0
#define LEFT                3
#define RIGHT               6

#define ALPHA_R             0
#define ALPHA_G             255
#define ALPHA_B             0

// DEBUT TILESET

#define CEILING             5
#define GROUND              1
#define WALL_UP             13
#define WALL_DOWN           23
#define WALL_LEFT           18
#define WALL_RIGHT          19
#define WALL_UP_LEFT        10
#define WALL_DOWN_LEFT      20
#define WALL_UP_RIGHT       14
#define WALL_DOWN_RIGHT     24
#define WALL_INNER_UP_LEFT  15
#define WALL_INNER_UP_RIGHT  16
#define WALL_INNER_DOWN_LEFT  25
#define WALL_INNER_DOWN_RIGHT  26

// FIN TILESET

#define TILE_SIZE           32
#define TILE_MAX            32

#define EMPTY               0
#define FILL                1

#define LOWLAYER            0
#define HIGHLAYER           1
#define EVENTLAYER          2

#define EVENT_INDEX         20

#define PLAY                3
#define DUNGEON_MAPPING     4
#define EVENTS              5

#define START_POINT         1

#define BLOCKS              1
#define BLOCK_MOVABLE       2
#define BLOCK_ONE_MOVE      3

#define KEYS                4
#define KEY_BASIC           5
#define KEY_BOSS            6

#define CHESTS              7
#define CHEST_BOSS          8
#define CHEST_BASIC         9

#define SWITCHS             10
#define SWITCH_TOLD         11
#define SWITCH_ONE          12

#define DOORS               13
#define DOOR_UP             14
#define DOOR_LEFT           15
#define DOOR_RIGHT          16
#define DOOR_DOWN           17

#define MONSTERS            18
#define MONSTER_SLIME       19
#define MONSTER_GOBELIN     20

#define OBJECTS             21
#define OBJECT_SWORD        22
#define OBJECT_SHIELD       23
#define OBJECT_BOMB         24
#define OBJECT_BOOMERANG    25
#define OBJECT_ARROW        26
#define OBJECT_BOW          27


#endif // DEFS_H
