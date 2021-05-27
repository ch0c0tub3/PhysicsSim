#ifndef PS_LIGHT_SOURCE_PROTOTYPE
#define PS_LIGHT_SOURCE_PROTOTYPE

#include "glm/vec3.hpp"
#include "render/shader.hpp"

class psLightSource {

protected:

	glm::vec3 m_source;
	glm::vec3 m_tint;
	float m_power;
	//glm::vec3 m_factor;

public:

	psLightSource(const glm::vec3 &pos,const glm::vec3 &rgb, const float &intensity) : m_power(intensity), m_source(pos), m_tint(rgb) {

		//m_factor = glm::vec3(1.f, 0.f, 0.f);
	}

	void createUniforms(psShader &shader);

	void setPos(const float &_x,const float &_y,const float &_z);

	void setRGB(const float &r,const float &g,const float &b);

	void setIntensity(const float &intensity);

	void bind(psShader &shader);

};

#endif