#pragma once
#include "Particle.h"

namespace l2qr {

class Swarm
{
public:
	const static int NPARTICLES = 5000;
	Particle* m_pParticles;
public:
	Swarm();
	~Swarm();

	const Particle* const getParticles() { return m_pParticles; };
};
}/* namespace l2qr */