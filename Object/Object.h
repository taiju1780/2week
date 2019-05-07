#pragma once
#include "../Input/Input.h"
#include "../Geometry.h"
#include <vector>

class Object
{
protected:
	Position2f _pos;
private:
	
public:
	Object();
	~Object();

	const Position2f GetPos() const;

	void Draw(Vector2f pos, int imgH, bool flag);
};

