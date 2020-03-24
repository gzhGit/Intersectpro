// Win32Project1.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Win32Project1.h"
#include "main.h"
#include "main1.h"
#define MAX_LOADSTRING 100
#include <string>
#include <iostream>
#include <fstream>
#include "Resource.h"
#include <vector>
#include <set>
//#include <iostream>
using namespace std;
// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Dialog(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Queren(HWND, UINT, WPARAM, LPARAM);
void initPaint(HWND);
void paintLine(HWND,int,int);
void openFile();
void paintIntersect(HWND, vector<Node>);
void intersect(HWND, int, int);
int zeroBoL(double a, double b);
vector<Node> judgeLegalll(char , char , Line , Line , vector<Node>);
vector<Node> judgeLegallc(char , Line , vector<Node>);
int zeroBoL(double , double );
int judgebetween(double, double, double);

set<Node> nodeset;
TCHAR inputstring[64];
int x1_int = 100;
char x_1[64],y_1[64],x_2[64],y_2[64];
char x[64], y[64], r[64];
int numofobj = 0;
char filename[64];
char zeroConst[4] = "0";
char numConst[11][4] = {"1","2","3","4","5","6","7","8","9","10","11"};
char negnumConst[11][4] = { "-1","-2","-3","-4","-5","-6","-7","-8","-9","-10","-11"};
int unit = 0;
int lines[64][5];		//lines[][0] x1 , [1] y1 , [2] x2 , [3] y2 , 
						//[4] 标记：0信息不全，1直线，2射线，3线段
