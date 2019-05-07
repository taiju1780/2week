#include "BackGround.h"


BackGround::BackGround()
{
	backimg = DxLib::LoadGraph("image/stage1.png");
}

BackGround::~BackGround()
{
}

void BackGround::Draw()
{
	DxLib::DrawExtendGraph(0, 0, 650, 900, backimg, true);
}

void BackGround::Update()
{
}
