#pragma once
#include "Object.h"

class BackGround : public Object
{
private:
	//�w�i�C���[�W
	int backimg;

public:
	BackGround();
	~BackGround();
	void Draw();
	void Update();
};

