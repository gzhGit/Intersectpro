#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <string>
#include "pch.h"

using namespace std;

class dot {
public:
	double x;
	double y;

	dot(double x, double y);

	void dotinsert();
};

class line {
public:
	int x1, y1, x2, y2;
	int type;//0-line,1-ray,2-segment

	line(int x1, int x2, int y1, int y2, int type);

	void lineinsert();
};

class cycle {
public:
	int x;
	int y;
	int r;

	cycle(int x, int y, int r);

	void cycleinsert();
};

vector<dot> dots;
vector<line> lines;
vector<cycle> cycles;

void dot::dotinsert() {
	for (int i = 0; i < dots.size(); i++) {
		if (fabs(dots[i].x - this->x) < 0.00000001 && fabs(dots[i].y - this->y) < 0.00000001)
			//if (dots[i].x == d.x && dots[i].y == d.y)
			return;
	}
	dots.push_back(*this);
}

void line::lineinsert() {
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].x1 == this->x1 && lines[i].y1 == this->y1 && lines[i].x2 == this->x2 && lines[i].y2 == this->y2)
			return;
	}
	lines.push_back(*this);
}

void cycle::cycleinsert() {
	for (int i = 0; i < cycles.size(); i++) {
		if (cycles[i].x == this->x && cycles[i].y == this->y && cycles[i].r == this->r)
			return;
	}
	cycles.push_back(*this);
}

dot::dot(double _x, double _y) {
	x = _x;
	y = _y;
}

line::line(int x1, int x2, int y1, int y2, int type) {
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
	this->type = type;
}

cycle::cycle(int x, int y, int r) {
	this->x = x;
	this->y = y;
	this->r = r;

}
/*class dot {
public:
	double x;
	double y;

	dot(double x, double y);

	void dotinsert(dot d);
};

class line {
public:
	double a, b, c;
	int x1, y1, x2, y2;
	int type;//0-line,1-ray,2-segment

	line(int x1, int x2, int y1, int y2, int type);

	line(double a, double b, double c, int type);

	void lintersrctl(double _a, double _b, double _c, int type);

	dot lintersrctl(line l);

	bool _lintersrctl(line l);

	void lineinsert(line l);
};

class cycle {
public:
	int x;
	int y;
	int r;

	cycle(int x, int y, int r);

	void cintersectl(line l);

	bool cintersectc(int x, int y, int r);

	void cycleinsert(cycle c);
};

vector<dot> dots;
vector<line> lines;
vector<cycle> cycles;

void solve();

void line::lineinsert(line l) {
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].a == l.a && lines[i].b == l.b && lines[i].c == l.c)
			return;
	}
	lines.push_back(l);
}

void cycle::cycleinsert(cycle c) {
	for (int i = 0; i < cycles.size(); i++) {
		if (cycles[i].x == c.x && cycles[i].y == c.y && cycles[i].r == c.r)
			return;
	}
	cycles.push_back(c);
}

dot::dot(double _x, double _y) {
	x = _x;
	y = _y;
}

void dot::dotinsert(dot d) {
	for (int i = 0; i < dots.size(); i++) {
		if (fabs(dots[i].x - d.x) < 0.00000001 && fabs(dots[i].y - d.y) < 0.00000001)
			//if (dots[i].x == d.x && dots[i].y == d.y)
			return;
	}
	dots.push_back(d);
}

cycle::cycle(int _x, int _y, int _r) {
	x = _x;
	y = _y;
	r = _r;
}

line::line(int x1, int x2, int y1, int y2, int type) {
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

void line::lintersrctl(double _a, double _b, double _c, int type) {
	if (b == 0 && _b == 0)
		return;
	if (b != 0 && _b != 0 && a / b == _a / _b)
		return;
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
					return;
			}
			else if (this->type == 1) {
				if (((x - (double)x1) * ((double)x2 - (double)x1) < 0) || ((x - (double)this->x1) * ((double)this->x2 - (double)this->x1) < 0))
					return;
			}
			else if (this->type == 2) {
				if (((x - (double)x1) * ((double)x2 - (double)x1) < 0) || (x < (double)min(this->x1, this->x2) || x >(double)max(this->x1, this->x2)))
					return;
			}
		}
		else if (type == 0) {
			if (this->type == 1) {
				if ((x - (double)this->x1) * ((double)this->x2 - (double)this->x1) < 0)
					return;
			}
			else if (this->type == 2) {
				if (x < (double)min(this->x1, this->x2) || x >(double)max(this->x1, this->x2))
					return;
			}
		}
		else if (type == 2) {
			if (this->type == 0) {
				if (x < (double)min(x1, x2) || x >(double)max(x1, x2))
					return;
			}
			else if (this->type == 1) {
				if (((x - (double)this->x1) * ((double)this->x2 - (double)this->x1) < 0) || (x < (double)min(x1, x2) || x >(double)max(x1, x2)))
					return;
			}
			else if (this->type == 2) {
				if ((x < (double)min(x1, x2) || x >(double)max(x1, x2)) || (x < (double)min(this->x1, this->x2) || x >(double)max(this->x1, this->x2)))
					return;
			}
		}
	}
	dot d = dot::dot(x, y);
	d.dotinsert(d);
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

void cycle::cintersectl(line l) {
	double k = 1 / l.a;
	double c = -k * this->x + this->y;
	line _l = line(-k, 1.0, c, 0);
	dot d = l.lintersrctl(_l);
	double dis = sqrt(pow((double)x - d.x, 2) + pow((double)y - d.y, 2));
	if (dis > r)
		return;
	if (dis == r) {
		if (l.type == 1) {
			if ((d.x - l.x1) * ((double)l.x2 - (double)l.x1) < 0)
				return;
		}
		else if (l.type == 2) {
			if (d.x < (double)min(l.x1, l.x2) || d.x >(double)max(l.x1, l.x2))
				return;
		}
		d.dotinsert(d);
		return;
	}
	double n = sqrt(((double)this->r * (double)this->r) - dis * dis);
	double dx = n / sqrt(l.a * l.a + 1);
	double dy = sqrt(n * n - dx * dx);
	if (l.a > 0) dy = -dy;
	dot d1 = dot(d.x + dx, d.y + dy);
	dot d2 = dot(d.x - dx, d.y - dy);
	if (l.type == 1) {
		if ((d1.x - l.x1) * ((double)l.x2 - (double)l.x1) >= 0)
			d1.dotinsert(d1);
		if ((d2.x - l.x1) * ((double)l.x2 - (double)l.x1) >= 0) 
			d2.dotinsert(d2);
		return;
	}
	if (l.type == 2) {
		if (d1.x >= (double)min(l.x1, l.x2) && d1.x <= (double)max(l.x1, l.x2))
			d1.dotinsert(d1);
		if (d2.x >= (double)min(l.x1, l.x2) && d2.x <= (double)max(l.x1, l.x2))
			d2.dotinsert(d2);
		return;
	}
	d1.dotinsert(d1);
	d2.dotinsert(d2);
}

bool cycle::cintersectc(int x, int y, int r) {
	double dis = sqrt(pow(((double)this->x - (double)x), 2) + pow(((double)this->y - (double)y), 2));
	if (dis > ((double)this->r + (double)r))
		return false;
	if (this->r > r && (dis + (double)r) < (double)this->r)
		return false;
	if (this->r < r && (dis + (double)this->r) < (double)r)
		return false;
	double a = ((double)this->x - (double)x) / ((double)this->y - (double)y);
	double c = ((double)(pow((double)this->r, 2) - pow((double)r, 2) - pow((double)this->x, 2) + pow((double)x, 2) - pow((double)this->y, 2) + pow((double)y, 2))) / (((double)y - (double)this->y) * 2);
	line l = line(a, 1.0, c, 0);
	cintersectl(l);
	return true;
}*/

