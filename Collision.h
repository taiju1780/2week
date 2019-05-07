#pragma once
#include "Geometry.h"

class Collision
{
public:
	Collision();
	~Collision();

	//Ç†ÇΩÇËîªíË
	bool Col(const Vector2f &posA, const Vector2f &sizeA, const Vector2f &posB, const Vector2f &sizeB);

	//è∞ìñÇΩÇË
	bool StageCol(const Vector2f &posA, const Vector2f &sizeA, const Vector2f &posB, const Vector2f &sizeB);
};

