#include "Object.h"


Object::Object()
{
	
}

Object::~Object()
{
}

void Object::Draw(Vector2f _pos, int imgH, bool flag)
{
	DrawRotaGraph(_pos.x, _pos.y, 2, 0, imgH, true, flag);
}

const Position2f Object::GetPos() const {
	return _pos;
}