int count = 0;

void solve() {
	for (int i = 0; i < lines.size(); i++) {
		line l = lines[i];
		for (int j = i + 1; j < lines.size(); j++) {
			double* d;
			char c1,c2;
			if (lines[i].type == 0)
				c1 = 'L';
			else if (lines[i].type == 1)
				c1 = 'R';
			else if (lines[i].type == 2)
				c1 = 'S';
			if (lines[j].type == 0)
				c2 = 'L';
			else if (lines[j].type == 1)
				c2 = 'R';
			else if (lines[j].type == 2)
				c2 = 'S';
			try
			{
				d = solve_ll(lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2, c1, 
				lines[j].x1, lines[j].y1, lines[j].x2, lines[j].y2, c2);
				if ((int)d[0] == 1) {
					dot _d = dot(d[1], d[2]);
					_d.dotinsert();
				}
			}
			catch (const char* msg)
			{
				cerr << msg << endl;
			}
		}
	}
	for (int i = 0; i < cycles.size(); i++) {
		cycle c = cycles[i];
		for (int j = i + 1; j < cycles.size(); j++) {
			double* d;
			try
			{
				d = solve_cc(cycles[i].x, cycles[i].y, cycles[i].r, 'C', cycles[j].x,
					cycles[j].y, cycles[j].r, 'C');
				double d0 = d[0];
				double d1 = d[1];
				double d2 = d[2];
				double d3 = d[3];
				double d4 = d[4];
				if ((int)d0 == 1) {
					dot _d = dot(d1, d2);
					_d.dotinsert();
				}
				else if ((int)d0 == 2) {
					dot _d = dot(d1, d2);
					_d.dotinsert();
					dot __d = dot(d3, d4);
					__d.dotinsert();
				}
			}
			catch (const char* msg)
			{
				cerr << msg << endl;
			}
		}
		for (int j = 0; j < lines.size(); j++) {
			double* d;
			char c;
			if (lines[j].type == 0)
				c = 'L';
			else if (lines[j].type == 1)
				c = 'R';
			else if (lines[j].type == 2)
				c = 'S';
			try
			{
				d = solve_lc(lines[j].x1, lines[j].y1, lines[j].x2, lines[j].y2, c,
					cycles[i].x, cycles[i].y, cycles[i].r, 'C');
				double d0 = d[0];
				double d1 = d[1];
				double d2 = d[2];
				double d3 = d[3];
				double d4 = d[4];
				if ((int)d0 == 1) {
					dot _d = dot(d1, d2);
					_d.dotinsert();
				}
				else if ((int)d0 == 2) {
					dot _d = dot(d1, d2);
					_d.dotinsert();
					dot __d = dot(d3, d4);
					__d.dotinsert();
				}
			}
			catch (const char* msg)
			{
				cerr << msg << endl;
			}
		}
	}
}

