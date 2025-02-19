#include "IGameObject.h"

float convertRadToDeg(const float& rad)
{
	return (180 * rad) / 3.14159f;
}

float convertDegToRad(const float& deg)
{
	return (deg * 3.14159f) / 180;
}

IGameObject::~IGameObject()
{
	delete m_shape;
}
