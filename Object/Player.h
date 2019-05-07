#pragma once
#include <DxLib.h>
#include "Object.h"
#include <vector>
#include <memory>
#include <map>

struct PlayerInfo {
	Vector2f size;
	int speed;
	int actnum;
	int life;
	Vector2f _vel;
	bool airflag;
	bool turnflag;
	bool colflag;
	bool dethflag;
	PlayerInfo() : size(0, 0),speed(0), actnum(0), life(2), _vel(0, 0), airflag(false), turnflag(false), colflag(false), dethflag(false){};
	PlayerInfo(const Vector2f& size, const int& speed,const int& actnum, const int& life,
		const Vector2f& _vel, const bool& flag, const bool& turnflag, const bool& colflag,const bool& dethflag) {
		this->size = size;
		this->speed = speed;
		this->actnum = actnum;
		this->life = life;
		this->_vel = _vel;
		this->airflag = flag;
		this->turnflag = turnflag;
		this->colflag = colflag;
		this->dethflag = dethflag;
	}
};

struct ShuriInfo {
	Position2f _pos;
	Vector2f size;
	Vector2f _vel;
	int actnum;
	bool shuriflag;
	ShuriInfo() : _pos(0, 0), size(0, 0), _vel(0, 0), actnum(0), shuriflag(false) {};
	ShuriInfo(Position2f _pos, Vector2f size, Vector2f _vel, int actnum, bool shuriflag) {
		this->size = size;
		this->actnum = actnum;
		this->shuriflag = shuriflag;
		this->_vel = _vel;
		this->_pos = _pos;
	}
};

class Player :
	public Object
{
private:
	//�ۑ��p
	Vector2f keeppos;

	//�A�N�V����
	int actnum;

	//�t���[��
	int flame;

	//�v���C���[��ԑJ�ڗp�����o�֐��|�C���^
	void (Player::*_updater)(const Input& p);

	void Wait(const Input& p);

	void ActionUpdate(const Input &p);

	void AttackUpdate(const Input &p);

	void GroundUpdate(const Input& p);

	void DownUpdate(const Input& p);

	void RecoilUpdate(const Input& p);

	void DamageUpdate(const Input& p);

	//�������ҋ@�C���[�W
	int walkimg[2];

	//�_�E���C���[�W
	int downimg[2];

	//�U���C���[�W
	int attackimg[2];

	//�_���[�W����
	int damageimg[4];

	//�藠��
	int shuriimg[2];

	PlayerInfo _pl;
	ShuriInfo shuriinfo;

	int actionState;

	//�A�N�V�����f�[�^�ێ�
	std::vector<int> action;

	void Attack();
	
	void ShurikenCreate();

	void ShurikenReset();

	//��
	int jumphandle;
	int shurihandle;

public:
	Player();
	~Player();
	
	void Update(const Input& p);

	void Draw();

	void GroundToch(int ground);

	void Down();

	void Recoil();

	void Damage();

	void PlayerReset();

	PlayerInfo & GetPLInfo();
	ShuriInfo & GetShuriInfo();
};

