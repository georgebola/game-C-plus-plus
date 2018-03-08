#ifndef Modelo_HPP
#define Modelo_HPP

#include <glm/glm.hpp>

class Modelo {
public:
    GLFWwindow* window;
	bool unbind;
    // Initial position : on +Z
    glm::vec3 position;
	glm::vec3 direction;

    // Initial horizontal angle : toward -Z
    float horizontalAngle;
    // Initial vertical angle : none
    float verticalAngle;
    // Field of View
    float FoV;
	float afe;
    float speed; // units / second
    float mouseSpeed;
    float fovSpeed;

	Modelo(GLFWwindow* window);

    void update();
};

#endif