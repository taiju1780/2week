#include "Item.h"
#include <DxLib.h>


Item::Item()
{
	DxLib::LoadDivGraph("image/item.png", 4, 4, 1, 16, 16, itemimg);

	int itemx, itemy;
	DxLib::GetGraphSize(itemimg[0], &itemx, &itemy);
	auto _pos = Vector2f(0, 0);
	auto size = Vector2f(itemx, itemy);

	flame = 0;

	_item = ItemInfo(_pos, size, 0, false);
}

Item::~Item()
{
}

void Item::Draw()
{
	for (auto iteminfo : _iteminfo) {
		if (iteminfo._getflag == false) {
			DxLib::DrawGraph(iteminfo._pos.x, iteminfo._pos.y, itemimg[iteminfo._actnum], true);
		}
	}
}

void Item::Update()
{
	flame++;
	for(auto iteminfo : _iteminfo){
		iteminfo._actnum = flame / 10 % 3;
	}
}

std::vector<ItemInfo> Item::GetInfo()
{
	return _iteminfo;
}

void Item::ItemCreat(const Position2f& _pos)
{
	int itemx, itemy;
	DxLib::GetGraphSize(itemimg[0], &itemx, &itemy);

	auto pos = _pos;
	auto size = Vector2f(itemx, itemy);
	auto actnum = 0;
	auto getflag = false;

	_item = ItemInfo(pos, size, actnum, getflag);
	_iteminfo.push_back(_item);
}

void Item::ItemDelete(const int& num)
{
	_iteminfo.erase(_iteminfo.begin() + num);
}
