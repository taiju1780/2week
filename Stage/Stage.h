#pragma once
#include <DxLib.h>
#include <vector>
#include "../Geometry.h"

struct StageInfo {
	Vector2f size;
	Vector2f centerpos;
	bool colflag;

	StageInfo() : size(0, 0), centerpos(0, 0),colflag(false) {};
	StageInfo(Vector2f size, Vector2f cpos, bool flag) {
		this->size = size;
		this->centerpos = cpos;
		this->colflag = flag;
	}
};

class Stage
{
private:
	std::vector<StageInfo> _stInfo;

public:
	Stage();
	~Stage();
	void Draw();

	void CreateStage(Vector2f size, Vector2f cpos);

	std::vector<StageInfo> GetStageCollider();

	void StageDebugDraw(Vector2f _pos, Vector2f size);
};