int centerx = 0;
int centery = 0;
int numofintersects;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。
	
    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
    //注册窗口类
	MyRegisterClass(hInstance);

    // 执行应用程序初始化: （创建窗口）
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));
	//MessageBox(NULL, _T("出来啦！"), _T("萌萌哒"), MB_OK);
    MSG msg;
	
    // 主消息循环: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT1);
	wcex.lpszClassName = szWindowClass;
		//NULL;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	//关键是注册函数
    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中
   //创建窗口
   WCHAR NAME[128];
   char* name = "绘图求交点";
   MultiByteToWideChar(CP_ACP, 0, name, strlen(name) + 1, NAME, 128);
   HWND hWnd = CreateWindowW(szWindowClass,		//LpClassName，类名	
	   //szTitle,									//LpWindowName，窗口标题			
	   NAME,
	   WS_OVERLAPPEDWINDOW,						//指定创建窗口的风格
	   CW_USEDEFAULT,							//x 指定窗口的初始水平位置
	   0,										//y 指定窗口的初始垂直位置
	   CW_USEDEFAULT,							//nWidth
	   0,										//nHeight
	   nullptr,									//hWndParent 父窗口句柄
	   nullptr,									//hMenu	菜单句柄
	   hInstance,								//与窗口相关联的模块示例的句柄
	   nullptr);								//LpParam 传入WM_CREATE的一个指针，
												//可以用来传递一些用于创建窗口的信息

   if (!hWnd)
   {
      return FALSE;
   }
   //显示窗口
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//	WM_LBUTTONDOWN 单击鼠标左键的消息：
//		LPARAM 低字节包含当前坐标的X坐标值，高字节包含当前光标的Y坐标值
//		WPARAM 包含一整数值以标识鼠标键的按下状态
//	WM_COMMAND 
//		Message Source:Menu	, WPARAM(low word)=Menu identifier(IDM_*)	
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//WNDPROC
	HDC hdc;
	PAINTSTRUCT ps;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择: 
            switch (wmId)
            {
            case IDM_ABOUT:
				//DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dialog);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				//DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, About);
				break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case ID_INPUT_X1:
				{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dialog);
				//strcpy((char*)x1, (char*)inputstring);

				//GetDlgItemText(hWnd, IDC_EDIT1, x1, 64);
				WideCharToMultiByte(CP_ACP, 0, inputstring, 64, x_1, 64, NULL, NULL);
				lines[numofobj][0] = atoi(x_1);
				//MessageBox(hWnd, inputstring, inputstring, MB_OK | MB_ICONINFORMATION);
				}
				break;
			case ID_INPUT_Y1:
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dialog);
				//strcpy((char*)x1, (char*)inputstring);

				//GetDlgItemText(hWnd, IDC_EDIT1, x1, 64);
				WideCharToMultiByte(CP_ACP, 0, inputstring, 64, y_1, 64, NULL, NULL);
				lines[numofobj][1] = atoi(y_1);
				//MessageBox(hWnd, inputstring, inputstring, MB_OK | MB_ICONINFORMATION);
			}
			break;
			case ID_INPUT_X2:
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dialog);
				//strcpy((char*)x1, (char*)inputstring);

				//GetDlgItemText(hWnd, IDC_EDIT1, x1, 64);
				WideCharToMultiByte(CP_ACP, 0, inputstring, 64, x_2, 64, NULL, NULL);
				lines[numofobj][2] = atoi(x_2);
				//MessageBox(hWnd, inputstring, inputstring, MB_OK | MB_ICONINFORMATION);
			}
			break;
			case ID_INPUT_Y2:
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dialog);
				//strcpy((char*)x1, (char*)inputstring);

				//GetDlgItemText(hWnd, IDC_EDIT1, x1, 64);
				WideCharToMultiByte(CP_ACP, 0, inputstring, 64, y_2, 64, NULL, NULL);
				lines[numofobj][3] = atoi(y_2);
				//MessageBox(hWnd, inputstring, inputstring, MB_OK | MB_ICONINFORMATION);
			}
			break;
			case ID_INPUTOBJ:
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dialog);
				char kind[64];
				WideCharToMultiByte(CP_ACP, 0, inputstring, 64, kind, 64, NULL, NULL);
				switch (kind[0]) {
				case 'L':
					lines[numofobj][4] = 1;
					break;
				case 'R':
					lines[numofobj][4] = 2;
					break;
				case 'S':
					lines[numofobj][4] = 3;
					break;
				case 'C':
					lines[numofobj][4] = 4;
					break;
				default:
					MessageBox(hWnd, _T("输入了未知的几何类型，请重新输入！"), _T("Type error!"), MB_OK);
					break;
				}
			}
			break;
			case ID_QUEREN:
			{
				if ((lines[numofobj][0] == lines[numofobj][2]) &&
					(lines[numofobj][1] == lines[numofobj][3])) {
					MessageBox(hWnd, _T("输入了重复的两个点，请重新输入！"), _T("Coordinate error!"), MB_OK);
					break;
				}
				numofobj++;
				MessageBox(hWnd, _T("输入成功！"), _T("输入成功！"), MB_OK | MB_ICONINFORMATION);
				//paintLine(hWnd,numofobj-1,0);
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
			case ID_INPUTFILE:
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_INPUTFILE), hWnd, Dialog);
			
				WideCharToMultiByte(CP_ACP, 0, inputstring, 64, filename, 64, NULL, NULL);

				openFile();

				/*for (int i = 0; i < numofobj; i++) {
					paintLine(hWnd,i,0);
				}*/
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
			case ID_YUANX:
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dialog);
				//strcpy((char*)x1, (char*)inputstring);

				//GetDlgItemText(hWnd, IDC_EDIT1, x1, 64);
				WideCharToMultiByte(CP_ACP, 0, inputstring, 64, x, 64, NULL, NULL);
				lines[numofobj][0] = atoi(x);
			}
			break;
			case ID_YUANY:
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dialog);
				//strcpy((char*)x1, (char*)inputstring);

				//GetDlgItemText(hWnd, IDC_EDIT1, x1, 64);
				WideCharToMultiByte(CP_ACP, 0, inputstring, 64, y, 64, NULL, NULL);
				lines[numofobj][1] = atoi(y);
			}
			break;
			case ID_R:
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dialog);
				//strcpy((char*)x1, (char*)inputstring);

				//GetDlgItemText(hWnd, IDC_EDIT1, x1, 64);
				WideCharToMultiByte(CP_ACP, 0, inputstring, 64, r, 64, NULL, NULL);
				if (atoi(r) <= 0) {
					MessageBox(hWnd, _T("圆的半径要大于0，请重新输入！"), _T("error!"), MB_OK);
					break;
				}
				lines[numofobj][2] = atoi(r);
			}
			break;
			case ID_Q:
			{
				lines[numofobj][4] = 4;
				numofobj++;
				MessageBox(hWnd, _T("输入成功！"), _T("输入成功！"), MB_OK | MB_ICONINFORMATION);
				//paintLine(hWnd, numofobj - 1,0);
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
			case ID_DELETEOBJ:
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, Dialog);
				char obj[8];
				WideCharToMultiByte(CP_ACP, 0, inputstring, 64, obj, 8, NULL, NULL);
				int i = atoi(obj);
				if (i < 0) {
					MessageBox(hWnd, _T("编号不合法，请重新输入！"), _T("输入失败！"), MB_OK | MB_ICONINFORMATION);
					break;
				}
				lines[i][4] = 0;
				
				//paintLine(hWnd, i,1);
				InvalidateRect(hWnd,NULL,TRUE);		
			}
			break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
			break;
        }
        break;
    case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
			RECT rClient;
			//HPEN hOldPen = (HPEN)SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(0X00, 0X00, 0X00)));
			GetClientRect(hWnd, &rClient);
			unit = rClient.right / 24;
			
			initPaint(hWnd);
			SetBkMode(hdc, TRANSPARENT);
			/*char x[64] = "test";
			TCHAR X[64];
			MultiByteToWideChar(CP_ACP, 0, x, strlen(x) + 1, X, 64);
			TextOut(hdc, rClient.right / 2, rClient.bottom / 2, X, lstrlen(X)); */
			for (int i = 0; i < numofobj; i++) {
				paintLine(hWnd, i,0);
			}
			int a, b;

			nodeset.clear();
			for (a = 0; a < numofobj - 1; a++) {
				for (b = a + 1; b < numofobj; b++) {
					intersect(hWnd,a, b);
				}
			}

			//输出交点个数
			string s = "当前交点个数：" + to_string(nodeset.size());
			TCHAR S[64];
			SetBkMode(GetDC(hWnd), TRANSPARENT);
			MultiByteToWideChar(CP_ACP, 0, const_cast<char*>(s.c_str()), 64, S, 64);
			TextOut(GetDC(hWnd), 50, 50, S, lstrlen(S));

			EndPaint(hWnd, &ps); 
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int renum[4];
int* string2num(char inputstring[], int kind) {
	renum[0] = renum[1] = renum[2] = renum[3];
	int i = 2, len = 0, count;
	char temp[4][1024];
	for (count = 0; count < kind; count++) {
		len = 0;
		while (1) {
			if (inputstring[i] == ' ' || inputstring[i] == '\t') {
				break;
			}
			temp[count][len] = inputstring[i];
			len++;
			i++;
			if (i == strlen(inputstring)) {
				break;
			}
		}
		if (inputstring[i] == ' ' || inputstring[i] == '\t') {
			i++;
		}
		else if (i == strlen(inputstring)) {
			break;
		}
	}
	for (count = 0; count < kind; count++) {
		renum[count] = atoi(temp[count]);
	}
	return renum;
}

