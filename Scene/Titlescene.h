#pragma once
#include "Scene.h"
class TitleScene :
	public Scene
{
private:
	int titleimg;
	void(TitleScene::*_updater)(const Input& p);
	void Wait(const Input& p);
	float point;
	int shuriimg[2];
	int flame;
	int actnum;

	int clickhandle;

public:
	TitleScene(const float& point);
	~TitleScene();
	void Update(const Input& p);
	void Draw();
};

