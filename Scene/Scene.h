#pragma once
#include "../Input/Input.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Update(const Input& p) = 0;
};