void openFile() {
	ifstream inputFile;
	inputFile.open(filename, ios::in);
	char firstnum[64],lineinfo[64];
	int numoflines;
	inputFile.getline(firstnum, 64);
	numoflines = atoi(firstnum);
	numofobj = numoflines;
	for (int i = 0; i < numoflines; i++) {
		inputFile.getline(lineinfo, 64);
		if ((lineinfo[0] == 'L') || (lineinfo[0] == 'R') || (lineinfo[0] == 'S')) {
			int *xy = string2num(lineinfo, 4);
			lines[i][0] = *xy;
			lines[i][1] = *(xy + 1);
			lines[i][2] = *(xy + 2);
			lines[i][3] = *(xy + 3);
			switch (lineinfo[0])
			{
			case 'L':
				lines[i][4] = 1;
				break;
			case 'R':
				lines[i][4] = 2;
				break;
			case 'S':
				lines[i][4] = 3;
				break;
			default:
				break;
			}
		}
	}
}

void initPaint(HWND hwnd) {
	HDC hdc = GetDC(hwnd);
	RECT rClient;
	HPEN pen = (HPEN)SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(0X00, 0X00, 0X00)));
	GetClientRect(hwnd, &rClient);
	unit = rClient.right / 24;
	centerx = rClient.right / 2;
	centery = rClient.bottom / 2;
	MoveToEx(hdc, 0, centery, NULL);
	LineTo(hdc, centerx*2, centery);

	MoveToEx(hdc, centerx, 0, NULL);
	LineTo(hdc, centerx, centery*2);
	
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, centerx, centery, _T("0"), 1);
	//TextOut(hdc, centerx, centery, _T("(1111111111111111)"), 19);
	/*string s = "当前交点个数：" + to_string(result.size());
	TCHAR S[64];
	MultiByteToWideChar(CP_ACP, 0, const_cast<char*>(s.c_str()), 64, S, 64);
	TextOut(GetDC(hwnd), 50, 50, S, lstrlen(S)); */

	for (int i = 0; i <= 10; i++) {
		TCHAR num[4],negNum[4];
		MultiByteToWideChar(CP_ACP, 0, numConst[i], strlen(numConst[i]) + 1, num,4);
		MultiByteToWideChar(CP_ACP, 0, negnumConst[i], strlen(negnumConst[i]) + 1, negNum, 4);
		TextOut(hdc, centerx + (i+1)*unit, centery, num, lstrlen(num));
		TextOut(hdc, centerx+5, centery - (i+1)*unit, num, lstrlen(num));
		TextOut(hdc, centerx - (i + 1)*unit, centery, negNum, lstrlen(negNum));
		TextOut(hdc, centerx+5, centery + (i + 1)*unit, negNum, lstrlen(negNum));
	}
}

