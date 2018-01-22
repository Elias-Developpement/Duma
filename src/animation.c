#include "animation.h"

void drawAnimatedPlayer() {
    if(hero.frameTimer <= 0) {
        hero.frameTimer = ANIMATION_SPEED;
        hero.frameIndex++;

        switch(hero.index) {
            case DOWN:
                // BAS
                if(hero.frameIndex > 2) {
                    hero.frameIndex = 0;
                }
                break;
            case LEFT:
                if(hero.frameIndex > 5) {
                    hero.frameIndex = 3;
                }
                // GAUCHE
                break;
            case RIGHT:
                if(hero.frameIndex > 8) {
                    hero.frameIndex = 6;
                }
                // DROITE
                break;
            case UP:
                if(hero.frameIndex > 11) {
                    hero.frameIndex = 9;
                }
                // HAUT
                break;
        }
    }
    else {
        hero.frameTimer--;
    }

    displayCharacter();
}
