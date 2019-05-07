#include "TitleScene.h"
#include "../Game.h"
#include "PlayScene.h"

void TitleScene::Wait(const Input & p)
{
	Game& game = Game::Instance();

	flame++;
	actnum = flame / 10 % 2;
	Draw();

	if (p.IsTrigger(PAD_INPUT_1)) {
		DxLib::PlaySoundMem(clickhandle, DX_PLAYTYPE_BACKBIT);
		game.ChangeScene(new PlayScene());
	}

}

TitleScene::TitleScene(const float& point)
{
	//フォントのロード
	LPCSTR font = "4x4kanafont.ttf";
	if (AddFontResourceEx(font, FR_PRIVATE, nullptr) > 0) {
	}
	else {
		MessageBox(nullptr, "失敗", "", MB_OK);
	}

	SetFontSize(16);

	ChangeFont("4x4極小かなフォント", DX_CHARSET_DEFAULT);

	titleimg = DxLib::LoadGraph("image/title.png");

	DxLib::LoadDivGraph("image/shuriken.png", 2, 2, 1, 8, 8, shuriimg);

	clickhandle = DxLib::LoadSoundMem("Sound/click_2.mp3");

	this->point = point;

	flame = 0;

	_updater = &TitleScene::Wait;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update(const Input& p)
{
	(this->*_updater)(p);
}

void TitleScene::Draw()
{
	int wsizex, wsizey, graphsizex, graphsizey;
	DxLib::GetWindowSize(&wsizex, &wsizey);
	DxLib::GetGraphSize(shuriimg[0], &graphsizex, &graphsizey);

	DxLib::DrawExtendGraph(0, 150, 651, 600, titleimg, true);

	DxLib::DrawRotaGraph(wsizex / 2 - graphsizex * 8, wsizey / 2 - graphsizey / 2, 2.0f, 0, shuriimg[actnum], true);

	DxLib::DrawFormatString(GetFontSize(), GetFontSize(), 0xff00ff, "HISCORE %d", (int)(point));
	if (flame / 30 % 2) {
		DxLib::DrawString(wsizex / 2 - GetFontSize() * 6, wsizey / 2 + wsizey /4, "PREESS Z KEY", 0x00ffff);
	}
}
