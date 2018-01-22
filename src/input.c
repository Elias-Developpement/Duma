#include "input.h"

void readInput(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type) {
        case SDL_QUIT:
            exit(1);
            break;
        case SDL_KEYDOWN:
            // Lorsque l'on enfonce une touche
            switch(event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    // Quitter le programme
                    exit(1);
                case SDLK_l:
                    // Charger une map
                    input.setLoad = 1;
                    break;
                case SDLK_s:
                    // Enregistrer une map
                    input.setSave = 1;
                    break;
                case SDLK_m:
                    // Sélectionne un event monstre
                    input.setMonster = 1;
                    break;
                case SDLK_d:
                    input.setDoor = 1;
                    break;
                case SDLK_i:
                    input.setSwitch = 1;
                    break;
                case SDLK_c:
                    input.setChest = 1;
                    break;
                case SDLK_b:
                    input.setBlock = 1;
                    break;
                case SDLK_k:
                    input.setKey = 1;
                    break;
                case SDLK_KP1:
                    input.setLowLayer = 1;
                    break;
                case SDLK_KP2:
                    input.setHighLayer = 1;
                    break;
                case SDLK_KP3:
                    input.setEventLayer = 1;
                    break;
                case SDLK_LCTRL:
                    input.setControl = 1;
                    break;
                case SDLK_DELETE:
                    input.setReset = 1;
                    break;
                case SDLK_UP:
                    input.setUp = 1;
                    if(game.edit == PLAY) {
                        hero.index = 9;
                        hero.frameIndex = 9;
                    }
                    break;
                case SDLK_DOWN:
                    input.setDown = 1;
                    if(game.edit == PLAY) {
                        hero.index = 0;
                        hero.frameIndex = 0;
                    }
                    break;
                case SDLK_LEFT:
                    input.setLeft = 1;
                    if(game.edit == PLAY) {
                        hero.index = 3;
                        hero.frameIndex = 3;
                    }
                    break;
                case SDLK_RIGHT:
                    input.setRight = 1;
                    if(game.edit == PLAY) {
                            hero.index = 6;
                        hero.frameIndex = 6;
                    }
                    break;
                case SDLK_TAB:
                    input.setGrid = 1;
                    break;
            }
            break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym) {
                case SDLK_LCTRL:
                    input.setControl = 0;
                    break;
                case SDLK_LEFT:
                    input.setLeft = 0;
                    break;
                case SDLK_RIGHT:
                    input.setRight = 0;
                    break;
                case SDLK_UP:
                    //printf("HERO_X : %d\n", hero.x / TILE_SIZE);
                    //printf("HERO_Y : %d\n", hero.y / TILE_SIZE);
                    input.setUp = 0;
                    break;
                case SDLK_DOWN:
                    input.setDown = 0;
                    break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            // Lorsque l'on appuis sur un bouton de la souris
            switch(event.button.button) {
                case SDL_BUTTON_LEFT:
                    input.setTile = 1;
                    break;
                case SDL_BUTTON_MIDDLE:
                    input.setCopy = 1;
                    break;
                case SDL_BUTTON_RIGHT:
                    input.setEmpty = 1;
                    break;
                case SDL_BUTTON_WHEELUP:
                    input.setNextTile = 1;
                    break;
                case SDL_BUTTON_WHEELDOWN:
                    input.setBackTile = 1;
                    break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            switch(event.button.button) {
                case SDL_BUTTON_LEFT:
                    input.setTile = 0;
                    break;
                case SDL_BUTTON_RIGHT:
                    input.setEmpty = 0;
                    break;
            }
            // Lorsque l'on relâche un bouton de la souris
            break;
        case SDL_MOUSEMOTION:
            //cursor.x = event.motion.x;
            //cursor.y = event.motion.y;

            //printf("POS_X : %d\n", cursor.tileX / TILE_SIZE);
            //printf("POS_Y : %d\n", cursor.tileY / TILE_SIZE);
            // Lorsque l'on déplace la souris
            break;
    }

    SDL_GetMouseState(&cursor.x, &cursor.y);

    switch(game.edit) {
        case DUNGEON_MAPPING:
            cursor.tileX;
            cursor.tileY;
            break;
    }
}

