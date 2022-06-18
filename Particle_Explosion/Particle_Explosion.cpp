// Particle_Explosion.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdlib.h>
#include <iostream>
#include <math.h>
#define SDL_MAIN_HANDLED
#include "Screen.h"
#include "Swarm.h"
#include "Particle_Explosion.h"

using namespace std;
using namespace l2qr;

int main()
{
    srand(time(NULL));

    Screen screen;

    if (screen.init() == false) {
        cout << "Error initialising SDL." << endl;
    }
    
    Swarm swarm;
    
    int halfScreenWidth = Screen::SCREEN_WIDTH / 2;
    int halfScreenHeight = Screen::SCREEN_HEIGHT / 2;
    
    while (true) {
        Uint64 elapsed = SDL_GetTicks64();

        swarm.update(elapsed);
        
        unsigned char red = (1 + (sin(elapsed * 0.000215))) * 112;
        unsigned char green = (1 + (sin(elapsed * 0.000205))) * 112;
        unsigned char blue = (1 + (sin(elapsed * 0.00033))) * 112;

        const Particle * const pParticles = swarm.getParticles();

        for (int i = 0; i < Swarm::NPARTICLES; i++) {
            Particle p = pParticles[i];
            
            int x = (p.m_x + 1) * halfScreenWidth;
            int y = p.m_y * halfScreenWidth + halfScreenHeight;
            
            double distanceFactor = hypot(p.m_x, p.m_y) / sqrt(2);

            unsigned char redD = red + ((255 - red) * (distanceFactor * Particle::getRandomInRange(0.1, 0.4)));
            unsigned char greenD = green - (green * (distanceFactor * Particle::getRandomInRange(0, 0.1)));
            unsigned char blueD = blue + ((255 - blue) * (distanceFactor * Particle::getRandomInRange(0.1, 0.2)));

            screen.setPixel(x, y, redD, greenD, blueD);

        }

        screen.boxBlur();

        // Update render
		screen.update();

        if (screen.processEvents() == false) break;
    }

    screen.close();
    return 0;
}