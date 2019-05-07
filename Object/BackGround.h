#pragma once
#include "Object.h"

class BackGround : public Object
{
private:
	//”wŒiƒCƒ[ƒW
	int backimg;

public:
	BackGround();
	~BackGround();
	void Draw();
	void Update();
};