void intersect(HWND hwnd,int i,int j) {
	int a = lines[i][4],b = lines[j][4];
	bool aisXian = (a >= 1) && (a <= 3);
	bool bisXian = (b >= 1) && (b <= 3);
	bool aisYuan = (a == 4);
	bool bisYuan = (b == 4);
	char A='x', B='x';
	switch (a) {
	case 1:
		A = 'L';
		break;
	case 2:
		A = 'R';
		break;
	case 3:
		A = 'S';
		break;
	case 4:
		A = 'C';
		break;
	}
	switch (b) {
	case 1:
		B = 'L';
		break;
	case 2:
		B = 'R';
		break;
	case 3:
		B = 'S';
		break;
	case 4:
		B = 'C';
		break;
	}
	vector<Node> result;
	if (aisXian && bisXian) {
		Line* line1 = new Line(lines[i][0], lines[i][1], lines[i][2], lines[i][3]);
		Line* line2 = new Line(lines[j][0], lines[j][1], lines[j][2], lines[j][3]);
		Intersect* inter = new Intersect();
		result = inter->lineCrossLine(*line1,*line2);
		result = judgeLegalll(A, B, *line1, *line2, result);
		paintIntersect(hwnd, result);
	}
	else if (aisXian && bisYuan) {
		Line* line = new Line(lines[i][0], lines[i][1], lines[i][2], lines[i][3]);
		Circle* circle = new Circle(lines[j][0], lines[j][1], lines[j][2]);
		Intersect* inter = new Intersect();
		result = inter->lineCrossCircle(*line, *circle);
		result = judgeLegallc(A, *line, result);
		paintIntersect(hwnd, result);
	}
	else if (aisYuan && bisXian) {
		Line* line = new Line(lines[j][0], lines[j][1], lines[j][2], lines[j][3]);
		Circle* circle = new Circle(lines[i][0], lines[i][1], lines[i][2]);
		Intersect* inter = new Intersect();
		result = inter->lineCrossCircle(*line, *circle);
		result = judgeLegallc(B, *line, result);
		paintIntersect(hwnd, result);
	}
	else if (aisYuan && bisYuan) {
		Circle* c1 = new Circle(lines[i][0], lines[i][1], lines[i][2]);
		Circle* c2 = new Circle(lines[j][0], lines[j][1], lines[j][2]);
		Intersect* inter = new Intersect();
		result = inter->circleCrossCircle(*c1, *c2);
		paintIntersect(hwnd, result);
	}
	return;
} 

