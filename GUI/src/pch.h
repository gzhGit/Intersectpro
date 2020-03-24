// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#pragma once
_declspec(dllexport) double* solve_ll(int x11, int y11, int x12, int y12, char c1, int x21, int y21, int x22, int y22, char c2);
_declspec(dllexport) double* solve_lc(int x11, int y11, int x12, int y12, char c1, int x21, int y21, int r, char c);
_declspec(dllexport) double* solve_cc(int x11, int y11, int r1, char c1, int x21, int y21, int r2, char c2);


