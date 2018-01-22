#include "map.h"

// Dungeon loading
void loadDungeon() {
    int i, j;
    FILE *file;

    file = fopen("data/dungeon.map", "r");

    // Load the dungeon data file
    if(file == NULL) {
        exit(1);
    }

    fscanf(file, "<dungeon>\n");
    fscanf(file, "  <layer>\n");

    for(i = 0 ; i < DUNGEON_MAX_Y ; i++) {
        for(j = 0 ; j < DUNGEON_MAX_X ; j++) {
            fscanf(file, "%d ", &dungeon.lowLayer[j][i]);
        }
        fscanf(file, "\n");
    }

    fscanf(file, "  </layer>\n");
    fscanf(file, "  <layer>\n");

    for(i = 0 ; i < DUNGEON_MAX_Y ; i++) {
        for(j = 0 ; j < DUNGEON_MAX_X ; j++) {
            fscanf(file, "%d ", &dungeon.highLayer[j][i]);
        }
        fscanf(file, "\n");
    }

    fscanf(file, "  </layer>\n");
    fscanf(file, "  <layer>\n");

    for(i = 0 ; i < DUNGEON_MAX_Y ; i++) {
        for(j = 0 ; j < DUNGEON_MAX_X ; j++) {
            fscanf(file, "%d ", &dungeon.eventLayer[j][i]);
        }
        fscanf(file, "\n");
    }

    fscanf(file, "  </layer>\n");
    fscanf(file, "</dungeon>");

    // Define the current position of the camera
    hero.x = 25 * 32;
    hero.y = 23 * 32;
    centerOnPlayer();

    // Show in the console some informations
    //printf("Position X (hero) : %d\n", hero.x);
    //printf("Position Y (hero) : %d\n\n", hero.y);

    //printf("Position X (camera) : %d\n", camera.x);
    //printf("Position Y (camera) : %d\n\n", camera.y);
    // Load the tileset
    tileset.fileName = loadTileset("data/img/tileset.png");
}

// Draw dungeon
void drawDungeon(void) {
    // Rectangles for calculate tiles positions
    SDL_Rect positionTile, positionIndex;

    // Variables for 'for' loop
    int i, j, endX, endY;

    if((camera.x % TILE_SIZE) != 0) {
        endX = WINDOWS_X + TILE_SIZE;
    }
    else {
        endX = WINDOWS_X;
    }

    if((camera.y % TILE_SIZE) != 0) {
        endY = WINDOWS_Y + TILE_SIZE;
    }
    else {
        endY = WINDOWS_Y;
    }

    // Display all layer
    for(i = ((camera.x % TILE_SIZE) * -1) ; i < endX ; i += TILE_SIZE) {
        for(j = ((camera.y % TILE_SIZE) * -1) ; j < endY ; j += TILE_SIZE) {
            positionTile.x = i; // Position du tile en x sur la map
            positionTile.y = j; // Position du tile en y sur la map

            // Display low layer
            positionIndex.x = (dungeon.lowLayer[(i + camera.x) / TILE_SIZE][(j + camera.y) / TILE_SIZE] % (tileset.fileName->w / TILE_SIZE)) * TILE_SIZE; // Détermine la position du tile en x
            positionIndex.y = (dungeon.lowLayer[(i + camera.x) / TILE_SIZE][(j + camera.y) / TILE_SIZE] / (tileset.fileName->w / TILE_SIZE)) * TILE_SIZE; // Détermine la position du tile en y
            positionIndex.w = TILE_SIZE; // Taille d'un tile
            positionIndex.h = TILE_SIZE; // Taille d'un tile

            if(dungeon.currentLayer == LOWLAYER || game.edit == PLAY) {
                SDL_SetAlpha(tileset.fileName, SDL_SRCALPHA, 255); // Opacité du tile
            }
            else {
                SDL_SetAlpha(tileset.fileName, SDL_SRCALPHA, 200); // Opacité du tile
            }
            SDL_BlitSurface(tileset.fileName, &positionIndex, game.screen, &positionTile); // Affichage du tile
            displayCharacter(); // Affichage du personnage

            /*// Display high layer
            positionIndex.x = (dungeon.highLayer[i][j] % (tileset.fileName->w / TILE_MAX)) * TILE_MAX;
            positionIndex.y = (dungeon.highLayer[i][j] / (tileset.fileName->w / TILE_MAX)) * TILE_MAX;
            positionIndex.w = TILE_MAX;
            positionIndex.h = TILE_MAX;

            if(dungeon.currentLayer == HIGHLAYER || game.edit == PLAY) {
                SDL_SetAlpha(tileset.fileName, SDL_SRCALPHA, 255);
            }
            else {
                SDL_SetAlpha(tileset.fileName, SDL_SRCALPHA, 128);
            }
            SDL_BlitSurface(tileset.fileName, &positionIndex, game.screen, &positionTile);

            // Display event layer
            positionIndex.x = (dungeon.eventLayer[i][j] % (tileset.fileName->w / TILE_MAX)) * TILE_MAX;
            positionIndex.y = (dungeon.eventLayer[i][j] / (tileset.fileName->w / TILE_MAX)) * TILE_MAX;
            positionIndex.w = TILE_MAX;
            positionIndex.h = TILE_MAX;

            if(dungeon.currentLayer == EVENTLAYER || game.edit == PLAY) {
                SDL_SetAlpha(tileset.fileName, SDL_SRCALPHA, 255);
            }
            else {
                SDL_SetAlpha(tileset.fileName, SDL_SRCALPHA, 0);
            }

            switch(dungeon.eventLayer[i][j]) {
                case START_POINT:
                    dungeon.positionText.x = i * TILE_MAX;
                    dungeon.positionText.y = j * TILE_MAX;

                    SDL_BlitSurface(dungeon.event, NULL, game.screen, &dungeon.positionText);
                    break;
            }
            */
        }
    }
}

