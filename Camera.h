/**
 * @file Camera.h
 * @brief Klasa reprezentuj¹ca kamerê.
 */

#pragma once
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
/**
 * @brief Klasa reprezentuj¹ca kamerê.
 * 
 * Umo¿liwia ustawianie pozycji, celu oraz obliczanie macierzy widoku.
 */
class Camera {
private:
	/** 
	 * @brief Pozycja kamery w przestrzeni 3D.
	 */
	glm::vec3 position;
	/** 
	 * @brief Punkt, na który kamera jest skierowana.
	 */
	glm::vec3 target;
	/** 
	 * @brief Wektor okreœlaj¹cy kierunek "do góry" kamery.
	 */
	glm::vec3 up;
public:
	/** 
	 * @brief Konstruktor domyœlny klasy Camera.
	 */
	Camera();
	/** 
	 * @brief Ustawia pozycjê kamery.
	 * 
	 * @param p Nowa pozycja kamery.
	 */
	void setPostion(const glm::vec3& p);
	/** 
	 * @brief Ustawia punkt docelowy kamery.
	 * 
	 * @param t Nowy punkt docelowy kamery.
	 */
	void setTarget(const glm::vec3& t);
	/** 
	 * @brief Przesuwa kamerê o okreœlony wektor przesuniêcia.
	 * 
	 * @param delta Wektor przesuniêcia.
	 */
	void move(const glm::vec3& delta);
	/** 
	 * @brief Zwraca macierz widoku kamery.
	 * 
	 * @return Macierz widoku jako glm::mat4.
	 */
	glm::mat4 getViewMatrix() const;
};