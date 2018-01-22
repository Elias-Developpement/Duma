#include "draw.h"

SDL_Surface* loadTileset(char *fileName) {
    SDL_Surface *temp = IMG_Load(fileName);
    SDL_Surface *image;

    if(temp == NULL) {
        return NULL;
    }

    SDL_SetColorKey(temp, (SDL_SRCCOLORKEY | SDL_RLEACCEL), SDL_MapRGB(temp->format, ALPHA_R, ALPHA_G, ALPHA_B));

    image = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    if(image == NULL) {
        return NULL;
    }

    tileset.x = 0;
    tileset.y = 0;
    tileset.width = image->w / TILE_MAX;
    tileset.height = image->h / TILE_MAX;
    tileset.tilesMax = (image->w / TILE_MAX) * (image->h / TILE_MAX);

    return image;
}

SDL_Surface* loadImage(char *name) {
    SDL_Surface *temp = IMG_Load(name);
    SDL_Surface *image;

    if(temp == NULL) {
        return NULL;
    }

    SDL_SetColorKey(temp, (SDL_SRCCOLORKEY | SDL_RLEACCEL), SDL_MapRGB(temp->format, ALPHA_R, ALPHA_G, ALPHA_B));

    image = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    if(image == NULL) {
        return NULL;
    }

    return image;
}

// Overall draw
void draw(void) {
    SDL_FillRect(game.screen, NULL, SDL_MapRGB(game.screen->format, 0, 0, 0));
    switch(game.edit) {
        case DUNGEON_MAPPING:
            // Draw the dungeon
            drawDungeon();

            SDL_ShowCursor(1);

            if(game.showGrid == 1) {
                drawGrid();
            }

            if(dungeon.currentLayer != EVENTLAYER) {
                drawCurrentTile();
            }
            else {
                if(dungeon.eventIndex != 0) {
                    drawCurrentEvent();
                }
            }

            displayCursor();
            break;
        case PLAY:
            // Draw the game
            drawDungeon();

            if(input.setLeft == 1 || input.setRight == 1 || input.setUp == 1 || input.setDown == 1) {
                drawAnimatedPlayer();
            }

            drawGui();
            break;
    }

    // Screen refresh
    SDL_Flip(game.screen);
    SDL_Delay(1);
}

// Draw image
void drawImage(SDL_Surface *image, int x, int y) {
    SDL_Rect positionImage;

    positionImage.x = x;
    positionImage.y = y;
    positionImage.w = image->w;
    positionImage.h = image->h;

    SDL_BlitSurface(image, NULL, game.screen, &positionImage);
}

// Draw map grid
void drawGrid(void) {
    SDL_Rect positionGrid;
    int i, j;

    for(i = TILE_SIZE - (camera.x % TILE_SIZE) ; i <= WINDOWS_X - (camera.x % TILE_SIZE) ; i += TILE_SIZE) {
        positionGrid.x = i;
        positionGrid.y = 0;

        if(i >= 0 && i <= WINDOWS_X - TILE_SIZE) {
            SDL_SetAlpha(game.gridX[i / TILE_SIZE], SDL_SRCALPHA, 95);
            SDL_FillRect(game.gridX[i / TILE_SIZE], NULL, SDL_MapRGB(game.screen->format, 255, 255, 255));
            SDL_BlitSurface(game.gridX[i / TILE_SIZE], NULL, game.screen, &positionGrid);
        }

    }

    for(j = TILE_SIZE - (camera.y % TILE_SIZE) ; j <= WINDOWS_Y - (camera.y % TILE_SIZE) ; j += TILE_SIZE) {
        positionGrid.x = 0;
        positionGrid.y = j;

        if(j >= 0 && j <= WINDOWS_Y - TILE_SIZE) {
            SDL_SetAlpha(game.gridY[j / TILE_SIZE], SDL_SRCALPHA, 95);
            SDL_FillRect(game.gridY[j / TILE_SIZE], NULL, SDL_MapRGB(game.screen->format, 255, 255, 255));
            SDL_BlitSurface(game.gridY[j / TILE_SIZE], NULL, game.screen, &positionGrid);
        }
    }
}

// Draw tiles
void drawTile(int x, int y, int index, int opacity) {
    SDL_Rect positionIndex, positionTile;
    switch(dungeon.currentLayer) {
        case LOWLAYER:
            positionIndex.y = index / tileset.width;
            positionIndex.x = index % tileset.width;
            positionIndex.w = TILE_MAX;
            positionIndex.h = TILE_MAX;

            positionTile.x = x;
            positionTile.y = y;

            SDL_SetAlpha(tileset.fileName, SDL_SRCALPHA, opacity);

            SDL_BlitSurface(tileset.fileName, &positionIndex, game.screen, &positionTile);
            break;
        case HIGHLAYER:
            positionIndex.y = index / tileset.width;
            positionIndex.x = index % tileset.width;
            positionIndex.w = TILE_MAX;
            positionIndex.h = TILE_MAX;

            positionTile.x = x;
            positionTile.y = y;

            SDL_SetAlpha(tileset.fileName, SDL_SRCALPHA, opacity);

            SDL_BlitSurface(tileset.fileName, &positionIndex, game.screen, &positionTile);
            break;
        case EVENTLAYER:
            positionTile.x = x;
            positionTile.y = y;

            SDL_SetAlpha(dungeon.event, SDL_SRCALPHA, opacity);
            if(dungeon.eventIndex == START_POINT) {
                SDL_BlitSurface(dungeon.event, NULL, game.screen, &positionTile);
            }
            break;
    }
}

// Draw selected tile
void drawCurrentTile(void) {
    SDL_Rect positionTile, positionIndex;

    // On récupère la position de la souris pour afficher le tile
    positionTile.x = cursor.x;
    positionTile.y = cursor.y;

    // On récupère l'emplacement du tile dans le tileset
    positionIndex.x = (dungeon.tileIndex % (tileset.fileName->w / TILE_MAX)) * TILE_MAX;
    positionIndex.y = (dungeon.tileIndex / (tileset.fileName->w / TILE_MAX)) * TILE_MAX;
    positionIndex.w = TILE_MAX;
    positionIndex.h = TILE_MAX;

    SDL_SetAlpha(tileset.fileName, SDL_SRCALPHA, 255);
    SDL_BlitSurface(tileset.fileName, &positionIndex, game.screen, &positionTile);
}

// Draw selected event
void drawCurrentEvent(void) {
    SDL_Rect positionTile;

    positionTile.x = cursor.x;
    positionTile.y = cursor.y;

    SDL_SetAlpha(dungeon.event, SDL_SRCALPHA, 255);
    SDL_BlitSurface(dungeon.event, NULL, game.screen, &positionTile);
}

// Frame rate
void delay(unsigned int frameLimit) {
    unsigned int ticks = SDL_GetTicks();

    if(frameLimit < ticks) {
        return;
    }

    if(frameLimit > ticks + 16) {
        SDL_Delay(16);
    }
    else {
        SDL_Delay(frameLimit - ticks);
    }
}
