#pragma once
#include "Object.h"
#include <DxLib.h>
#include <memory>

class Player;

struct EnemyInfo {
	Vector2f size;
	int speed;
	int actnum;
	Vector2f _vel;
	bool turnflag;
	bool dethflag;
	bool stunflag;
	EnemyInfo() : size(0, 0), speed(0), actnum(0), _vel(0, 0),turnflag(false), dethflag(false), stunflag(false) {};
	EnemyInfo(const Vector2f size, const int speed, const int actnum, const Vector2f _vel, const bool turnflag, const bool dethflag, const bool stunflag) {
		this->size = size;
		this->speed = speed;
		this->actnum = actnum;
		this->_vel = _vel;
		this->turnflag = turnflag;
		this->dethflag = dethflag;
		this->stunflag = stunflag;
	}
};

struct EnemyShuriInfo {
	Position2f _pos;
	Vector2f size;
	Vector2f _vel;
	int actnum;
	bool shuriflag;
	EnemyShuriInfo() : _pos(0, 0), size(0, 0), _vel(0, 0), actnum(0), shuriflag(false) {};
	EnemyShuriInfo(Position2f _pos, Vector2f size, Vector2f _vel, int actnum, bool shuriflag) {
		this->size = size;
		this->actnum = actnum;
		this->shuriflag = shuriflag;
		this->_vel = _vel;
		this->_pos = _pos;
	}
};


class Enemy :
	public Object
{
private:
	void(Enemy::*_updater)(const Input& p);
	void Wait(const Input& p);
	void ActionUpdate(const Input& p);
	void DamageUpdate(const Input& p);
	void StunUpdate(const Input& p);
	void AttackUpdate(const Input& p);

	//ìGÉCÉÅÅ[ÉW
	int enemyimg[10];

	//éËó†åï
	int shuriimg[2];

	int flame;

	EnemyInfo _ene;

	EnemyShuriInfo shuriinfo;

	const Player& _player;

	void ShurikenReset();

	void ShurikenCreate();

	const int walkrange = 30;
	const int atackrange = 100;

public:
	Enemy(const Player& player, const Position2f pos);
	~Enemy();
	void Draw();
	void Update(const Input& p);

	void Damage();
	void Stunning();

	void Attack();
	const EnemyInfo &GetENInfo();
	EnemyShuriInfo &GetShuriInfo();
};