// Save dungeon
void saveDungeon(void) {
    int i, j;
    FILE *file;

    file = fopen("data/dungeon.map", "w");

    if(file == NULL) {
        exit(1);
    }

    fprintf(file, "<dungeon>\n");
    fprintf(file, "  <layer>\n");

    for(i = 0 ; i < DUNGEON_MAX_Y ; i++) {
        for(j = 0 ; j < DUNGEON_MAX_X ; j++) {
            fprintf(file, "%d ", dungeon.lowLayer[j][i]);
        }
        fprintf(file, "\n");
    }

    fprintf(file, "  </layer>\n");
    fprintf(file, "  <layer>\n");

    for(i = 0 ; i < DUNGEON_MAX_Y ; i++) {
        for(j = 0 ; j < DUNGEON_MAX_X ; j++) {
            fprintf(file, "%d ", dungeon.highLayer[j][i]);
        }
        fprintf(file, "\n");
    }

    fprintf(file, "  </layer>\n");
    fprintf(file, "  <layer>\n");

    for(i = 0 ; i < DUNGEON_MAX_Y ; i++) {
        for(j = 0 ; j < DUNGEON_MAX_X ; j++) {
            fprintf(file, "%d ", dungeon.eventLayer[j][i]);
        }
        fprintf(file, "\n");
    }

    fprintf(file, "  </layer>\n");
    fprintf(file, "</dungeon>");

    fclose(file);
}