int zeroBoL(double a, double b) {
	if (b - a >= 0) {
		return 1;
	}
	return 0;
}

int judgebetween(double a, double b, double center) {
	if (((center >= a) && (center <= b)) || ((center >= b) && (center <= a))) {
		return 1;
	}
	return 0;
}

int judgeHasIn(Node node) {
	if (nodeset.find(node) == nodeset.end()) {
		return 0;
	}
	else return 1;
}

vector<Node> judgeLegalll(char a, char b, Line l1, Line l2, vector<Node> nodes) {
	vector<Node> result;
	int x11, y11, x12, y12, x21, y21, x22, y22, hasIn;
	double nodex,nodey;
	for (int i = 0; i < nodes.size(); i++) {
		Node node = nodes.at(i);
		if (node.judgeCross == 0) {
			break;
		}
		hasIn = 0;
		if (a == 'R') {
			nodex = node.x;
			nodey = node.y;
			x11 = l1.x1;
			y11 = l1.y1;
			x12 = l1.x2;
			y12 = l1.y2;
			if ((zeroBoL(x11, x12) == zeroBoL(x11, nodex)) && (zeroBoL(y11, y12) == zeroBoL(y11, nodey))) {
				result.push_back(node);
				hasIn = 1;
			}
		}
		if (a == 'S') {
			nodex = node.x;
			nodey = node.y;
			x11 = l1.x1;
			y11 = l1.y1;
			x12 = l1.x2;
			y12 = l1.y2;
			if (judgebetween(x11, x12, nodex) && judgebetween(y11, y12, nodey) && (hasIn == 0)) {
				result.push_back(node);
				hasIn = 1;
			}
		}
		if (b == 'R') {
			nodex = node.x;
			nodey = node.y;
			x21 = l2.x1;
			y21 = l2.y1;
			x22 = l2.x2;
			y22 = l2.y2;
			if ((zeroBoL(x21, x22) == zeroBoL(x21, nodex)) && (zeroBoL(y21, y22) == zeroBoL(y21, nodey)) && (hasIn == 0)) {
				result.push_back(node);
				hasIn = 1;
			}
		}
		if (b == 'S') {
			nodex = node.x;
			nodey = node.y;
			x21 = l2.x1;
			y21 = l2.y1;
			x22 = l2.x2;
			y22 = l2.y2;
			if (judgebetween(x21, x22, nodex) && judgebetween(y21, y22, nodey) && (hasIn == 0)) {
				result.push_back(node);
				hasIn = 1;
			}
		}
		if ((hasIn == 0) && (a == 'L') && (b == 'L')) {
			result.push_back(node);
		}
	}
	return result;
}

vector<Node> judgeLegallc(char a, Line line, vector<Node> nodes) {
	vector<Node> result;
	double nodex, nodey;
	int x1, y1, x2, y2;
	for (int i = 0; i < nodes.size(); i++) {
		Node node = nodes.at(i);
		if (node.judgeCross == 0) {
			break;
		}
		nodex = node.x;
		nodey = node.y;
		if (a == 'R') {
			x1 = line.x1;
			y1 = line.y1;
			x2 = line.x2;
			y2 = line.y2;
			if ((zeroBoL(x1, x2) == zeroBoL(x1, nodex)) && (zeroBoL(y1, y2) == zeroBoL(y1, nodey))) {
				result.push_back(node);
			}
		}
		if (a == 'S') {
			x1 = line.x1;
			y1 = line.y1;
			x2 = line.x2;
			y2 = line.y2;
			if (judgebetween(x1, x2, nodex) && judgebetween(y1, y2, nodey)) {
				result.push_back(node);
			}
		}
		if (a == 'L') {
			result.push_back(node);
		}
	}
	return result;
}

