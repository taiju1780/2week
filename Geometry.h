#pragma once

template<typename T>	

struct Vector2D {
	Vector2D() :x(0), y(0) {}
	Vector2D(T inx, T iny) : x(inx), y(iny) {}
	T x;
	T y;

	void operator += (const Vector2D<T> &in) {	
		x += in.x;
		y += in.y;
	}

	void operator -= (const Vector2D<T> &in) {
		x -= in.x;
		y -= in.y;
	}

	void operator *= (const Vector2D<T> &in) {
		x *= in.x;
		y *= in.y;
	}
};

//Vector2D<T>のための+ｵﾍﾟﾚｰﾀｵｰﾊﾞｰﾛｰﾄﾞ
template<typename T>
Vector2D<T> operator+(const Vector2D<T>& lv, const Vector2D<T>& rv) {

	return Vector2D<T>(lv.x + rv.x, lv.y + rv.y);

}

template<typename T>
Vector2D<T> operator-(const Vector2D<T>& in) {
	return Vector2D<T>(in.x - in.x);
}

template<typename T>
Vector2D<T> operator*(const Vector2D<T>& in) {
	return Vector2D<T>(in.x * in.x);
}


class Geometry
{
public:
	Geometry();
	~Geometry();
};

//整数型
typedef Vector2D<int> Vector2;
typedef Vector2 Position2;

//実数型
typedef Vector2D<float> Vector2f;
typedef Vector2f Position2f;

///サイズを表す構造体
struct Size {
	Size();
	Size(int inx, int iny);
	int width;
	int height;
};

///矩形を表現する構造体
struct Rect {
	Position2 center;
	Size size;

	Rect();
	Rect(int x, int y, int w, int h);
	Rect(Position2 &pos, Size &sz);
	const int Left()const;
	const int Right()const;
	const int Top()const;
	const int Bottom()const;
	const int Width()const { return size.width; }
	const int Height()const { return size.height; }

	//矩形を描画する
	void Draw(unsigned int color = 0xffffffff);
	void Draw(const Vector2& offset, unsigned int color = 0xffffffff); //デフォルト引数はｈ側に書く
};



