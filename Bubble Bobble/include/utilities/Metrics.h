#ifndef	METRICS_H
#define	METRICS_H

#include "MemoryManage.h"

typedef unsigned int Dim;

class Point{
	public:
		Point():x(0), y(0) {}
		Point(Dim _x, Dim _y):x(_x), y(_y) {}
		Point ( const Point & a ) { x = a.x; y=a.y; }

		Dim GetX(void) const { return x; } 
		Dim GetY(void) const { return y; }

		void SetX(Dim _x) { x = _x; }
		void SetY(Dim _y) { y = _y; }

		void operator() (const Point & a ) { x = a.x; y = a.y; }
		Point * clone(void) { return new Point( x, y); }

	private:
		Dim x;
		Dim y;
};

class Rect : public Point{
	public:	
		Rect(Dim x, Dim y, Dim w, Dim h);
		Rect(Point p, Dim w, Dim y);
		~Rect(void);

		Dim GetWidth(void) { return w; }
		Dim GetHeigth(void) { return h; }

		void SetWidth(Dim _Width) { DASSERT( _Width > 0 ); w = _Width; }
		void SetHeigth(Dim _Heigth) { DASSERT( _Heigth > 0 ); h = _Heigth } ;

		void operator() (const Rect & a ) { w = a.w; h = a.h; SetX( a.GetX() ); SetY( a.GetY() ); }
		Rect * clone(void) { return new Rect(  GetX(), GetY(), w, h); }

	private:
		Dim w;
		Dim h;
};

#endif