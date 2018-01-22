#include "camera.h"

void setCamera(int x, int y) {
    camera.x = x;
    camera.y = y;
}

void centerOnPlayer(void) {
    // Calculate the camera position
    camera.x = hero.x - ((WINDOWS_X / TILE_SIZE / 2) * TILE_SIZE);
    camera.y = hero.y - ((WINDOWS_Y / TILE_SIZE / 2) * TILE_SIZE);

    // If the position x of the camera is out of the dungeon size
    if(camera.x < 0) {
        camera.x = 0;
    }
    else if(camera.x + WINDOWS_X > DUNGEON_MAX_X * TILE_SIZE) {
        camera.x = (DUNGEON_MAX_X * TILE_SIZE - WINDOWS_X);
    }

    // If the position y of the camera is out of the dungeon size
    if(camera.y < 0) {
        camera.y = 0;
    }
    else if(camera.y > (DUNGEON_MAX_Y * TILE_SIZE - WINDOWS_Y)) {
        camera.y = (DUNGEON_MAX_Y * TILE_SIZE - WINDOWS_Y);
    }

    //printf("Position X (camera) : %dpx\n", camera.x);
    //printf("Position Y (camera) : %dpx\n\n", camera.y);
}
