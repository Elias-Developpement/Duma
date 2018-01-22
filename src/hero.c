#include "hero.h"

void displayCharacter(void) {
    SDL_Rect positionCharacter, indexHero;

    // Set the position of the character in the middle of the screen
    if(camera.x == 0) {
        positionCharacter.x = hero.x;
    }
    else {
        positionCharacter.x = (WINDOWS_X / 2) - (hero.charset->w / 2 / 3);
    }

    if(camera.y == 0) {
        positionCharacter.y = hero.y;
    }
    else {
        positionCharacter.y = (WINDOWS_Y / 2) - (hero.charset->h / 2 / 4);
    }
    indexHero.x = hero.frameIndex % 3 * TILE_MAX;
    indexHero.y = hero.frameIndex / 3 * TILE_MAX;
    indexHero.w = TILE_MAX;
    indexHero.h = TILE_MAX;

    // Display the current sprite of the character
    SDL_BlitSurface(hero.charset, &indexHero, game.screen, &positionCharacter);
}

int checkWall(int direction) {
    switch(direction) {
        case UP:
            if(dungeon.lowLayer[(hero.x + (TILE_SIZE / 2)) / TILE_SIZE][(int)(((hero.y) - HERO_SPEED * clock.delta)) / TILE_SIZE] != GROUND) { // dungeon.lowLayer[(hero.x) / TILE_SIZE][((hero.y + TILE_SIZE - COLLIDER_HEIGHT) - HERO_SPEED) / TILE_SIZE]
                return COLLIDER_FALSE;
            }
            else {
                return COLLIDER_TRUE;
            }
            break;
        case DOWN:
            if(dungeon.lowLayer[(hero.x + (TILE_SIZE / 2)) / TILE_SIZE][(int)(((hero.y) + HERO_SPEED * clock.delta) + TILE_SIZE / 2) / TILE_SIZE] != GROUND) { // dungeon.lowLayer[(hero.x) / TILE_SIZE][((hero.y + TILE_SIZE) + HERO_SPEED) / TILE_SIZE]
                return COLLIDER_FALSE;
            }
            else {
                return COLLIDER_TRUE;
            }
            break;
        case LEFT:
            if(dungeon.lowLayer[(int)((hero.x - (HERO_SPEED) * clock.delta) + 10) / TILE_SIZE][(hero.y + (TILE_SIZE / 2)) / TILE_SIZE] != GROUND) { // dungeon.lowLayer[((hero.x + ((TILE_SIZE - COLLIDER_WIDTH) / 2)) - HERO_SPEED) / TILE_SIZE][(hero.y) / TILE_SIZE]
                return COLLIDER_FALSE;
            }
            else {
                return COLLIDER_TRUE;
            }
            break;
        case RIGHT:
            if(dungeon.lowLayer[(int)((hero.x + (HERO_SPEED) * clock.delta) + 22) / TILE_SIZE][(hero.y + (TILE_SIZE / 2)) / TILE_SIZE] != GROUND) { // dungeon.lowLayer[(hero.x + (TILE_SIZE - ((TILE_SIZE - COLLIDER_WIDTH) / 2)) + HERO_SPEED) / TILE_SIZE][(hero.y) / TILE_SIZE]
                return COLLIDER_FALSE;
            }
            else {
                return COLLIDER_TRUE;
            }
            break;
    }
}