void paintIntersect(HWND hwnd, vector<Node> nodes) {
	double x,y;
	int runover;
	for (runover = 0; runover < (int)nodes.size(); runover++) {
		Node node = nodes.at(runover);
		if (node.judgeCross == 1) {
			if (judgeHasIn(node) == 1) {
				continue;
			}
			nodeset.insert(node);
			TCHAR S[64];
			x = node.x;
			y = node.y;
			string s = "(" + to_string(node.x) + "," + to_string(node.y) + ")";
			HDC hdc = GetDC(hwnd);
			SetBkMode(hdc, TRANSPARENT);
			//SetBkMode(hdc, TRANSPARENT);
			MultiByteToWideChar(CP_ACP, 0, const_cast<char*>(s.c_str()), 64, S, 64);
			TextOut(hdc, (double)centerx + x*(double)unit, (double)centery - y*(double)unit, S, lstrlen(S));
			//TextOut(hdc, centerx, centery, _T("(111111111)"), 12);
		}
	}
} 

void paintLine(HWND hwnd,int i,int special) {
	HDC hdc = GetDC(hwnd);
	RECT rclient;
	HPEN pen = NULL;
	
	if (special == 0) {
		pen = (HPEN)SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB((0 + i * 10) % 256, (0 + i * 10) % 256, (0 + i * 10) % 256)));
	}
	else if (special == 1) {
		pen = (HPEN)SelectObject(hdc, GetStockObject(WHITE_PEN));
	}
	//HPEN pen = (HPEN)SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(0,0,0)));
	HBRUSH bursh = NULL;
	bursh = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
	GetClientRect(hwnd, &rclient);
	SetBkMode(hdc, TRANSPARENT);
	int x1 = lines[i][0];
	int y1 = lines[i][1];
	int x2 = lines[i][2];
	int y2 = lines[i][3];
	double k, b;
	if (x1 != x2) {
		k = ((double)y2 - (double)y1) / ((double)x2 - (double)x1);
		b = (double)y1 - k*(double)x1;
	}
	if (lines[i][4] == 1) {
		if (x1 == x2) {
			MoveToEx(hdc, centerx + x1*unit, 0, NULL);
			LineTo(hdc, centerx + x1*unit, 3000);
		}
		else {
			double x1 = -20;
			double y1 = k*x1 + b;
			double x2 = 20;
			double y2 = k*x2 + b;
			MoveToEx(hdc, centerx + x1*unit, centery - y1*unit, NULL);
			LineTo(hdc, centerx + x2*unit, centery - y2*unit);
		}
	}
	else if (lines[i][4] == 2) {
		int dx = x2 - x1;
		int dy = y2 - y1;
		MoveToEx(hdc, centerx + x1*unit, centery - y1*unit, NULL);
		LineTo(hdc, centerx + (x2 + 10 * dx)*unit, centery - (y2 + 10 * dy)*unit);
	}
	else if (lines[i][4] == 3) {
		MoveToEx(hdc, centerx + x1*unit, centery - y1*unit, NULL);
		LineTo(hdc, centerx + x2*unit, centery - y2*unit);
	}
	else if (lines[i][4] == 4) {
		int x = lines[i][0];
		int y = lines[i][1];
		int r = lines[i][2];
		Ellipse(hdc, centerx + (x - r)*unit, centery - (y + r)*unit, centerx + (x + r)*unit, centery - (y - r)*unit);
	}
	DeleteObject(SelectObject(hdc, pen));
	return;
} 

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Dialog(HWND hdlg,UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	int mId, eId;
	
	int lenth;
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		//MessageBox(NULL, _T("fuck"), _T("fuck"), MB_OK);
			switch (LOWORD(wParam))
			{
			case IDOK:
				lenth = GetDlgItemText(hdlg, IDC_EDIT1, inputstring, 64);
				if (lenth == 0) {
					EndDialog(hdlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
				}
				MessageBox(NULL, _T("输入成功！"), _T("输入成功！"), MB_OK);
				EndDialog(hdlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			case IDCANCEL:
				EndDialog(hdlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Queren(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hdlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
