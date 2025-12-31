#pragma once
#include "GameObject.h"

class DrawableObject : public virtual GameObject {
public:
	virtual ~DrawableObject() = default;
	virtual void draw() = 0;
};