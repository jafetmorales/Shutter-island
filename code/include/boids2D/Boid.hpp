#ifndef BOID_HPP
#define BOID_HPP

#include <glm/glm.hpp>
#include <memory>

#include <vector>
#include "TypeBoid.hpp"

class Boid
{
 public:
	Boid(glm::vec3 position, TypeBoid t);

	glm::vec3 getLocation();

	void setLocation(glm::vec3 newLocation);

	bool isMovable();

	float getDistanceMin();

	float getAngle();

	void setAngle(float angle);

 private:
 	glm::vec3 m_location;
 	float m_angle;
 	TypeBoid m_typeBoid;
 	bool m_movable;
 	float m_distanceMin = 1;
};

typedef std::shared_ptr<Boid> BoidPtr;

#endif