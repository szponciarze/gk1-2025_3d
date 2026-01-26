/**
 * @file DrawableObject.h
 * @brief Abstrakcyjna klasa bazowa dla obiektów mo¿liwych do rysowania.
 */

#pragma once
#include "GameObject.h"

/**
 * @brief Abstrakcyjna klasa bazowa dla obiektów mo¿liwych do rysowania.
 *
 * DrawableObject rozszerza GameObject o interfejs renderowania.
 * 
 */

class DrawableObject : public virtual GameObject {
public:
	/**
	* @brief Wirtualny destruktor klasy DrawableObject.
	*/
	virtual ~DrawableObject() = default;
	/**
	 * @brief Metoda do rysowania obiektu.
	 *
	 * Klasy pochodne musz¹ zaimplementowaæ tê metodê.
	 * 
	 */
	virtual void draw() = 0;
};