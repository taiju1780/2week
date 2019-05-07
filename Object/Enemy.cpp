#include "Enemy.h"
#include <random>
#include "Player.h"

void Enemy::Wait(const Input & p)
{
	_ene.stunflag = false;
	_updater =& Enemy::ActionUpdate;
}

void Enemy::ActionUpdate(const Input & p)
{
	flame++;

	if (_ene.turnflag) {
		if (_player.GetPos().y >= _pos.y - walkrange && _player.GetPos().y <= _pos.y + walkrange) {
			_ene._vel.x = 1;
			if (flame / 10 % 2 == 1) {
				if (abs(_player.GetPos().x - _pos.x) <= atackrange) {
					Attack();
				}
			}
		}
		else {
			_ene._vel.x = 0;
		}
		
	}
	else {
		if (_player.GetPos().y >= _pos.y - walkrange && _player.GetPos().y <= _pos.y + walkrange) {
			_ene._vel.x = -1;
			if (flame / 10 % 2 == 1) {
				if (abs(_player.GetPos().x - _pos.x) <= atackrange) {
					Attack();
				}
			}
		}
		else {
			_ene._vel.x = 0;
		}
	}
	_ene.actnum = flame / 10 % 2;
}

void Enemy::DamageUpdate(const Input & p)
{
	flame++;
	_ene.actnum = (flame / 10 % 2) + 8;
	if (flame >= 40) {
		_ene._vel.y = 3;
	}
}

void Enemy::StunUpdate(const Input & p)
{
	flame++;
	_ene.actnum = (flame / 10 % 2) + 6;
	if (flame >= 120) {
		_updater = &Enemy::Wait;
	}
}

void Enemy::AttackUpdate(const Input & p)
{
	flame++;
	shuriinfo.actnum = flame / 10 % 2;

	if (flame < 10) {
		_ene.actnum = 2;
	}
	else if (flame < 50) {
		_ene.actnum = 3;
	}
	else {
		ShurikenReset();
		_updater = &Enemy::Wait;
	}

	if (_ene.turnflag) {
		shuriinfo._vel.x = 2;
	}
	else {
		shuriinfo._vel.x = -2;
	}
}

void Enemy::Attack()
{
	flame = 0;
	_ene._vel.x = 0;
	ShurikenCreate();
	shuriinfo.shuriflag = true;
	_updater = &Enemy::AttackUpdate;
}

const EnemyInfo & Enemy::GetENInfo()
{
	return _ene;
}

EnemyShuriInfo & Enemy::GetShuriInfo()
{
	return shuriinfo;
}

void Enemy::ShurikenReset()
{
	shuriinfo = EnemyShuriInfo(Position2f(), Vector2f(), Vector2f(), 0, false);
}

void Enemy::ShurikenCreate()
{
	int sizex, sizey;
	DxLib::GetGraphSize(shuriimg[0], &sizex, &sizey);
	auto pos = _pos;
	auto actnum = 0;
	auto shuriflag = false;
	auto _vel = Vector2f(0, 0);
	auto _size = Vector2f(sizex * 2, sizey * 2);

	shuriinfo = EnemyShuriInfo(pos, _size, _vel, actnum, shuriflag);
}

Enemy::Enemy(const Player& player, const Position2f pos) : _player(player)
{
	//敵
	DxLib::LoadDivGraph("image/enemy.png", 10, 10, 1, 16, 16, enemyimg);

	//手裏剣
	DxLib::LoadDivGraph("image/shuriken.png", 2, 2, 1, 8, 8, shuriimg);

	int csizex, csizey;
	DxLib::GetGraphSize(enemyimg[0], &csizex, &csizey);

	//エネミー初期化
	_pos = pos;
	auto size = Vector2f(csizex * 2, csizey * 2);
	auto speed = 3;
	auto actnum = 0;
	auto _vel = Vector2f(0, 0);
	auto turnflag = false;
	auto dethflag = false;
	auto stunflag = false;
	_ene = EnemyInfo(size, speed, actnum, _vel, turnflag, dethflag, stunflag);


	//手裏剣構造体初期化
	int sizex, sizey;
	DxLib::GetGraphSize(shuriimg[0], &sizex, &sizey);
	auto shuripos = Vector2f(0, 0);
	auto sactnum = 0;
	auto shuriflag = false;
	auto vel = Vector2f(0, 0);
	auto _size = Vector2f(sizex * 2, sizey * 2);
	shuriinfo = EnemyShuriInfo(shuripos, _size, vel, sactnum, shuriflag);
	flame = 0;

	_updater = &Enemy::Wait;
}

Enemy::~Enemy()
{
}

void Enemy::Draw()
{
	Object::Draw(_pos,enemyimg[_ene.actnum],_ene.turnflag);

	if (shuriinfo.shuriflag) {
		DrawRotaGraph(shuriinfo._pos.x, shuriinfo._pos.y, 2, 0, shuriimg[shuriinfo.actnum], true);
	}
}

void Enemy::Update(const Input & p)
{
	if (_player.GetPos().x > _pos.x) {
		_ene.turnflag = true;
	}
	else if (_player.GetPos().x < _pos.x) {
		_ene.turnflag = false;
	}
	_pos += _ene._vel;

	shuriinfo._pos.x += shuriinfo._vel.x;

	(this->*_updater)(p);
}

void Enemy::Damage()
{
	flame = 0;
	_ene._vel = Vector2f(0, 0);
	_ene.dethflag = true;
	ShurikenReset();
	_updater = &Enemy::DamageUpdate;
}

void Enemy::Stunning()
{
	flame = 0;
	_ene._vel = Vector2f(0, 0);
	_ene.stunflag = true;
	_updater = &Enemy::StunUpdate;
}
