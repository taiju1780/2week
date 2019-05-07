#include "Stage.h"

Stage::Stage()
{
}


Stage::~Stage()
{
}

void Stage::Draw()
{
	
}

void Stage::CreateStage(Vector2f size, Vector2f cpos)
{
	auto flag = false;
	auto _st = StageInfo(size, cpos, flag);

	_stInfo.push_back(_st);
}

std::vector<StageInfo> Stage::GetStageCollider()
{
	return _stInfo;
}

void Stage::StageDebugDraw(Vector2f _pos, Vector2f size)
{
	DxLib::DrawBox(_pos.x - size.x / 2, _pos.y - size.y / 2, _pos.x + size.x / 2, _pos.y + size.y / 2, 0xff00ff, false);
}
