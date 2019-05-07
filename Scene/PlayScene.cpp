#include "PlayScene.h"
#include "../Game.h"
#include "../Object/Player.h"
#include "../Object/BackGround.h"
#include "../Stage/Stage.h"
#include "../Collision.h"
#include "../Geometry.h"
#include "ResultScene.h"
#include "../Object/Enemy.h"
#include "../Item.h"
#include <algorithm>

const int fontsize = 10;

void PlayScene::Wait(const Input & p)
{
	int wsizex, wsizey;
	DxLib::GetWindowSize(&wsizex, &wsizey);

	keyflame++;

	auto &_pl = _player->GetPLInfo();

	//描画関係
	DxLib::DrawString(wsizex / 2 - GetFontSize() * 7 / 2, wsizey / 2, "Scene01", 0xffffff);
	DxLib::DrawString(wsizex / 2 - GetFontSize() * 8 / 2, wsizey / 2 - 20, "Player 1", 0xffffff);
	DxLib::DrawString(wsizex / 2 - GetFontSize() * 5 / 2, wsizey / 2 - 20 * 2, "START", 0xffffff);

	DxLib::DrawFormatString(60, 790, 0xffffff," X %d" , _pl.life);
	DxLib::DrawRotaGraph(50, 800, 2, 0, playerimg[0], true);

	if (keyflame / 30 % 2) {
		DxLib::DrawString(wsizex / 2 - GetFontSize() * 6, wsizey / 2 + wsizey / 4, "PREESS Z KEY", 0x00ffff);
	}

	flame = 0;
	
	ground_line = 820;

	_player->PlayerReset();

	if (p.IsTrigger(PAD_INPUT_1)) {
		DxLib::PlaySoundMem(clickhandle, DX_PLAYTYPE_NORMAL);
		_updater = &PlayScene::Run;
	}
}

void PlayScene::Run(const Input & p)
{
	int sizex, sizey;
	GetWindowSize(&sizex, &sizey);

	auto _pl = _player->GetPLInfo();
	auto stage = _st->GetStageCollider();
	auto shuri = _player->GetShuriInfo();

	flame++;

	_ui._time = flame / 60;
	_ui._totaltime = 60 - _ui._time;

	//着地
	if (!_pl.dethflag) {
		if (_player->GetPos().y > ground_line) {
			_player->GroundToch(ground_line);
		}
	}

	//ステージとのあたり判定
	for (int i = 0; i < 6; i++) {
		//床判定
		if (_pl.colflag) {
			if (_col->StageCol(_player->GetPos(), _pl.size, stage[i].centerpos, stage[i].size)) {

				stage[i].colflag = true;

				_pl.airflag = false;

				ground_line = _player->GetPos().y + 0.1;

				DxLib::DrawString(740, 20, "Hit", 0xff00ff);
			}
		}
	}

	if (_pl.airflag) {
		ground_line = 820;
	}

	//プレイヤーの攻撃と敵のあたり判定
	for (auto &enemies : _enemies) {
		if (shuri.shuriflag) {
			if (!enemies->GetENInfo().dethflag) {
				if (_col->Col(shuri._pos, shuri.size, enemies->GetPos(), enemies->GetENInfo().size)) {
					enemies->Damage();
					_item->ItemCreat(enemies->GetPos());
					DxLib::PlaySoundMem(hithandle, DX_PLAYTYPE_BACKBIT);
					_ui._point += 500;
					shuri.shuriflag = false;
				}
			}
		}

		//プレイヤーと敵のあたり判定
		if (!enemies->GetENInfo().dethflag && !_pl.dethflag) {
			if (!enemies->GetENInfo().stunflag) {
				if (_col->Col(_player->GetPos(), _pl.size, enemies->GetPos(), enemies->GetENInfo().size)) {
					enemies->Stunning();
					DxLib::PlaySoundMem(hithandle, DX_PLAYTYPE_BACKBIT);
					_player->Recoil();
				}
			}
		}

		//敵の攻撃とプレイヤーのあたり判定
		if (enemies->GetShuriInfo().shuriflag) {
			if (!_pl.dethflag) {
				if (_col->Col(enemies->GetShuriInfo()._pos, enemies->GetShuriInfo().size, _player->GetPos(), _pl.size)) {
					_player->Damage();
					DxLib::PlaySoundMem(hithandle, DX_PLAYTYPE_BACKBIT);
				}
			}
		}

		//プレイヤーとアイテムの当たり判定
		for (int i = 0; i < _item->GetInfo().size(); i++) {
			if (_col->Col(_player->GetPos(), _pl.size, _item->GetInfo()[i]._pos, _item->GetInfo()[i]._size)) {
				_item->ItemDelete(i);
				PointGet(); 
				DxLib::PlaySoundMem(itempick, DX_PLAYTYPE_BACKBIT);
			}
		}

		//敵が全員死んだらresult
		if (std::all_of(_enemies.begin(), _enemies.end(), 
			[](const std::shared_ptr<Enemy> enemy) {return enemy->GetENInfo().dethflag == true; }) 
			&& 
			std::all_of(_enemies.begin(), _enemies.end(),
			[](const std::shared_ptr<Enemy> enemy) {return enemy->GetPos().y >= 900;})) {
			Change();
		}
		
	}

	
	if (_ui._totaltime == 0) {
		_pl.dethflag = true;
	}

	_player->Update(p);

	for (auto &enemies : _enemies) {
		enemies->Update(p);
	}

	_item->Update();

	if (_player->GetPos().y >= 900 && _pl.dethflag) {
		Change();
	}

	Draw();
}