// Add walls
void setWall(int tileX, int tileY) {
    // Côté gauche
    switch(dungeon.lowLayer[tileX - 1][tileY]) {
        case GROUND:
            break;
        case CEILING:
            dungeon.lowLayer[tileX - 1][tileY] = WALL_LEFT;
            break;
        case WALL_DOWN:
            dungeon.lowLayer[tileX - 1][tileY] = WALL_INNER_UP_RIGHT;
            break;
        case WALL_UP:
            dungeon.lowLayer[tileX - 1][tileY] = WALL_INNER_DOWN_RIGHT;
            break;
        case WALL_UP_LEFT:
            dungeon.lowLayer[tileX - 1][tileY] = WALL_LEFT;
            break;
        case WALL_DOWN_LEFT:
            dungeon.lowLayer[tileX - 1][tileY] = WALL_LEFT;
            break;
        case WALL_DOWN_RIGHT:
            dungeon.lowLayer[tileX - 1][tileY] = WALL_LEFT;
            break;
    }

    // Côté droite
    switch(dungeon.lowLayer[tileX + 1][tileY]) {
        case GROUND:
            break;
        case CEILING:
            dungeon.lowLayer[tileX + 1][tileY] = WALL_RIGHT;
            break;
        case WALL_DOWN:
            dungeon.lowLayer[tileX + 1][tileY] = WALL_INNER_UP_LEFT;
            break;
        case WALL_UP:
            dungeon.lowLayer[tileX + 1][tileY] = WALL_INNER_DOWN_LEFT;
            break;
        case WALL_UP_LEFT:
            dungeon.lowLayer[tileX + 1][tileY] = WALL_RIGHT;
            break;
        case WALL_UP_RIGHT:
            dungeon.lowLayer[tileX + 1][tileY] = WALL_RIGHT;
            break;
        case WALL_DOWN_RIGHT:
            dungeon.lowLayer[tileX + 1][tileY] = WALL_RIGHT;
            break;
    }

    // Côté haut
    switch(dungeon.lowLayer[tileX][tileY - 1]) {
        case GROUND:
            break;
        case CEILING:
            dungeon.lowLayer[tileX][tileY - 1] = WALL_UP;
            break;
        case WALL_LEFT:
            dungeon.lowLayer[tileX][tileY - 1] = WALL_INNER_DOWN_RIGHT;
            break;
        case WALL_RIGHT:
            dungeon.lowLayer[tileX][tileY - 1] = WALL_INNER_DOWN_LEFT;
            break;
        case WALL_UP_LEFT:
            dungeon.lowLayer[tileX][tileY - 1] = WALL_UP;
            break;
        case WALL_DOWN_LEFT:
            dungeon.lowLayer[tileX][tileY - 1] = WALL_UP;
            break;
        case WALL_UP_RIGHT:
            dungeon.lowLayer[tileX][tileY - 1] = WALL_UP;
            break;
        case WALL_DOWN_RIGHT:
            dungeon.lowLayer[tileX][tileY - 1] = WALL_UP;
            break;
    }

    // Côté bas
    switch(dungeon.lowLayer[tileX][tileY + 1]) {
        case GROUND:
            break;
        case CEILING:
            dungeon.lowLayer[tileX][tileY + 1] = WALL_DOWN;
            break;
        case WALL_LEFT:
            dungeon.lowLayer[tileX][tileY + 1] = WALL_INNER_UP_RIGHT;
            break;
        case WALL_RIGHT:
            dungeon.lowLayer[tileX][tileY + 1] = WALL_INNER_UP_LEFT;
            break;
        case WALL_UP_LEFT:
            dungeon.lowLayer[tileX][tileY + 1] = WALL_DOWN;
            break;
        case WALL_DOWN_LEFT:
            dungeon.lowLayer[tileX][tileY + 1] = WALL_DOWN;
            break;
        case WALL_UP_RIGHT:
            dungeon.lowLayer[tileX][tileY + 1] = WALL_DOWN;
            break;
        case WALL_DOWN_RIGHT:
            dungeon.lowLayer[tileX][tileY + 1] = WALL_DOWN;
            break;
    }

    switch(dungeon.lowLayer[tileX - 1][tileY - 1]) {
        case GROUND:
            break;
        case CEILING:
            dungeon.lowLayer[tileX - 1][tileY - 1] = WALL_UP_LEFT;
            break;
        case WALL_UP:
            break;
    }

    switch(dungeon.lowLayer[tileX - 1][tileY + 1]) {
        case GROUND:
            break;
        case CEILING:
            dungeon.lowLayer[tileX - 1][tileY + 1] = WALL_DOWN_LEFT;
            break;
        case WALL_UP:
            break;
    }

    switch(dungeon.lowLayer[tileX + 1][tileY - 1]) {
        case GROUND:
            break;
        case CEILING:
            dungeon.lowLayer[tileX + 1][tileY - 1] = WALL_UP_RIGHT;
            break;
        case WALL_UP:
            break;
    }

    switch(dungeon.lowLayer[tileX + 1][tileY + 1]) {
        case GROUND:
            break;
        case CEILING:
            dungeon.lowLayer[tileX + 1][tileY + 1] = WALL_DOWN_RIGHT;
            break;
        case WALL_UP:
            break;
    }
}

