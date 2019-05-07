#pragma once
#include "Geometry.h"
#include <vector>

struct ItemInfo {
	Position2f _pos;
	Vector2f _size;
	int _actnum;
	bool _getflag;
	ItemInfo() :_pos(0, 0), _size(0, 0), _actnum(0), _getflag(false){};
	ItemInfo(const Position2f&pos, const Vector2f& size, const int& actnum, const bool& getflag) {
		this->_pos = pos;
		this->_size = size;
		this->_actnum = actnum;
		this->_getflag = getflag;
	}
};
class Item
{
private:
	int itemimg[3];
	ItemInfo _item;
	std::vector<ItemInfo> _iteminfo;
	int flame;

public:
	Item();
	~Item();
	void Draw();
	void Update();

	std::vector<ItemInfo> GetInfo();
	void ItemCreat(const Position2f& _pos);

	void ItemDelete(const int& num);
};

