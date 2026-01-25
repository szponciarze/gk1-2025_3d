/**
 * @file Camera.cpp
 * @brief Implementacja klasy Camera.
 *
 * Klasa Camera odpowiada za obs³ugê kamery w scenie 3D,
 * w tym jej pozycjê, punkt obserwowany oraz macierz widoku.
 */

#include "Camera.h"

 /**
  * @brief Konstruktor domyœlny kamery.
  *
  * Inicjalizuje kamerê w pozycji (0, 0, 10),
  * skierowan¹ na punkt (0, 0, 0) z wektorem "góra" (0, 1, 0).
  */
Camera::Camera():position(0,0,10),target(0,0,0),up(0,1,0){}

/**
 * @brief Ustawia pozycjê kamery.
 *
 * @param p Nowa pozycja kamery w przestrzeni 3D
 */
void Camera::setPostion(const glm::vec3& p) {
	position = p;
}

/**
 * @brief Ustawia punkt, na który skierowana jest kamera.
 *
 * @param t Punkt docelowy (target) kamery
 */
void Camera::setTarget(const glm::vec3& t) {
	target = t;
}

/**
 * @brief Przesuwa kamerê w przestrzeni.
 *
 * Funkcja przesuwa zarówno pozycjê kamery,
 * jak i punkt docelowy, zachowuj¹c kierunek patrzenia.
 *
 * @param delta Wektor przesuniêcia
 */
void Camera::move(const glm::vec3& delta) {
	position += delta;
	target += delta;
}

/**
 * @brief Zwraca macierz widoku kamery.
 *
 * Macierz widoku jest obliczana przy u¿yciu funkcji
 * glm::lookAt na podstawie pozycji kamery,
 * punktu docelowego oraz wektora "góra".
 *
 * @return Macierz widoku (view matrix)
 */
glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(position, target, up);
}