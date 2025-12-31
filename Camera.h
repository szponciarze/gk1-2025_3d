#pragma once
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

class Camera {
private:
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;
public:
	Camera();
	void setPostion(const glm::vec3& p);
	void setTarget(const glm::vec3& t);
	void move(const glm::vec3& delta);
	glm::mat4 getViewMatrix() const;
};