void PlayScene::End(const Input & p)
{
	Game& game = Game::Instance();
	
	DxLib::StopSoundMem(bgm);

	game.ChangeScene(new ResultScene(_ui._point,_ui._totaltime,_ui._itemcnt,clearflag));
}

void PlayScene::Change()
{
	auto &_pl = _player->GetPLInfo();
	_pl.actnum = 0;
	if (_player->GetPLInfo().life == -1) {
		clearflag = false;
		_updater = &PlayScene::End;
	}
	else if(std::all_of(_enemies.begin(), _enemies.end(),
		[](const std::shared_ptr<Enemy> enemy) {return enemy->GetENInfo().dethflag == true; })) {
		clearflag = true;
		_updater = &PlayScene::End;
	}
	else {
		_updater = &PlayScene::Wait;
	}
}

PlayScene::PlayScene()
{
	//各初期化
	_player.reset(new Player());

	_ene.reset(new Enemy(*_player, Position2f(450, 700)));
	_enemies.push_back(_ene); 

	_ene.reset(new Enemy(*_player, Position2f(320, 700)));
	_enemies.push_back(_ene);

	_ene.reset(new Enemy(*_player, Position2f(300, 610)));
	_enemies.push_back(_ene);

	_ene.reset(new Enemy(*_player, Position2f(200, 430)));
	_enemies.push_back(_ene);

	_bg.reset(new BackGround());

	_st.reset(new Stage());

	_col.reset(new Collision());

	_item.reset(new Item());

	//フォントのロード
	LPCSTR font = "4x4kanafont.ttf";
	if (AddFontResourceEx(font, FR_PRIVATE, nullptr) > 0) {
	}
	else {
		MessageBox(nullptr, "失敗", "", MB_OK);
	}

	SetFontSize(12);
	ChangeFont("4x4極小かなフォント", DX_CHARSET_DEFAULT);

	DxLib::LoadDivGraph("image/walk.png", 2, 2, 1, 16, 16, playerimg);

	//音
	clickhandle = DxLib::LoadSoundMem("Sound/click_2.mp3");

	bgm = DxLib::LoadSoundMem("Sound/stage.mp3");

	itempick = DxLib::LoadSoundMem("Sound/poka03.mp3");

	hithandle = DxLib::LoadSoundMem("Sound/shuri.mp3");


	colflag = false;

	clearflag = false;

	flame = 0;

	keyflame = 0;

	//ステージの生成
	_st->CreateStage(Vector2f(740, 0.2), Vector2f(350, 820));
	_st->CreateStage(Vector2f(740, 0.2), Vector2f(350, 720));
	_st->CreateStage(Vector2f(740, 0.2), Vector2f(350, 630));
	_st->CreateStage(Vector2f(740, 0.2), Vector2f(350, 540));
	_st->CreateStage(Vector2f(740, 0.2), Vector2f(350, 450));
	_st->CreateStage(Vector2f(740, 0.2), Vector2f(350, 360));

	_updater = &PlayScene::Wait;

	auto totaltime = 60.0f;
	auto time = 0.0f;
	auto _itemcnt = 0;
	auto point = 0.0f;

	_ui = UI(totaltime, time, _itemcnt, point);

	DxLib::ChangeVolumeSoundMem(128, bgm);
	DxLib::ChangeVolumeSoundMem(128, itempick);
	DxLib::ChangeVolumeSoundMem(128, hithandle);

	DxLib::PlaySoundMem(bgm, DX_PLAYTYPE_BACK);
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update(const Input & p)
{
	(this->*_updater)(p);
}

void PlayScene::Draw()
{
	int wsizex, wsizey;
	GetWindowSize(&wsizex, &wsizey);
	auto _pl = _player->GetPLInfo();

	_bg->Draw();

	_player->Draw();
	
	for (auto& enemies : _enemies) {
		enemies->Draw();
	}

	_item->Draw();

	//時間
	auto ten = (int)(_ui._totaltime) / 10;
	auto one = (int)(_ui._totaltime) % 10;

	DxLib::DrawFormatString(wsizex / 2, wsizey - fontsize * 2, 0xffffff, "%d", ten);
	DxLib::DrawFormatString(wsizex / 2 + fontsize, wsizey - fontsize * 2, 0xffffff, "%d", one);

	//ポイント
	DxLib::DrawFormatString(GetFontSize() * 5, GetFontSize(), 0xff00ff, "%d", (int)(_ui._point));

}

void PlayScene::PointGet()
{
	_ui._point += 100;
	_ui._itemcnt++;
}