int main(int argc, char* argv[]) {
	int n;
	ifstream infile;
	infile.open(argv[2]);
	if (infile) {
		string str;
		int i = 0;
		while (getline(infile, str)) {
			if (i == 0) {
				n = 0;
				int j = 0;
				while (str[j] >= 48 && str[j] <= 57) {
					int temp = (int)(str[j] - 48);
					n = 10 * n + temp;
					j++;
				}
			}
			else if (i <= n) {
				char c = str[0];
				if (c == 'L' || c == 'R' || c == 'S') {
					int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
					int j = 2;
					int sym = 0;
					if (str[j] == '-') {
						j = j + 1;
						sym = 1;
					}
					while (str[j] >= 48 && str[j] <= 57) {
						int temp = (int)(str[j] - 48);
						x1 = 10 * x1 + temp;
						j++;
					}
					if (sym == 1) x1 = -x1;
					j = j + 1;
					sym = 0;
					if (str[j] == '-') {
						j = j + 1;
						sym = 1;
					}
					while (str[j] >= 48 && str[j] <= 57) {
						int temp = (int)(str[j] - 48);
						y1 = 10 * y1 + temp;
						j++;
					}
					if (sym == 1) y1 = -y1;
					j = j + 1;
					sym = 0;
					if (str[j] == '-') {
						j = j + 1;
						sym = 1;
					}
					while (str[j] >= 48 && str[j] <= 57) {
						int temp = (int)(str[j] - 48);
						x2 = 10 * x2 + temp;
						j++;
					}
					if (sym == 1) x2 = -x2;
					j = j + 1;
					sym = 0;
					if (str[j] == '-') {
						j = j + 1;
						sym = 1;
					}
					while (str[j] >= 48 && str[j] <= 57) {
						int temp = (int)(str[j] - 48);
						y2 = 10 * y2 + temp;
						j++;
					}
					if (sym == 1) y2 = -y2;
					line l = line(x1, x2, y1, y2, 0);
					if (c == 'R')
						l.type = 1;
					if (c == 'S')
						l.type = 2;
					l.lineinsert();
				}
				else if (c == 'C') {
					int x = 0, y = 0, r = 0;
					int j = 2;
					int sym = 0;
					if (str[j] == '-') {
						j = j + 1;
						sym = 1;
					}
					while (str[j] >= 48 && str[j] <= 57) {
						int temp = (int)(str[j] - 48);
						x = 10 * x + temp;
						j++;
					}
					if (sym == 1) x = -x;
					j = j + 1;
					sym = 0;
					if (str[j] == '-') {
						j = j + 1;
						sym = 1;
					}
					while (str[j] >= 48 && str[j] <= 57) {
						int temp = (int)(str[j] - 48);
						y = 10 * y + temp;
						j++;
					}
					if (sym == 1) y = -y;
					j = j + 1;
					sym = 0;
					if (str[j] == '-') {
						j = j + 1;
						sym = 1;
					}
					while (str[j] >= 48 && str[j] <= 57) {
						int temp = (int)(str[j] - 48);
						r = 10 * r + temp;
						j++;
					}
					if (sym == 1) r = -r;
					cycle cy = cycle(x, y, r);
					cy.cycleinsert();
				}
			}
			else break;
			i++;
		}//°´ÐÐÏÔÊ¾
		infile.close();
	}
	solve();
	ofstream outfile;
	outfile.open(argv[4]);
	outfile << dots.size();
	outfile.close();
	for (int i = 0; i < dots.size(); i++) {
		cout << dots[i].x << " " << dots[i].y << endl;
	}
	cout << dots.size();
	return 0;
}