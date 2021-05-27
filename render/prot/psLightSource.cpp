#include "psLightSource.h"

void psLightSource::createUniforms(psShader &shader) {

	shader.buildUniform("light_pos");
	shader.buildUniform("light_tint");
	shader.buildUniform("light_power");
}

void psLightSource::setPos(const float &_x,const float &_y,const float &_z) {

	m_source.x = _x;
	m_source.y = _y;
	m_source.z = _z;
}

void psLightSource::setRGB(const float &r,const float &g,const float &b) {

	m_tint.x = r;
	m_tint.y = g;
	m_tint.z = b;
}

void psLightSource::setIntensity(const float &intensity) {

	m_power = intensity;
}

void psLightSource::bind(psShader &shader) {

	shader.setUniform("light_pos", m_source);
	shader.setUniform("light_tint", m_tint);
	shader.setUniform("light_power", m_power);
}