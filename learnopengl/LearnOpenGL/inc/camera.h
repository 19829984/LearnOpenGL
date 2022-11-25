#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

enum class Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Defaults
const float YAW = -90.f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
public:
	//Camera Attributes
	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 world_up;

	float yaw;
	float pitch;

	float mov_speed;
	float mouse_sens;
	float zoom;

	Camera(glm::vec3 _pos = glm::vec3(0, 0, 0), glm::vec3 _up = glm::vec3(0, 1, 0), float _yaw = YAW, float _pitch = PITCH) :
		front(glm::vec3(0, 0, -1)), mov_speed(SPEED), mouse_sens(SENSITIVITY), zoom(ZOOM) {
		pos = _pos;
		world_up = _up;
		yaw = _yaw;
		pitch = _pitch;

		updateCameraVectors();
	}

	glm::mat4 GetViewMatrix() {
		return glm::lookAt(pos, pos + front, up);
	}

	void ProcessKeyboard(Camera_Movement dir, float deltaTime) {
		float velocity = mov_speed * deltaTime;
		switch (dir)
		{
		case Camera_Movement::FORWARD:
			pos += front * velocity;
			break;
		case Camera_Movement::BACKWARD:
			pos -= front * velocity;
			break;
		case Camera_Movement::LEFT:
			pos -= right * velocity;
			break;
		case Camera_Movement::RIGHT:
			pos += right * velocity;
			break;
		default:
			break;
		}
	}

	void ProcessMouseMovement(float deltaX, float deltaY, GLboolean contrainPitch = true) {
		yaw += mouse_sens * deltaX;
		pitch += mouse_sens * deltaY;

		if (contrainPitch) {
			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;
		}

		updateCameraVectors();
	}

	void ProcessMouseScroll(float yoffset) {
		zoom -= yoffset;
		if (zoom < 1.f) zoom = 1.f;
		if (zoom > 45.f) zoom = 45.f;
	}
private:
	void updateCameraVectors() {
		glm::vec3 dir;
		dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		dir.y = sin(glm::radians(pitch));
		dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(dir);

		right = glm::normalize(glm::cross(front, world_up));
		up = glm::normalize(glm::cross(right, front));
	}
};

#endif