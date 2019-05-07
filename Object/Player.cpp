#include "Player.h"

const float gravity = 4;
const float Ground = 700;

Player::Player() :keeppos(0, 0)
{
	//プレイヤー
	DxLib::LoadDivGraph("image/walk.png", 2, 2, 1, 16, 16, walkimg);
	DxLib::LoadDivGraph("image/down.png", 2, 2, 1, 16, 16, downimg);
	DxLib::LoadDivGraph("image/attack.png", 2, 2, 1, 16, 16, attackimg);
	DxLib::LoadDivGraph("image/damage.png", 4, 4, 1, 16, 16, damageimg);

	//手裏剣
	DxLib::LoadDivGraph("image/shuriken.png", 2, 2, 1, 8, 8, shuriimg);

	//音
	jumphandle =  DxLib::LoadSoundMem("Sound/jump06.mp3");
	shurihandle =  DxLib::LoadSoundMem("Sound/shuri.mp3");

	DxLib::ChangeVolumeSoundMem(128,jumphandle);
	DxLib::ChangeVolumeSoundMem(128,shurihandle);

	//アクション初期化

	//歩く0,1
	action.push_back(walkimg[1]);
	action.push_back(walkimg[0]);
	//下に降りる2,3
	action.push_back(downimg[1]);
	action.push_back(downimg[0]);
	//攻撃4,5
	action.push_back(attackimg[0]);
	action.push_back(attackimg[1]);

	//ダメージ6～9
	for (int i = 0; i < 4;i++) {
		action.push_back(damageimg[i]);
	}

	int csizex, csizey;
	DxLib::GetGraphSize(walkimg[0], &csizex, &csizey);

	//プレイヤー構造体初期化
	_pos = Vector2f(250, 800);
	auto size = Vector2f(csizex * 2, csizey * 2);
	auto speed = 3;
	auto actnum = 0;
	auto life = 2;
	auto _vel = Vector2f(0, 0);
	auto airflag = true;
	auto turnflag = false;
	auto colflag = true;
	auto dethflag = false;
	_pl = PlayerInfo(size, speed, actnum, life, _vel, airflag, turnflag, colflag, dethflag);

	//手裏剣構造体初期化
	int sizex, sizey;
	DxLib::GetGraphSize(shuriimg[0], &sizex, &sizey);
	auto pos = Vector2f(0,0);
	auto sactnum = 0;
	auto shuriflag = false;
	auto vel = Vector2f(0, 0);
	auto _size = Vector2f(sizex * 2, sizey * 2);
	shuriinfo = ShuriInfo(pos, _size, vel, sactnum, shuriflag);

	flame = 0;

	_updater = &Player::ActionUpdate;
}

Player::~Player()
{
}

void Player::Wait(const Input & p)
{
	_pl.speed = 3;

	_pl.actnum = 0;

	_pl.colflag = true;

	_updater = &Player::ActionUpdate;
}

void Player::ActionUpdate(const Input & p)
{
	flame++;
	int csizex, csizey, wsizex, wsizey;
	DxLib::GetWindowSize(&wsizex, &wsizey);
	DxLib::GetGraphSize(walkimg[0], &csizex, &csizey);
	
	//右へ歩く
	if (p.IsPressed(PAD_INPUT_RIGHT)) {
		_pl.turnflag = true;
		_pos.x += _pl.speed;
		if (_pl.airflag == false) {
			_pl.actnum = flame / 10 % 2;
		}
	}
	//左へ歩く
	else if (p.IsPressed(PAD_INPUT_LEFT)) {
		_pl.turnflag = false;
		_pos.x -= _pl.speed;
		if (_pl.airflag == false) {
			_pl.actnum = flame / 10 % 2;
		}
	}

	//ジャンプ
	if (p.IsPressed(PAD_INPUT_10) && (_pl.airflag == false)) {

		PlaySoundMem(jumphandle, DX_PLAYTYPE_BACKBIT);

		_pl.actnum = 1;

		keeppos.y = _pos.y;

		_pl.speed = 2;

		_pl.airflag = true;

		_pl._vel.y += -10; 
	}

	//ダウン
	if (_pos.y <= 800) {
		if (p.IsPressed(PAD_INPUT_DOWN) && (_pl.airflag == false)) {
			_pl.actnum = 3;
			Down();
		}
	}

	//攻撃
	if (p.IsPressed(PAD_INPUT_2)) {
		Attack();
	}

	//移動制限
	if (_pos.x <= csizex) {
		_pos.x += 3;
	}
	if (_pos.x >= wsizex - csizex) {
		_pos.x -= 3;
	}
}

