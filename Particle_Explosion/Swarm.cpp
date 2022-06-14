#include "Swarm.h"
namespace l2qr {

Swarm::Swarm()
{
	m_pParticles = new Particle[NPARTICLES];
}

Swarm::~Swarm()
{
	delete[] m_pParticles;
}
}/* namespace l2qr */