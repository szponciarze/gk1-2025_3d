#pragma once
#include "GameObject.h"
#include <glm/glm/glm.hpp>

class TransformableObject : public virtual GameObject {
public:
	virtual ~TransformableObject() = default;
	virtual void translate(const glm::vec3& translation) = 0;
	virtual void rotate(float angle, const glm::vec3& axis) = 0;
	virtual void scale(const glm::vec3& scale) = 0;
};