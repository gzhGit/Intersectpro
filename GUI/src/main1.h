#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>

using namespace std;

class _declspec(dllexport) Node {
public:
	int judgeCross = 0;
	double x = 0.0, y = 0.0;

	bool operator < (const Node node) const;

	Node(int judgeCross);
	Node(int judgeCross, double x, double y);
};

class _declspec(dllexport) Line {
public:
	int x1 = 0 , y1 = 0 , x2 = 0 , y2 = 0;
	int special = 0;
	double k = 0.0, b = 0.0, x = 0.0;
	Line();
	Line(int x1, int y1, int x2, int y2);
	Line(double x);
	Line(double k, double b);
};

// circle's model,includes center <a,b> , r
class _declspec(dllexport) Circle {
public:
	int a = 0, b = 0;
	int r = 0;
	Circle(int a, int b, int r);
};

class _declspec(dllexport) Object {
public:
	// line:0,circle:1
	int lineOrCircle = 0;
	Line *line;
	Circle *circle;
	Object();
	Object(int lineOrCircle, Line *line);
	Object(int lineOrCircle, Circle *circle);
};

class _declspec(dllexport) Intersect {
public:
	//calculate line and ine intersect
	vector<Node> lineCrossLine(Line line1, Line line2);
	//calculate line and circle interacts
	vector<Node> lineCrossCircle(Line line, Circle circle);
	//calculate circle and circle interacts
	vector<Node> circleCrossCircle(Circle c1, Circle c2);
};

_declspec(dllexport) int* string2num(char inputstring[], int kind);
