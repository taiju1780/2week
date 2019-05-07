#include "ResultScene.h"
#include "../Object/BackGround.h"
#include "../Game.h"
#include "../Scene/Titlescene.h"

void ResultScene::Wait(const Input & p)
{
	_background->Draw();
	_updater = &ResultScene::Run;
}

void ResultScene::Run(const Input & p)
{
	int wsizex, wsizey;
	DxLib::GetWindowSize(&wsizex, &wsizey);
	Draw();
	flame++;
	if (flame >= 180) {

		if (totalpoint < (time * 10 + point)) {
			totalpoint += 10;
		}
		if (totaltime > 0) {
			if (flame % 10) {
				totaltime--;
			}
		}
		else {
			if (flame / 30 % 2) {
				DxLib::DrawString(wsizex / 2 - GetFontSize() * 6, wsizey / 2 + wsizey / 4, "PREESS Z KEY", 0x00ffff);
			}
			if (p.IsTrigger(PAD_INPUT_1)) {
				_updater = &ResultScene::End;
			}
		}
	}
	
}

void ResultScene::End(const Input & p)
{
	auto &game = Game::Instance();

	StopSoundMem(clearhandle);
	StopSoundMem(gameoverhandle);
	game.ChangeScene(new TitleScene(totalpoint));
	
}

ResultScene::ResultScene(float& point, float& time, float& item, bool& clearflag)
{
	_background.reset(new BackGround());

	gameoverimg = DxLib::LoadGraph("image/gameover.png");

	DxLib::LoadDivGraph("image/item.png", 4, 4, 1, 16, 16, itemimg);

	//フォントのロード
	LPCSTR font = "4x4kanafont.ttf";
	if (AddFontResourceEx(font, FR_PRIVATE, nullptr) > 0) {
	}
	else {
		MessageBox(nullptr, "失敗", "", MB_OK);
	}

	SetFontSize(16);
	ChangeFont("4x4極小かなフォント", DX_CHARSET_DEFAULT);

	flame = 0;

	clearhandle = DxLib::LoadSoundMem("Sound/fanfare1.mp3");
	gameoverhandle = DxLib::LoadSoundMem("Sound/requiem1.mp3");

	ChangeVolumeSoundMem(128,clearhandle);
	ChangeVolumeSoundMem(128,gameoverhandle);

	this->clearflag = clearflag;

	this->point = point;
	totalpoint = point;
	this->time = time;
	totaltime = time;
	this->item = item;

	_updater = &ResultScene::Wait;

	if (!this->clearflag) {
		PlaySoundMem(gameoverhandle, DX_PLAYTYPE_BACKBIT);
	}
	else {
		PlaySoundMem(clearhandle, DX_PLAYTYPE_BACKBIT);
	}

}

ResultScene::~ResultScene()
{
}

void ResultScene::Draw()
{
	int wsizex, wsizey;
	DxLib::GetWindowSize(&wsizex, &wsizey);

	if (clearflag == false) {
		_background->Draw();
		DxLib::DrawExtendGraph(wsizex / 2 - 100, wsizey / 2 - 50,
			wsizex / 2 + 100, wsizey / 2 + 50, gameoverimg, true);
	}
	else {
		int wsizex, wsizey, bsizex, bsizey, tsizex, tsizey;
		DxLib::GetWindowSize(&wsizex, &wsizey);

		//Bonus表記
		DxLib::DrawString(wsizex / 2 - GetFontSize() * 7 / 2, 300, "BONUS ", 0xfffffff);

		//Time表記
		DxLib::DrawString(wsizex / 2 - GetFontSize() * 7 / 2, 350, " TIME  ", 0xfffffff);

		//time
		DxLib::DrawFormatString(wsizex / 2 - GetFontSize() * 7 / 2, 350 + GetFontSize() * 2, 0xfffffff, "%d X 10", totaltime);

		//アイテム画像
		DxLib::DrawRotaGraph(wsizex / 2 - GetFontSize() * 3, 350 + GetFontSize() * 4 + 5, 1.5f, 0, itemimg[0], true);

		//アイテム獲得数
		DxLib::DrawFormatString(wsizex / 2 - GetFontSize() * 7 / 2, 350 + GetFontSize() * 4, 0xfffffff, "   X %d ", item);

		//point
		DxLib::DrawFormatString(GetFontSize() * 2, GetFontSize()*3, 0xff00fff, "%d", totalpoint);
	}
}

void ResultScene::Update(const Input & p)
{
	(this->*_updater)(p);
}
