#include "psLightSource.h"

void psLightSource::setPos(float _x, float _y, float _z) {

	m_source.x = _x;
	m_source.y = _y;
	m_source.z = _z;
}

void psLightSource::setRGB(float r, float g, float b) {

	m_tint.x = r;
	m_tint.y = g;
	m_tint.z = b;
}

void psLightSource::setIntensity(float intensity) {

	m_power = intensity;
}

void psLightSource::bind(psShader &shader) {

	shader.setUniform("light_pos", m_source);
	shader.setUniform("light_tint", m_tint);
	shader.setUniform("light_power", m_power);
}