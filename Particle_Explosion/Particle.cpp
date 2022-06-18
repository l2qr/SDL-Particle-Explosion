#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <SDL.h>
#include "Particle.h"

namespace l2qr {

	Particle::Particle()
{
		init();
}

Particle::~Particle(){
}

void Particle::update(Uint64 interval)
{
	if ((double)rand() < RAND_MAX / 2500) {
		init();
	}

	double x_speed = m_speed * cos(m_deg);
	double y_speed = m_speed * sin(m_deg);

	m_x += x_speed * interval;
	m_y += y_speed * interval;

	
	if (m_x <= -1.0 || m_x >= 1.0 || m_y <= -1.0 || m_y >= 1.0) {
		init();
	}
	
	double centerDistance = (sqrt(2) - hypot(m_x, m_y)) / sqrt(2);
	double tmp_deg = interval * ((getRandomInRange(1.30, 2) * m_speed)  * (getRandomInRange(3.2, 3.7))  * centerDistance);
	m_deg += getRandomInRange(0.0, 1) < 0.5 ? tmp_deg : -tmp_deg;
}

double Particle::getSpeed()
{
	return m_speed;
}

double Particle::getRandomInRange(double min, double max)
{
	return ((double)rand() / (RAND_MAX + 1))* (max - min + 1) + min;
}

void Particle::init() {
	m_x = 0.0;
	m_y = 0.0;
	m_deg = 2 * M_PI * getRandomInRange(0, 1);
	m_speed = 0.03 * getRandomInRange(0, 1);
	m_speed *= m_speed;
}

}/* namespace l2qr */