#include "Collision.h"
#include "cmath"

Collision::Collision()
{
}


Collision::~Collision()
{
}

bool Collision::Col(const Position2f &posA, const Vector2f &sizeA, const Position2f &posB, const Vector2f &sizeB)
{
	return ((abs(posA.x - posB.x) < sizeA.x / 2 + sizeB.x / 2) && (abs(posA.y - posB.y) < sizeA.y / 2 + sizeB.y / 2));
}

bool Collision::StageCol(const Position2f & posA, const Vector2f & sizeA, const Position2f & posB, const Vector2f & sizeB)
{
	return(((abs(posA.x - posB.x) <= sizeA.x / 2 + sizeB.x / 2) && 
		(abs(posA.y - posB.y) <= sizeA.y / 2 + sizeB.y / 2)) && 
		((posA.y + sizeA.y / 2) >= (posB.y - sizeB.y) / 2));
}