// Erease walls
void ereaseWall(int tileX, int tileY) {
    // Côté gauche
    switch(dungeon.lowLayer[tileX - 1][tileY]) {
        case GROUND:
            dungeon.lowLayer[tileX - 1][tileY] = WALL_RIGHT;
            break;
        case WALL_DOWN:
            dungeon.lowLayer[tileX - 1][tileY] = WALL_DOWN_RIGHT;
            break;
        case WALL_UP:
            dungeon.lowLayer[tileX - 1][tileY] = WALL_UP_RIGHT;
            break;
        case WALL_UP_LEFT:
            dungeon.lowLayer[tileX - 1][tileY] = CEILING;
            break;
        case WALL_DOWN_LEFT:
            dungeon.lowLayer[tileX - 1][tileY] = CEILING;
            break;
        case WALL_INNER_DOWN_LEFT:
            dungeon.lowLayer[tileX - 1][tileY] = WALL_RIGHT;
            break;
        case WALL_INNER_UP_LEFT:
            dungeon.lowLayer[tileX - 1][tileY] = WALL_RIGHT;
            break;
    }

    // Côté droite
    switch(dungeon.lowLayer[tileX + 1][tileY]) {
        case GROUND:
            dungeon.lowLayer[tileX + 1][tileY] = WALL_LEFT;
            break;
        case WALL_DOWN:
            dungeon.lowLayer[tileX + 1][tileY] = WALL_DOWN_LEFT;
            break;
        case WALL_UP:
            dungeon.lowLayer[tileX + 1][tileY] = WALL_UP_LEFT;
            break;
        case WALL_UP_RIGHT:
            dungeon.lowLayer[tileX + 1][tileY] = CEILING;
            break;
        case WALL_DOWN_RIGHT:
            dungeon.lowLayer[tileX + 1][tileY] = CEILING;
            break;
        case WALL_INNER_DOWN_RIGHT:
            dungeon.lowLayer[tileX + 1][tileY] = WALL_LEFT;
            break;
        case WALL_INNER_UP_RIGHT:
            dungeon.lowLayer[tileX + 1][tileY] = WALL_LEFT;
            break;
    }

    // Côté haut
    switch(dungeon.lowLayer[tileX][tileY - 1]) {
        case GROUND:
            dungeon.lowLayer[tileX][tileY - 1] = WALL_DOWN;
            break;
        case WALL_LEFT:
            dungeon.lowLayer[tileX][tileY - 1] = WALL_DOWN_LEFT;
            break;
        case WALL_RIGHT:
            dungeon.lowLayer[tileX][tileY - 1] = WALL_DOWN_RIGHT;
            break;
        case WALL_INNER_UP_LEFT:
            dungeon.lowLayer[tileX][tileY - 1] = WALL_DOWN;
            break;
        case WALL_INNER_UP_RIGHT:
            dungeon.lowLayer[tileX][tileY - 1] = WALL_DOWN;
            break;
    }

    // Côté bas
    switch(dungeon.lowLayer[tileX][tileY + 1]) {
        case GROUND:
            dungeon.lowLayer[tileX][tileY + 1] = WALL_UP;
            break;
        case WALL_LEFT:
            dungeon.lowLayer[tileX][tileY + 1] = WALL_UP_LEFT;
            break;
        case WALL_RIGHT:
            dungeon.lowLayer[tileX][tileY + 1] = WALL_UP_RIGHT;
            break;
        case WALL_INNER_DOWN_RIGHT:
            dungeon.lowLayer[tileX][tileY + 1] = WALL_UP;
            break;
        case WALL_INNER_DOWN_LEFT:
            dungeon.lowLayer[tileX][tileY + 1] = WALL_UP;
            break;
    }

    switch(dungeon.lowLayer[tileX - 1][tileY - 1]) {
        case GROUND:
            dungeon.lowLayer[tileX - 1][tileY - 1] = WALL_INNER_UP_LEFT;
            break;
    }

    switch(dungeon.lowLayer[tileX - 1][tileY + 1]) {
        case GROUND:
            dungeon.lowLayer[tileX - 1][tileY + 1] = WALL_INNER_DOWN_LEFT;
            break;
    }

    switch(dungeon.lowLayer[tileX + 1][tileY - 1]) {
        case GROUND:
            dungeon.lowLayer[tileX + 1][tileY - 1] = WALL_INNER_UP_RIGHT;
            break;
    }

    switch(dungeon.lowLayer[tileX + 1][tileY + 1]) {
        case GROUND:
            dungeon.lowLayer[tileX + 1][tileY + 1] = WALL_INNER_DOWN_RIGHT;
            break;
    }
}

// Initialize dungeon
void initDungeon(void) {
    int i, j;

    for(i = 0 ; i < DUNGEON_MAX_Y ; i++) {
        for(j = 0 ; j < DUNGEON_MAX_Y ; j++) {
            dungeon.lowLayer[j][i] = CEILING;
            dungeon.highLayer[j][i] = 0;
            dungeon.eventLayer[j][i] = 0;
            dungeon.currentLayer = 0;
        }
    }
}
