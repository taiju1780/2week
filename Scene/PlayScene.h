#pragma once
#include "Scene.h"
#include <memory>
#include <vector>

class Player;
class BackGround;
class Stage;
class Collision;
class Enemy;
class Shuriken;
class Item;

struct UI {
	float _totaltime;
	float _time;
	float _itemcnt;
	float _point;
	UI() :_totaltime(0), _time(0), _itemcnt(0), _point(0) {};
	UI(float totaltime, float time, float _itemcnt, float point) {
		this->_totaltime = totaltime;
		this->_time = time;
		this->_itemcnt = _itemcnt;
		this->_point = point;
	}
};

class PlayScene :
	public Scene
{
private:
	//プレイヤー
	std::shared_ptr<Player> _player;

	//背景
	std::shared_ptr<BackGround> _bg;

	//ステージ
	std::shared_ptr<Stage> _st;

	//あたり判定
	std::shared_ptr<Collision> _col;

	//敵
	std::shared_ptr<Enemy> _ene;
	std::vector<std::shared_ptr<Enemy>> _enemies;

	//手裏剣
	std::shared_ptr<Shuriken> _shuri;

	//アイテム
	std::shared_ptr<Item> _item;

	UI _ui;

	//フォントタイプ
	int font;

	bool colflag;

	int flame;

	//状態遷移用のメンバ関数ポインタ
	void(PlayScene::*_updater)(const Input &p);
	void Wait(const Input& p);
	void Run(const Input& p);
	void End(const Input& p);

	void Change();

	int ground_line = 820;

	std::vector<int> colCheck;

	int playerimg[2];

	bool clearflag;

	int keyflame;


	//音
	int clickhandle;

	int bgm;

	int itempick;

	int hithandle;

public:
	PlayScene();
	~PlayScene();
	void Update(const Input &p);
	void Draw();
	void PointGet();
};

