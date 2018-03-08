#include <glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "move.h"

using namespace glm;

Modelo::Modelo(GLFWwindow* window) : window(window) {
    position = glm::vec3(0, 0, 5);
    horizontalAngle = 3.14f;
    verticalAngle = 0.0f;
    FoV = 45.0f;
    speed = 0.2f;
    mouseSpeed = 0.001f;
    fovSpeed = 2.0f;
	unbind = false;
	afe = 0.0f;
}

void Modelo::update() {
    // glfwGetTime is called only once, the first time this function is called
    static double lastTime = glfwGetTime();

    // Compute time difference between current and last frame
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    // Get mouse position
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    // Reset mouse position for next frame
    glfwSetCursorPos(window, width / 2, height / 2);


    // Compute new horizontal and vertical angles, given windows size
    // and cursor position

    horizontalAngle += mouseSpeed * float(width / 2 - xPos);
    verticalAngle += mouseSpeed * float(height / 2 - yPos);
	// KANE CLAMP OTAN H KAMERA EINAI BINDED STO MONTELO
	if (unbind == false) {
	//	horizontalAngle = clamp(horizontalAngle, 3.14f - 0.4f, 3.14f + 0.4f);
	//	verticalAngle = clamp(verticalAngle, -3.14f / 3.0f, 3.14f / 3.0f);
	}
    // right and up vectors of the camera coordinate system
    // use spherical coordinates
	
    vec3 direction(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );

    // Right vector
    vec3 right(
        sin(horizontalAngle - 3.14f / 2.0f),
        0,
        cos(horizontalAngle - 3.14f / 2.0f)
    );
	
    // Up vector
    vec3 up = cross(right, direction);
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // Task 5.5: update camera position using the direction/right vectors
    // Move forward
	//GLFW_CROSSHAIR_CURSOR
	
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		if (unbind) {
			position += direction * deltaTime * speed;
			//aferw apto last position to y
			afe = position.y-0.22;
		}
		else {
			position += vec3(direction.x, 0, direction.z) * deltaTime * speed;
			position.y = position.y - afe;
			afe = 0.0;

		}
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		if (unbind) {
			position -= direction * deltaTime * speed;
			afe = position.y-0.22;
		}
		else {
			position -= vec3(direction.x, 0, direction.z) * deltaTime * speed;
			position.y = position.y - afe;
			afe = 0.0;

		}
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position += right * deltaTime * speed;
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position -= right * deltaTime * speed;
    }

    // Task 5.6: handle zoom in/out effects
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        FoV -= fovSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        FoV += fovSpeed;
    }
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		unbind = true;
	}
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		unbind = false;
	}
	    // Task 5.7: construct projection and view matrices
    //*/

    // Homework XX: perform orthographic projection

    // For the next frame, the "last time" will be "now"
    lastTime = currentTime;
}