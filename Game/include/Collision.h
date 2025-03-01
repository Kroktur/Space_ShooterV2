#pragma once
#include "IGameObject.h"
#include "KT_Vector.h"
class IComposite;
class IComponant;
bool Collision(AABB A, AABB B);

class Colision
{
public:
	void HandleCollision(KT::Vector<IComponant*> objects);
private:
	bool Compose(IComponant* lhs, IComponant* rhs);
	void destroy(KT::Vector<IComponant*> objects);
};
