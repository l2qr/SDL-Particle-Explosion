#pragma once
#include "Particle.h"

namespace l2qr {

class Swarm
{
public:
	const static int NPARTICLES = 7500;
private:
	Particle* m_pParticles;
	Uint64 lastTime;
public:
	Swarm();
	virtual ~Swarm();
	void update(Uint64 elapsed);

	const Particle* const getParticles() { return m_pParticles; };
};
}/* namespace l2qr */