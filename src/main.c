#include "main.h"

int main(int argc, char *argv[])
{
    // To let the console
    freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stderr);

    // Frame rate limitation
    unsigned int frameLimit = SDL_GetTicks() + 16;
    int isRunning = 1;

    // Initialisation
    init("Alena Studio - Dungeon Maker");

    loadGame();

    // Call at the exit of the program
    atexit(cleanup);

    // Main loop
    while(isRunning == 1) {
        // Read all inputs
        readInput();

        // Refresh data
        update();

        // Draw graphics elements
        draw();

        setDelta();
        delay(1);
    }
    exit(0);
}

void setDelta(void) {
    float now = SDL_GetTicks();

    if(now > clock.last_tick) {
        clock.delta = (float)((now - clock.last_tick) / 100);
        clock.last_tick = now;
        //printf("FPS : %f\n", clock.delta);
    }
}
