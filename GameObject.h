/**
 * @file GameObject.h
 * @brief Bazowa klasa dla wszystkich obiektów w grze.
 */


#pragma once
/**
 * @brief Bazowa klasa dla wszystkich obiektów w grze.
 *
 * Klasa GameObject definiuje wspólny interfejs
 * dla wszystkich obiektów.
 */
class GameObject {
public:
    /**
  * @brief Wirtualny destruktor klasy GameObject.
  *
  * Zapewnia poprawne niszczenie obiektów klas pochodnych.
  * 
  */
	virtual ~GameObject() = default;
};