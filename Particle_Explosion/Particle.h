#pragma once

namespace l2qr {

struct Particle
{
	double m_x;
	double m_y;
private:
	double m_speed;
	double m_deg;

public:
	Particle();
	virtual ~Particle();
	void update(Uint64 interval);
	double getSpeed();
	double static getRandomInRange(double min, double max);
private:
	void init();
};

}/* namespace l2qr */