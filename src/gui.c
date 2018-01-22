#include "gui.h"

void drawGui(void) {
    int i, j, currentLife, currentMana;
    SDL_Rect positionHealth, positionMana, positionHealthBar, positionManaBar, positionKey, positionObject;

    currentLife = (int)(175 * hero.life / 10);
    currentMana = (int)(175 * hero.mana / 10);

    positionHealthBar.x = 20;
    positionHealthBar.y = 20;
    positionManaBar.x = 20;
    positionManaBar.y = 50;
    positionKey.x = WINDOWS_X - ui.key->w - 20;
    positionKey.y = WINDOWS_Y - ui.key->h - 20;
    positionObject.x = WINDOWS_X - ui.object->w - 20;
    positionObject.y = 20;

    // Display bar container
    SDL_BlitSurface(ui.healthBar, NULL, game.screen, &positionHealthBar);
    SDL_BlitSurface(ui.manaBar, NULL, game.screen, &positionManaBar);

    for(i = 0 ; i < currentLife ; i++) {
        positionHealth.x = positionHealthBar.x + 34 + ((ui.healthBar->h - ui.health->h) / 2) + i;
        positionHealth.y = 20 + ((ui.healthBar->h - ui.health->h) / 2);
        SDL_BlitSurface(ui.health, NULL, game.screen, &positionHealth);
    }

    for(j = 0 ; j < currentMana ; j++) {
        positionMana.x = positionManaBar.x + 34 + ((ui.manaBar->h - ui.mana->h) / 2) + j;
        positionMana.y = 50 + ((ui.manaBar->h - ui.mana->h) / 2);
        SDL_BlitSurface(ui.mana, NULL, game.screen, &positionMana);
    }

    SDL_BlitSurface(ui.key, NULL, game.screen, &positionKey);
    SDL_BlitSurface(ui.object, NULL, game.screen, &positionObject);
}

void keyManager(void) {
    // Function to display the key owned by the player
}

void displayCursor(void) {
    int x, y;

    // Calculate the x and y position of the cursor
    x = (((cursor.x + ((camera.x % TILE_SIZE) * 1)) / TILE_SIZE * TILE_SIZE) - (camera.x % TILE_SIZE));
    y = (((cursor.y + ((camera.y % TILE_SIZE) * 1)) / TILE_SIZE * TILE_SIZE) - (camera.y % TILE_SIZE));

    drawImage(cursor.skin, x, y);
}

void displayDebug(void) {
    SDL_Rect positionCollider;
    switch(hero.index) {
        case UP:
            ui.collision = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 16, 32, 0, 0, 0, 0);

            positionCollider.x = (WINDOWS_X / 2) - (hero.charset->w / 2 / 3) + (TILE_SIZE / 2);
            positionCollider.y = (WINDOWS_Y / 2) - (hero.charset->h / 2 / 4);

            SDL_SetAlpha(ui.collision, SDL_SRCALPHA, 255);
            SDL_FillRect(ui.collision, NULL, SDL_MapRGB(game.screen->format, 255, 0, 0));
            SDL_BlitSurface(ui.collision, NULL, game.screen, &positionCollider);
            break;
        case DOWN:
            ui.collision = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 16, 32, 0, 0, 0, 0);

            positionCollider.x = (WINDOWS_X / 2) - (hero.charset->w / 2 / 3) + (TILE_SIZE / 2);
            positionCollider.y = (WINDOWS_Y / 2) - (hero.charset->h / 2 / 4) + TILE_SIZE;

            SDL_SetAlpha(ui.collision, SDL_SRCALPHA, 255);
            SDL_FillRect(ui.collision, NULL, SDL_MapRGB(game.screen->format, 255, 0, 0));
            SDL_BlitSurface(ui.collision, NULL, game.screen, &positionCollider);
            break;
        case LEFT:
            ui.collision = SDL_CreateRGBSurface(SDL_HWSURFACE, 16, 1, 32, 0, 0, 0, 0);

            positionCollider.x = (WINDOWS_X / 2) - (hero.charset->w / 2 / 3) - (TILE_SIZE / 2);
            positionCollider.y = (WINDOWS_Y / 2) - (hero.charset->h / 2 / 4) + TILE_SIZE;

            SDL_SetAlpha(ui.collision, SDL_SRCALPHA, 255);
            SDL_FillRect(ui.collision, NULL, SDL_MapRGB(game.screen->format, 255, 0, 0));
            SDL_BlitSurface(ui.collision, NULL, game.screen, &positionCollider);
            break;
        case RIGHT:
            ui.collision = SDL_CreateRGBSurface(SDL_HWSURFACE, 16, 1, 32, 0, 0, 0, 0);

            positionCollider.x = (WINDOWS_X / 2) - (hero.charset->w / 2 / 3) - (TILE_SIZE / 2);
            positionCollider.y = (WINDOWS_Y / 2) - (hero.charset->h / 2 / 4) + TILE_SIZE;

            SDL_SetAlpha(ui.collision, SDL_SRCALPHA, 255);
            SDL_FillRect(ui.collision, NULL, SDL_MapRGB(game.screen->format, 255, 0, 0));
            SDL_BlitSurface(ui.collision, NULL, game.screen, &positionCollider);
            break;
    }
}
