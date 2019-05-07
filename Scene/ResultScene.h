#pragma once
#include "Scene.h"
#include <memory>
#include "../Object/BackGround.h"

class BuckGround;

class ResultScene :
	public Scene
{
private:
	void (ResultScene::*_updater)(const Input& p);
	void Wait(const Input& p);
	void Run(const Input& p);
	void End(const Input& p);

	std::shared_ptr<BackGround> _background;

	int gameoverimg;
	int itemimg[4];

	int point;
	int totalpoint;
	int time;
	int totaltime;
	int item;

	bool clearflag;
	
	int flame;
	
	//‰¹
	int clearhandle;
	int gameoverhandle;
public:
	ResultScene(float& point, float& time, float& item, bool& clearflag);
	~ResultScene();
	void Draw();
	void Update(const Input& p);

};