void Player::AttackUpdate(const Input & p)
{
	flame++;
	_pl._vel.x = 0;
	_pl.speed = 0;
	shuriinfo.actnum = flame / 10 % 2;

	if (flame < 10) {
		_pl.actnum = 4;
	}
	else if (flame < 50) {
		_pl.actnum = 5;
	}
	else {
		ShurikenReset();
		_updater = &Player::Wait;
	}

	if (_pl.turnflag) {
		shuriinfo._vel.x = 2;
	}
	else {
		shuriinfo._vel.x = -2;
	}
}

void Player::GroundUpdate(const Input & p)
{
	_updater = &Player::ActionUpdate;
}

void Player::DownUpdate(const Input & p)
{
	//アニメーション
	flame++;
	_pl.actnum = 2;
	if(flame >= 10){
		_pl.colflag = false;
		_updater = &Player::Wait;
	}
}

void Player::RecoilUpdate(const Input & p)
{
	_pl._vel.x *= 0.95;
	_pos.x += _pl._vel.x;
	if (int(_pl._vel.x) == 0) {
		_updater = &Player::ActionUpdate;
	}
}

void Player::DamageUpdate(const Input & p)
{
	flame++;
	_pl.actnum = (flame / 10 % 2) + 6;
	if (flame >= 20) {
		_pl._vel.y = 3;
	}
}

void Player::GroundToch(int ground)
{
	_pl._vel.y = 0;

	_pl.speed = 3;

	_pos.y = ground;

	_pl.airflag = false;

	_updater = &Player::GroundUpdate;
}

void Player::Attack()
{
	flame = 0;
	ShurikenCreate();
	PlaySoundMem(shurihandle, DX_PLAYTYPE_BACKBIT);
	shuriinfo.shuriflag = true;
	_updater = &Player::AttackUpdate;
}

void Player::ShurikenCreate()
{
	int sizex, sizey;
	DxLib::GetGraphSize(shuriimg[0], &sizex, &sizey);
	auto pos = _pos;
	auto actnum = 0;
	auto shuriflag = false;
	auto _vel = Vector2f(0, 0);
	auto _size = Vector2f(sizex * 2, sizey * 2);

	shuriinfo = ShuriInfo(pos, _size, _vel, actnum, shuriflag);
}

void Player::ShurikenReset()
{
	shuriinfo = ShuriInfo(Vector2f(0, 0), Vector2f(0, 0), Vector2f(0, 0), 0, false);
}

void Player::PlayerReset()
{
	_pos = Vector2f(250, 800);
	_pl = PlayerInfo(_pl.size, 3, 0, _pl.life, Vector2f(0, 0), true, false, true, false);
}

void Player::Down()
{
	flame = 0;

	_pl.airflag = true;

	_pl.colflag = false;

	_updater = &Player::DownUpdate;
}

void Player::Recoil()
{
	if (_pl.turnflag) {
		_pl._vel.x = -3;
	}
	else {
		_pl._vel.x = 3;
	}
	_updater = &Player::RecoilUpdate;
}

void Player::Damage()
{
	flame = 0;
	_pl._vel = Vector2f(0, 0);
	_pl.life -= 1;
	_pl.dethflag = true;
	_pl.colflag = false;
	_updater = &Player::DamageUpdate;
}

PlayerInfo & Player::GetPLInfo()
{
	return _pl;
}

ShuriInfo & Player::GetShuriInfo()
{
	return shuriinfo;
}

void Player::Update(const Input & p)
{
	_pos.y += _pl._vel.y;

	shuriinfo._pos.x += shuriinfo._vel.x;

	if (_pl.airflag && !_pl.dethflag) {
		_pl._vel.y *= 0.98;
		_pos.y += gravity;
	}

	(this->*_updater)(p);
}

void Player::Draw()
{
	Object::Draw(_pos, action[_pl.actnum], _pl.turnflag);
	if (shuriinfo.shuriflag) {
		DrawRotaGraph(shuriinfo._pos.x, shuriinfo._pos.y, 2, 0, shuriimg[shuriinfo.actnum], true);
	}
}
