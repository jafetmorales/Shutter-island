#include "../../include/boids2D/Wolf.hpp"
#include "../../include/boids2D/BoidType.hpp"

Wolf::Wolf(glm::vec3 location, glm::vec3 landmarkPosition, MovableParametersPtr parameters) 
	: Wolf(location, landmarkPosition, glm::vec3(0,0,0), parameters)
{

}

Wolf::Wolf(glm::vec3 location, glm::vec3 landmarkPosition, glm::vec3 velocity, MovableParametersPtr parameters) 
	: Wolf(location, landmarkPosition, velocity, 0.05f, parameters)
{

}

Wolf::Wolf(glm::vec3 location, glm::vec3 landmarkPosition, glm::vec3 velocity, float mass,
    MovableParametersPtr parameters)
	: MovableBoid(location, landmarkPosition, velocity, mass, WOLF, parameters, 3)
{

}
