#pragma once
#include "DrawableObject.h"
#include "TransformableObject.h"
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

class ShapeObject : public DrawableObject,TransformableObject  {
protected:
	glm::mat4 modelMatrix;

public:
	ShapeObject(): modelMatrix(1.0f){}
	virtual ~ShapeObject() = default;
	virtual void translate(const glm::vec3& translation) override {
		modelMatrix = glm::translate(modelMatrix, translation);
	}
	virtual void rotate(float angle, const glm::vec3& axis) override {
		modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), axis);
	}
	virtual void scale(const glm::vec3& scale) override {
		modelMatrix = glm::scale(modelMatrix, scale);
	}
};