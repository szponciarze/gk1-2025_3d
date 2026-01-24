#pragma once
#include "GameObject.h"
#include <glm/glm/glm.hpp>
/**
 * @brief Abstrakcyjna klasa bazowa dla obiektów mo¿liwych do transformacji.
 *
 * TransformableObject rozszerza GameObject o interfejs transformacji przestrzennej.
 * 
 */
class TransformableObject : public virtual GameObject {
public:
	/**
	 * @brief Wirtualny destruktor klasy TransformableObject.
	*/
	virtual ~TransformableObject() = default;
	/**
	 * @brief Metoda do translacji obiektu.
	 *
	 * Klasy pochodne musz¹ zaimplementowaæ tê metodê.
	 * 
	 * @param translation Wektor okreœlaj¹cy przesuniêcie.
	 */
	virtual void translate(const glm::vec3& translation) = 0;
	/**
	 * @brief Metoda do rotacji obiektu.
	 *
	 * Klasy pochodne musz¹ zaimplementowaæ tê metodê.
	 * 
	 * @param angle K¹t rotacji w stopniach.
	 * @param axis Oœ rotacji jako wektor.
	 */
	virtual void rotate(float angle, const glm::vec3& axis) = 0;
	/**
	 * @brief Metoda do skalowania obiektu.
	 *
	 * Klasy pochodne musz¹ zaimplementowaæ tê metodê.
	 * 
	 * @param scale Wektor okreœlaj¹cy skalê.
	 */
	virtual void scale(const glm::vec3& scale) = 0;
};