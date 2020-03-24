// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class dot {
public:
	double x;
	double y;

	dot(double x, double y);
};

class line {
public:
	double a, b, c;
	int x1, y1, x2, y2;
	int type;//0-line,1-ray,2-segment

	line(int x1, int y1, int x2, int y2, int type);

	line(double a, double b, double c, int type);

	bool lintersrctl(double _a, double _b, double _c, int type, dot* d);

	dot lintersrctl(line l);

	bool _lintersrctl(line l);
};

class cycle {
public:
	int x;
	int y;
	int r;

	cycle(int x, int y, int r);

	vector<dot> cintersectl(line l);

	vector<dot> cintersectc(int x, int y, int r);
};

dot::dot(double _x, double _y) {
	x = _x;
	y = _y;
}

cycle::cycle(int _x, int _y, int _r) {
	x = _x;
	y = _y;
	r = _r;
}

line::line(int x1, int y1, int x2, int y2, int type) {
	if (x1 == x2) {
		b = 0.0;
		a = 1.0;
		c = (double)x1;
		this->x1 = x1;
		this->x2 = x2;
		this->y1 = y1;
		this->y2 = y2;
		this->type = type;
		return;
	}
	double t1 = (double)y2 - (double)y1;
	double t2 = (double)x1 - (double)x2;
	a = t1 / t2;
	b = 1.0;
	this->type = type;
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
	c = a * x1 + b * y1;
}

line::line(double a, double b, double c, int type) {
	this->a = a;
	this->b = b;
	this->c = c;
	this->type = type;
}

bool line::_lintersrctl(line l) {
	if (b == 0 && l.b == 0)
		return false;
	if (b != 0 && l.b != 0 && a / b == l.a / l.b)
		return false;
	return true;
}

dot line::lintersrctl(line l) {
	double t1 = fabs(a * l.b - l.a * b);
	double t2 = fabs(c * l.b - b * l.c);
	double t3 = fabs(c * l.a - a * l.c);
	double x = t2 / t1;
	double y = t3 / t1;
	dot d = dot::dot(x, y);
	return d;
}

bool line::lintersrctl(double _a, double _b, double _c, int type, dot* d) {
	if (b == 0 && _b == 0)
		return false;
	if (b != 0 && _b != 0 && a / b == _a / _b)
		return false;
	double t1 = this->a * _c - _a * this->c;
	double t2 = this->a * _b - _a * this->b;
	double t3 = _b * this->c - this->b * _c;
	double t4 = (double)(this->a * _b - _a * this->b);
	double x = t3 / t4;
	double y = t1 / t2;
	if (type != 0 || this->type != 0) {
		if (type == 1) {
			if (this->type == 0) {
				if ((x - (double)x1) * ((double)x2 - (double)x1) < 0)
					return false;
			}
			else if (this->type == 1) {
				if (((x - (double)x1) * ((double)x2 - (double)x1) < 0) || ((x - (double)this->x1) * ((double)this->x2 - (double)this->x1) < 0))
					return false;
			}
			else if (this->type == 2) {
				if (((x - (double)x1) * ((double)x2 - (double)x1) < 0) || (x < (double)min(this->x1, this->x2) || x >(double)max(this->x1, this->x2)))
					return false;
			}
		}
		else if (type == 0) {
			if (this->type == 1) {
				if ((x - (double)this->x1) * ((double)this->x2 - (double)this->x1) < 0)
					return false;
			}
			else if (this->type == 2) {
				if (x < (double)min(this->x1, this->x2) || x >(double)max(this->x1, this->x2))
					return false;
			}
		}
		else if (type == 2) {
			if (this->type == 0) {
				if (x < (double)min(x1, x2) || x >(double)max(x1, x2))
					return false;
			}
			else if (this->type == 1) {
				if (((x - (double)this->x1) * ((double)this->x2 - (double)this->x1) < 0) || (x < (double)min(x1, x2) || x >(double)max(x1, x2)))
					return false;
			}
			else if (this->type == 2) {
				if ((x < (double)min(x1, x2) || x >(double)max(x1, x2)) || (x < (double)min(this->x1, this->x2) || x >(double)max(this->x1, this->x2)))
					return false;
			}
		}
	}
	dot _d = dot(x, y);
	if (d != NULL) {
		d->x = _d.x;
		d->y = _d.y;
	}
	return true;
}