void update(void) {
    // Go to up
    if(input.setUp == 1) {
        switch(game.edit) {
        case DUNGEON_MAPPING:
            hero.y -= HERO_SPEED;
            if(hero.y < 0) {
                hero.y = 0;
            }
            centerOnPlayer();
            break;
        case PLAY:
            if(checkWall(UP) == COLLIDER_TRUE) {
                hero.y = hero.y - HERO_SPEED * clock.delta;
                centerOnPlayer();
            }
            else {
                printf("Collision\n");
            }
            break;
        }
    }
    // Go to down
    else if(input.setDown == 1) {
        switch(game.edit) {
            case DUNGEON_MAPPING:
                hero.y += HERO_SPEED;
                if(hero.y > DUNGEON_MAX_Y * TILE_MAX) {
                    hero.y = DUNGEON_MAX_Y * TILE_MAX;
                }
                printf("Position x (hero) : %d\n", hero.x / TILE_SIZE);
                printf("Position y (hero) : %d\n\n", hero.y / TILE_SIZE);
                printf("Valeur du carreau : %d\n\n", dungeon.lowLayer[hero.x / TILE_SIZE][(hero.y + TILE_SIZE) / TILE_SIZE]);
                centerOnPlayer();
                break;
            case PLAY:
                if(checkWall(DOWN) == COLLIDER_TRUE) {
                    hero.y = hero.y + HERO_SPEED * clock.delta;
                    centerOnPlayer();
                }
                else {
                    printf("Collision\n");
                }
                break;
        }
    }
    // Go to left
    else if(input.setLeft == 1) {
            switch(game.edit) {
                case DUNGEON_MAPPING:
                    hero.x -= HERO_SPEED;
                    if(hero.x < 0) {
                        hero.x = 0;
                    }
                    centerOnPlayer();
                    break;
                case PLAY:
                    if(checkWall(LEFT) == COLLIDER_TRUE) {
                        hero.x = hero.x - HERO_SPEED * clock.delta;
                        centerOnPlayer();
                    }
                    else {
                        printf("Collision\n");
                    }
                    break;
        }
    }
    // Go to right
    else if(input.setRight == 1) {
            switch(game.edit) {
                case DUNGEON_MAPPING:
                    hero.x += HERO_SPEED;
                    if(hero.x > DUNGEON_MAX_X * TILE_SIZE) {
                        hero.x = DUNGEON_MAX_X * TILE_SIZE;
                    }
                    centerOnPlayer();
                    break;
                case PLAY:
                    if(checkWall(RIGHT) == COLLIDER_TRUE) {
                        hero.x = hero.x + HERO_SPEED * clock.delta;
                        centerOnPlayer();
                    }
                    else {
                        printf("Collision\n");
                    }
                    break;
        }
    }

    if(input.setTile == 1) {
        switch(game.edit) {
            case DUNGEON_MAPPING:
                switch(dungeon.currentLayer) {
                    case LOWLAYER:
                        dungeon.lowLayer[((cursor.x + (camera.x % TILE_SIZE * -1)) / TILE_SIZE) + (camera.x / TILE_SIZE)][((cursor.y + (camera.x % TILE_SIZE * -1)) / TILE_SIZE) + (camera.y / TILE_SIZE)] = GROUND;
                        setWall((cursor.x / TILE_SIZE) + (camera.x / TILE_SIZE), (cursor.y / TILE_SIZE) + (camera.y / TILE_SIZE));
                        break;
                    case HIGHLAYER:
                        dungeon.lowLayer[(cursor.x / TILE_SIZE) + (camera.x / TILE_SIZE)][(cursor.y / TILE_SIZE) + (camera.y / TILE_SIZE)] = dungeon.tileIndex;
                        break;
                    case EVENTLAYER:
                        if(dungeon.eventIndex == START_POINT && dungeon.start == 0) {
                            dungeon.start = 1;
                            dungeon.lowLayer[(cursor.x / TILE_SIZE) + (camera.x / TILE_SIZE)][(cursor.y / TILE_SIZE) + (camera.y / TILE_SIZE)] = dungeon.eventIndex;
                        }
                        else if(dungeon.eventIndex != START_POINT) {
                            dungeon.lowLayer[(cursor.x / TILE_SIZE) + (camera.x / TILE_SIZE)][(cursor.y / TILE_SIZE) + (camera.y / TILE_SIZE)] = dungeon.eventIndex;
                        }
                        input.setTile = 0;
                        break;
                }
                break;
        }
    }
    else if(input.setEmpty == 1) {
        switch(game.edit) {
            case DUNGEON_MAPPING:
                switch(dungeon.currentLayer) {
                    case LOWLAYER:
                        dungeon.lowLayer[(cursor.x / TILE_SIZE) + (camera.x / TILE_SIZE)][(cursor.y / TILE_SIZE) + (camera.y / TILE_SIZE)] = CEILING;
                        ereaseWall((cursor.x / TILE_SIZE) + (camera.x / TILE_SIZE), (cursor.y / TILE_SIZE) + (camera.y / TILE_SIZE));
                        break;
                    case HIGHLAYER:
                        dungeon.lowLayer[(cursor.x / TILE_SIZE) + (camera.x / TILE_SIZE)][(cursor.y / TILE_SIZE) + (camera.y / TILE_SIZE)] = EMPTY;
                        break;
                    case EVENTLAYER:
                        if(dungeon.lowLayer[(cursor.x / TILE_SIZE) + (camera.x / TILE_SIZE)][(cursor.y / TILE_SIZE) + (camera.y / TILE_SIZE)] == START_POINT) {
                            dungeon.start = 0;
                        }
                        dungeon.lowLayer[(cursor.x / TILE_SIZE) + (camera.x / TILE_SIZE)][(cursor.y / TILE_SIZE) + (camera.y / TILE_SIZE)] = EMPTY;
                        input.setEmpty = 0;
                        break;
                }
                break;
        }
    }

    if(input.setCopy == 1) {
        if(game.edit == DUNGEON_MAPPING) {
            switch(dungeon.currentLayer) {
                case LOWLAYER:
                    dungeon.tileIndex = dungeon.lowLayer[(cursor.x / TILE_SIZE) + camera.x][(cursor.y / TILE_SIZE) + camera.y];
                    break;
                case HIGHLAYER:
                    dungeon.tileIndex = dungeon.highLayer[(cursor.x / TILE_SIZE) + camera.x][(cursor.y / TILE_SIZE) + camera.y];
                    break;
                case EVENTLAYER:
                    dungeon.eventIndex = dungeon.eventLayer[(cursor.x / TILE_SIZE) + camera.x][(cursor.y / TILE_SIZE) + camera.y];
                    break;
            }
        }
        input.setCopy = 0;
    }

    if(input.setNextTile == 1) {
        if(dungeon.currentLayer == LOWLAYER || dungeon.currentLayer == HIGHLAYER) {
            dungeon.tileIndex++;

            if(dungeon.tileIndex > (tileset.width) * (tileset.height / 32)) {
                dungeon.tileIndex = 0;
            }
        }
        else if(dungeon.currentLayer == EVENTLAYER) {
            dungeon.eventIndex++;

            if(dungeon.eventIndex > 1) {
                dungeon.eventIndex = 0;
            }
        }
        input.setNextTile = 0;
    }
    else if(input.setBackTile == 1) {
        if(dungeon.currentLayer == LOWLAYER || dungeon.currentLayer == HIGHLAYER) {
            dungeon.tileIndex--;

            if(dungeon.tileIndex < 0) {
                dungeon.tileIndex = (tileset.width) * (tileset.height / 32);
            }
        }
        else if(dungeon.currentLayer == EVENTLAYER) {
            dungeon.eventIndex--;

            if(dungeon.eventIndex < 0) {
                dungeon.eventIndex = 1;
            }
        }
        input.setBackTile = 0;
    }

    if(input.setLowLayer == 1) {
        if(game.edit == DUNGEON_MAPPING) {
            dungeon.currentLayer = LOWLAYER;
        }

        input.setLowLayer = 0;
    }
    else if(input.setHighLayer == 1) {
        if(game.edit == DUNGEON_MAPPING) {
            dungeon.currentLayer = HIGHLAYER;
        }

        input.setHighLayer = 0;
    }
    else if(input.setEventLayer == 1) {
        if(game.edit == DUNGEON_MAPPING) {
            dungeon.currentLayer = EVENTLAYER;
        }

        input.setEventLayer = 0;
    }

    if(input.setGrid == 1) {
        switch(game.showGrid) {
            case 0:
                game.showGrid = 1;
                break;
            case 1:
                game.showGrid = 0;
                break;
        }
        input.setGrid = 0;
    }

    if(input.setReset == 1) {
        switch(game.edit) {
            case DUNGEON_MAPPING:
                initDungeon();
                break;
        }

        input.setReset = 0;
    }

    // Add door (or try dmg)
    if(input.setDoor == 1) {
        switch(game.edit) {
            case PLAY:
                if(hero.life > 0) {
                    hero.life -= 2;
                    if(hero.life < 0) {
                        hero.life = 0;
                    }
                }

                if(hero.mana > 0) {
                    hero.mana -= 4;
                    if(hero.mana < 0) {
                        hero.mana = 0;
                    }
                }

                hero.key++;
                break;
        }

        input.setDoor = 0;
    }

    if(input.setBlock == 1) {
        switch(game.edit) {
        case PLAY:
            if(hero.life < 10) {
                hero.life += 10;
                if(hero.life > 10) {
                    hero.life = 10;
                }
            }

            if(hero.mana < 10) {
                hero.mana += 2;
                if(hero.mana > 10) {
                    hero.mana = 10;
                }
            }

            hero.key--;
            break;
        }

        input.setBlock = 0;
    }

    if(input.setKey == 1) {
        //printf("Position X (camera) : %d\n", camera.x);
        //printf("Position Y (camera) : %d\n\n", camera.y);

        //printf("Position X (hero) : %d\n", hero.x);
        //printf("Position Y (hero) : %d\n\n", hero.y);

        //printf("Position X (map) : %d\n", camera.x / TILE_SIZE);
        //printf("Position Y (map) : %d\n", camera.y / TILE_SIZE);
        //printf("Reste X (map) : %d\n", (camera.y % TILE_SIZE) * -1);
        //printf("Reste Y (map) : %d\n\n", (camera.y % TILE_SIZE) * -1);

        input.setKey = 0;
    }

    if(input.setControl == 1) {
        // Changer de mode d'édition
        switch(game.edit) {
            case DUNGEON_MAPPING:
                printf("Jeu en cours\n");
                setWindow("Duma - Jeu en cours", WINDOWS_X, WINDOWS_Y);
                SDL_ShowCursor(1);
                //printf("posX : %d\n", hero.x);
                //printf("posY : %d\n\n", hero.x);
                //printf("dungX : %d\n", camera.x);
                //printf("dungY : %d\n\n", camera.y);
                game.edit = PLAY;
                break;
            case PLAY:
                hero.index = 0;
                setWindow("Duma - Edition en cours", WINDOWS_X, WINDOWS_Y);
                printf("Edition en cours\n");
                SDL_ShowCursor(1);
                game.edit = DUNGEON_MAPPING;
                break;
        }

        input.setControl = 0;
    }

    if(input.setLoad == 1) {
        switch(game.edit) {
            case DUNGEON_MAPPING:
                loadDungeon();
                break;
        }
        input.setLoad = 0;
    }

    if(input.setSave == 1) {
        switch(game.edit) {
            case DUNGEON_MAPPING:
                saveDungeon();
                break;
        }

        input.setSave = 0;
    }

    // Vitesse du scrolling
    if(input.setLeft == 1 || input.setUp == 1 || input.setDown == 1 || input.setRight == 1) {
        switch(game.edit) {
            case DUNGEON_MAPPING:
                SDL_Delay(10);
                break;
            case PLAY:
                SDL_Delay(10);
                break;
        }
    }
}
