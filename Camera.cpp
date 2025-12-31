#include "Camera.h"

Camera::Camera():position(0,0,10),target(0,0,0),up(0,1,0){}

void Camera::setPostion(const glm::vec3& p) {
	position = p;
}
void Camera::setTarget(const glm::vec3& t) {
	target = t;
}
void Camera::move(const glm::vec3& delta) {
	position += delta;
	target += delta;
}

glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(position, target, up);
}