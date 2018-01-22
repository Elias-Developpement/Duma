#ifndef STRUCTS_H
#define STRUCTS_H

#include "defs.h"

#endif // STRUCTS_H

// Structure pour les salles de donjon
typedef struct Window {
    SDL_Surface *screen;
    SDL_Surface *gridX[WINDOWS_X / TILE_MAX], *gridY[WINDOWS_Y / TILE_MAX];
    Mix_Music *music;

    int edit, showGrid;
}Window;

// Structure d'un donjon
typedef struct Dungeon {
    SDL_Surface *tileset, *font, *event;
    SDL_Color color;
    SDL_Rect positionText;
    TTF_Font *arial;

    int x, y, currentLayer, tileIndex, eventIndex, start;

    int lowLayer[DUNGEON_MAX_X][DUNGEON_MAX_Y];
    int highLayer[DUNGEON_MAX_X][DUNGEON_MAX_Y];
    int eventLayer[DUNGEON_MAX_X][DUNGEON_MAX_Y];
}Dungeon;

typedef struct Ui {
    SDL_Surface *healthBar;
    SDL_Surface *health;
    SDL_Surface *manaBar;
    SDL_Surface *mana;

    SDL_Surface *object;
    SDL_Surface *key;
    SDL_Surface *collision;
}Ui;

typedef struct Hero {
    SDL_Surface *charset;

    int life;
    int mana;
    int key;
    int x, y, speed, animationSpeed;
    int displayed, index, frameIndex, frameTimer;
}Hero;

typedef struct Camera {
    int x, y;
    int width, height, mode;
}Camera;

// Structure du curseur de la souris
typedef struct Cursor {
    SDL_Surface *skin;

    int x, y, tileX, tileY, tileIndex;
}Cursor;

typedef struct Clock {
    float delta;
    float last_tick;
    float last_fps;
}Clock;

// Structure des entrées claviers
typedef struct Input {
    int setTile, setEmpty, setCopy, setSave, setLoad, setReset, setUp, setLeft, setRight, setDown, setControl, setMonster, setChest, setDoor;
    int setSwitch, setBlock, setKey, setNextTile, setBackTile, setLowLayer, setHighLayer, setEventLayer, setGrid;
}Input;

// Structure d'un tileset
typedef struct Tileset {
    SDL_Surface *fileName;
    char name[50];

    int x, y, w, h, width, height, tilesMax;
}Tileset;











































