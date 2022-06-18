#include <SDL.h>
#include "Swarm.h"

namespace l2qr {

Swarm::Swarm() : lastTime(0)
{
	m_pParticles = new Particle[NPARTICLES];
}

Swarm::~Swarm()
{
	delete[] m_pParticles;
}
void Swarm::update(Uint64 elapsed)
{
	Uint64 interval = elapsed - lastTime;

	for (int i = 0; i < NPARTICLES; i++) {
		m_pParticles[i].update(interval);
	}
	lastTime = elapsed;
}
}/* namespace l2qr */