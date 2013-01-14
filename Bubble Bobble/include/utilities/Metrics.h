#ifndef	METRICS_H
#define	METRICS_H

#include <iostream>
#include <sstream>
#include <string>
#include "MemoryManage.h"

typedef unsigned int Dim;

template <typename T>
std::string NumberToString ( T Number )
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}

template <typename T>
Dim StringToDim ( T str )
{
	std::stringstream s_str( str );
	Dim dim;
	s_str >> dim;
	return dim;
}

class Point{
	public:
		Point():x(0), y(0) {}
		Point(Dim _x, Dim _y):x(_x), y(_y) {}
		Point ( const Point & a ) { x = a.GetX(); y = a.GetY(); }

		~Point() { x = 0; y = 0; }

		Dim GetX(void) const { return x; } 
		Dim GetY(void) const { return y; }

		void SetX(Dim _x) { x = _x; }
		void SetY(Dim _y) { y = _y; }

		friend std::ostream& operator<< (std::ostream& stream, const Point& p) 
		{ return ( stream << "{ " << p.GetX() << ", " << p.GetY() << " }" ); }
		void operator() (const Point & a ) { x = a.x; y = a.y; }

		std::string ToString() { return std::string( "{ " + NumberToString(x) + ", " + NumberToString(y) + " }" ); }

	private:
		Dim x;
		Dim y;
};

class Rect : public Point{
	public:	
		Rect(): Point(0, 0), w(1), h(1) {}
		Rect(Dim x, Dim y, Dim _w, Dim _h): Point(x, y), w(_w), h(_h) {}
		Rect(Point p, Dim _w, Dim _h): Point(p), w(_w), h(_h) {}
		Rect(const Rect & rect): Point(rect.GetX(), rect.GetY()), w(rect.GetWidth()), h(rect.GetHeigth()) {}

		~Rect(void) { DASSERT( w > 0 ); w = 0; DASSERT( h > 0 ); h = 0; }

		Dim GetWidth(void) const { DASSERT( w > 0 ); return w; }
		Dim GetHeigth(void) const { DASSERT( h > 0 ); return h; }

		void SetWidth(Dim _Width) { DASSERT( _Width > 0 ); w = _Width; }
		void SetHeigth(Dim _Heigth) { DASSERT( _Heigth > 0 ); h = _Heigth; }

		void operator() (const Rect & a ) { w = a.GetWidth(); h = a.GetHeigth(); SetX( a.GetX() ); SetY( a.GetY() ); }
		friend std::ostream& operator<< (std::ostream& stream, const Rect& r) 
		{ return ( stream << "{ " << r.GetX() << ", " << r.GetY() << ", " << r.GetWidth() << ", " << r.GetHeigth() <<" }" ); }

		std::string ToString() { return std::string( "{ " + NumberToString( GetX() ) + ", " + NumberToString( GetY() ) + 
									", " + NumberToString( GetWidth() ) + ", " + NumberToString(GetHeigth()) + " }" ); }

	private:
		Dim w;
		Dim h;
};

#endif