vector<dot> cycle::cintersectl(line l) {
	vector<dot> dots;
	double k = 1 / l.a;
	double c = -k * this->x + this->y;
	line _l = line(-k, 1.0, c, 0);
	dot d = l.lintersrctl(_l);
	double dis = sqrt(pow((double)x - d.x, 2) + pow((double)y - d.y, 2));
	if (dis > r)
		return dots;
	if (dis == r) {
		if (l.type == 1) {
			if ((d.x - l.x1) * ((double)l.x2 - (double)l.x1) < 0)
				return dots;
		}
		else if (l.type == 2) {
			if (d.x < (double)min(l.x1, l.x2) || d.x >(double)max(l.x1, l.x2))
				return dots;
		}
		dots.push_back(d);
		return dots;
	}
	double n = sqrt(((double)this->r * (double)this->r) - dis * dis);
	double dx = n / sqrt(l.a * l.a + 1);
	double dy = sqrt(n * n - dx * dx);
	if (l.a > 0) dy = -dy;
	dot d1 = dot(d.x + dx, d.y + dy);
	dot d2 = dot(d.x - dx, d.y - dy);
	if (l.type == 1) {
		if ((d1.x - l.x1) * ((double)l.x2 - (double)l.x1) >= 0)
			dots.push_back(d1);
		if ((d2.x - l.x1) * ((double)l.x2 - (double)l.x1) >= 0)
			dots.push_back(d2);
		return dots;
	}
	if (l.type == 2) {
		if (d1.x >= (double)min(l.x1, l.x2) && d1.x <= (double)max(l.x1, l.x2))
			dots.push_back(d1);
		if (d2.x >= (double)min(l.x1, l.x2) && d2.x <= (double)max(l.x1, l.x2))
			dots.push_back(d2);
		return dots;
	}
	dots.push_back(d1);
	dots.push_back(d2);
	return dots;
}

vector<dot> cycle::cintersectc(int x, int y, int r) {
	vector<dot> dots;
	double dis = sqrt(pow(((double)this->x - (double)x), 2) + pow(((double)this->y - (double)y), 2));
	if (dis > ((double)this->r + (double)r))
		return dots;
	if (this->r > r && (dis + (double)r) < (double)this->r)
		return dots;
	if (this->r < r && (dis + (double)this->r) < (double)r)
		return dots;
	double a;
	double b;
	double c;
	if (((double)this->y - (double)y == 0)) {
		a = 1.0;
		b = 0.0;
	}
	else {
		a = ((double)this->x - (double)x) / ((double)this->y - (double)y);
		b = 1.0;
	}
	c = ((double)(pow((double)this->r, 2) - pow((double)r, 2) - pow((double)this->x, 2) + pow((double)x, 2) - pow((double)this->y, 2) + pow((double)y, 2))) / (((double)y - (double)this->y) * 2);
	line l = line(a, b, c, 0);
	vector<dot> ds = cintersectl(l);
	return ds;
}

double* solve_ll(int x11, int y11, int x12, int y12, char c1, int x21, int y21, int x22, int y22, char c2) {
	line l1 = line(x11, y11, x12, y12, 0);
	line l2 = line(x21, y21, x22, y22, 0);
	if (c1 == 'R') l1.type = 1;
	else if (c1 == 'S') l1.type = 2;
	if (c2 == 'R') l2.type = 1;
	else if (c2 == 'S') l2.type = 2;
	double dots[3];
	dots[0] = 0;
	dot* d = (dot*)malloc(sizeof(dot));
	if (l1.lintersrctl(l2.a, l2.b, l2.c, l2.type, d)) {
		dots[0] = 1;
		if (d != NULL) {
			dots[1] = d->x;
			dots[2] = d->y;
		}
	}
	return dots;
}

double* solve_lc(int x11, int y11, int x12, int y12, char c1, int x21, int y21, int r, char c) {
	line l1 = line(x11, y11, x12, y12, 0);
	if (c1 == 'R') l1.type = 1;
	else if (c1 == 'S') l1.type = 2;
	cycle cy = cycle(x21, y21, r);
	vector<dot> dots = cy.cintersectl(l1);
	double d[5];
	d[0] = (double)dots.size();
	for (int i = 0; i < (int)dots.size(); i++) {
		d[i * 2 + 1] = dots[i].x;
		d[i * 2 + 2] = dots[i].y;
	}
	return d;
}

double* solve_cc(int x11, int y11, int r1, char c1, int x21, int y21, int r2, char c2) {
	cycle cy1 = cycle(x11, y11, r1);
	cycle cy2 = cycle(x21, y21, r2);
	vector<dot> dots = cy1.cintersectc(cy2.x, cy2.y, cy2.r);
	double d[5];
	d[0] = (double)dots.size();
	for (int i = 0; i < (int)dots.size(); i++) {
		d[i * 2 + 1] = dots[i].x;
		d[i * 2 + 2] = dots[i].y;
	}
	return d;
}
// 当使用预编译的头时，需要使用此源文件，编译才能成功。
