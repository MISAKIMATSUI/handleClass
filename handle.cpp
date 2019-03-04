#include <iostream>
class Point 
{
	public : Point() : xValue(0), yValue(0) {}
	public : Point(int x, int y) : xValue(x), yValue(y) {}
	public : int x() const { return xValue; }
	public : int y() const { return yValue; }
	public : Point& x(int xval) {
				 xValue = xval;
				 return *this;
			 }
	public : Point& y(int yval) { 
				 yValue = yval; 
				 return *this;
			 }
	private : 
		int xValue;
		int yValue;
};
class UPoint
{
	friend class Handle;
	Point p;
	int u;

	UPoint() : u(1) {}
	UPoint(int xval, int yval) : p(xval, yval), u(1) {}
	UPoint(const Point& p0) : p(p0), u(1) {}
};
class Handle 
{
	public : Handle();
	public : Handle(int x, int y);
	public : Handle(const Point&);
	public : Handle(const Handle&);
	public : Handle& operator=(const Handle&);
	public : ~Handle();
	public : int x() const;
	public : Handle& x(int xval);
	public : int y() const;
	public : Handle& y(int yval);

	private : 
		UPoint* up;

};
Handle::Handle() : up(new UPoint) {}
Handle::Handle(int x, int y) : up(new UPoint(x, y)) {}
Handle::Handle(const Point& p) : up(new UPoint(p)) {}
Handle::Handle(const Handle& h) : up(h.up) { ++up->u; }
Handle& Handle::operator=(const Handle& h) {
	++h.up->u;
	if (--up->u == 0) {
		delete up;
	}
	up = h.up;
	return *this;
}
Handle::~Handle() {
	if(--up->u == 0)
		delete up;
}
int Handle::x() const {
	return up->p.x(); 
}
int Handle::y() const { 
	return up->p.y(); 
}
#if 1 // ハンドルがポインタのようにふるまうか値的なようにふるまうか
Handle& Handle::x(int xval) {
	up->p.x(xval);
	return *this;
}
Handle& Handle::y(int yval) {
	up->p.y(yval);
	return *this;
}
#else
Handle& Handle::x(int xval) {
	if (up->u != 1) {
		--up->u;
		up = new UPoint(up->p);
	}
	up->p.x(xval);
	return *this;
}
Handle& Handle::y(int yval) {
	if (up->u != 1) {
		--up->u;
		up = new UPoint(up->p);
	}
	up->p.y(yval);
	return *this;
}
#endif
int main(void)
{
	Handle handle(3,5);
	Handle handle1 = handle;
	handle1.x(30);
	std::cout << handle.x() << std::endl;
	std::cout << handle.y() << std::endl;
	std::cout << handle1.x() << std::endl;
	std::cout << handle1.y() << std::endl;
}
