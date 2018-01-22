#include "init.h"

void init(char *title) {
    // Charger le module SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("La SDL n'a pas pu être initialisee : %s\n", SDL_GetError());
        exit(1);
    }

    // Chargement du module PNG de SDL Image
    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        exit(1);
    }

    // Charger le module de texte
    if(TTF_Init() < 0) {
        printf("Le module d'ecriture n'a pas pu etre initialise !\n");
        exit(1);
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0) {
        exit(1);
    }

    // On définit notre fenêtre principale
    game.screen = SDL_SetVideoMode(WINDOWS_X, WINDOWS_Y, 32, SDL_HWSURFACE);

    if(game.screen == NULL) {
        printf("Erreur lors de l'initialisation de l'ecran !\n");
        exit(1);
    }

    SDL_WM_SetCaption(title, NULL);
    SDL_WM_SetIcon(IMG_Load("Logo.png"), NULL);
}

void setWindow(char *title, int w, int h) {
    game.screen = SDL_SetVideoMode(w, h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    if(game.screen == NULL) {
        exit(1);
    }

    SDL_WM_SetCaption(title, NULL);
}

// Game loading
void loadGame(void) {
    int i, j;

    // Set up the grid
    for(i = 0 ; i < WINDOWS_X / TILE_MAX ; i++) {
        game.gridX[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, WINDOWS_Y, 32, 0, 0, 0, 0);
    }

    for(j = 0 ; j < WINDOWS_Y / TILE_MAX ; j++) {
        game.gridY[j] = SDL_CreateRGBSurface(SDL_HWSURFACE, WINDOWS_X, 1, 32, 0, 0, 0, 0);
    }

    // Camera settings
    camera.width = WINDOWS_X;
    camera.height = WINDOWS_Y;
    camera.x = 0;
    camera.y = 0;

    // Hero settings
    hero.life = 10;
    hero.mana = 10;
    hero.key = 0;
    hero.speed = 0.8;

    // Set up clock
    clock.delta = 0.0;
    clock.last_tick = 0;
    clock.last_fps = 0;

    // Load all elements needed to make the game work
    hero.charset = loadImage("data/img/player.png");
    cursor.skin = loadImage("data/img/cursor.png");
    ui.healthBar = loadImage("data/img/health_bar.png");
    ui.manaBar = loadImage("data/img/mana_bar.png");
    ui.health = loadImage("data/img/health.png");
    ui.mana = loadImage("data/img/mana.png");
    ui.key = loadImage("data/img/key.png");
    ui.object = loadImage("data/img/object.png");

    // Game settings
    game.edit = DUNGEON_MAPPING;
    loadDungeon();

    // Sound settings
    game.music = Mix_LoadMUS("music.wav");
    Mix_VolumeMusic(MIX_MAX_VOLUME / 8);
    //Mix_PlayMusic(game.music, -1);

    dungeon.arial = TTF_OpenFont("arial.ttf", 11);

}

// Clean up all resources at exit
void cleanup(void) {
    int i, j;

    for(i = 0 ; i < WINDOWS_X / TILE_MAX ; i++) {
        SDL_FreeSurface(game.gridX[i]);
    }

    for(j = 0 ; j < WINDOWS_Y / TILE_MAX ; j++) {
        SDL_FreeSurface(game.gridY[j]);
    }

    if(tileset.fileName != NULL) {
        SDL_FreeSurface(tileset.fileName);
    }
    if(dungeon.tileset != NULL) {
        SDL_FreeSurface(dungeon.tileset);
    }
    if(dungeon.font != NULL) {
        SDL_FreeSurface(dungeon.font);
    }
    if(hero.charset != NULL) {
        SDL_FreeSurface(hero.charset);
    }
    if(ui.health != NULL) {
        SDL_FreeSurface(ui.health);
    }
    if(ui.healthBar != NULL) {
        SDL_FreeSurface(ui.healthBar);
    }
    if(ui.mana != NULL) {
        SDL_FreeSurface(ui.mana);
    }
    if(ui.manaBar != NULL) {
        SDL_FreeSurface(ui.manaBar);
    }
    if(ui.key != NULL) {
        SDL_FreeSurface(ui.key);
    }
    if(ui.object != NULL) {
        SDL_FreeSurface(ui.object);
    }
    if(ui.collision != NULL) {
        SDL_FreeSurface(ui.collision);
    }

    Mix_FreeMusic(game.music);
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}
