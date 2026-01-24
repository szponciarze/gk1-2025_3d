#pragma once
#include "DrawableObject.h"
#include "TransformableObject.h"
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
/**
 * @class ShapeObject
 * @brief Klasa reprezentuj¹ca obiekt dziedzicz¹ca po DrawableObject i TransformableObject.
 * 
 * Klasa ShapeObject implementuje metody do translacji, rotacji i skalowania obiektu.
 * 
 */
class ShapeObject : public DrawableObject,TransformableObject  {
protected:
	/** 
	 * @brief Macierz modelu obiektu.
	 * 
	 * Przechowuje transformacje obiektu w przestrzeni 3D.
	 */
	glm::mat4 modelMatrix;

public:
	/**
	 * @brief Konstruktor domyœlny.
	 *
	 * Inicjalizuje modelMatrix jako macierz jednostkow¹.
	 */	
	ShapeObject(): modelMatrix(1.0f){}
	/**
	 * @brief Wirtualny destruktor klasy ShapeObject.
	 */
	virtual ~ShapeObject() = default;
	/**
	 * @brief Implementacja metody translacji obiektu.
	 *
	 * Modyfikuje modelMatrix poprzez dodanie przesuniêcia.
	 * 
	 * @param translation Wektor okreœlaj¹cy przesuniêcie.
	 */
	virtual void translate(const glm::vec3& translation) override {
		modelMatrix = glm::translate(modelMatrix, translation);
	}
	/**
	 * @brief Implementacja metody rotacji obiektu.
	 *
	 * Modyfikuje modelMatrix poprzez dodanie rotacji.
	 * 
	 * @param angle K¹t rotacji w stopniach.
	 * @param axis Oœ rotacji jako wektor.
	 */
	virtual void rotate(float angle, const glm::vec3& axis) override {
		modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), axis);
	}
	/**
	 * @brief Implementacja metody skalowania obiektu.
	 *
	 * Modyfikuje modelMatrix poprzez dodanie skalowania.
	 * 
	 * @param scale Wektor okreœlaj¹cy skalê.
	 */
	virtual void scale(const glm::vec3& scale) override {
		modelMatrix = glm::scale(modelMatrix, scale);
	}
};