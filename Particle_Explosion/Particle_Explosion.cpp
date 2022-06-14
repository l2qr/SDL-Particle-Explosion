// Particle_Explosion.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdlib.h>
#include <iostream>
#include <math.h>
#define SDL_MAIN_HANDLED
#include "Screen.h"
#include "Swarm.h"

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

	// Check for messages/events
    while (true) {
		// Update particles
        
        // Draw particles
        Uint64 elapsed = SDL_GetTicks64();

        /*unsigned char red = (1 + sin(elapsed * 0.001)) * 128;
        unsigned char green = (1 + sin(elapsed * 0.0003)) * 128;
        unsigned char blue = (1 + sin(elapsed * 0.0017)) * 128;

        for (int y = 0; y < Screen::SCREEN_HEIGHT; y++) {
            for (int x = 0; x < Screen::SCREEN_WIDTH; x++) {
                screen.setPixel(x, y, red, green, blue);
            }
        }*/
        const Particle * const pParticles = swarm.getParticles();

        for (int i = 0; i < Swarm::NPARTICLES; i++) {
            Particle p = pParticles[i];

            int x = (p.m_x + 1) * Screen::SCREEN_WIDTH / 2;
            int y = (p.m_y + 1) * Screen::SCREEN_HEIGHT / 2;
        }

        // Update render
		screen.update();

        if (screen.processEvents() == false) break;
    }

    screen.close();
    return 0;
}






// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
