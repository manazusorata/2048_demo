// 2048_Demo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include<string>
#include<vector>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include"curses.h"
#include <iostream>



void initialize() {
	//初始化屏幕
	initscr();
	//按键不需要输入回车直接交互
	cbreak();
	//按键不显示
	noecho();
	//隐藏光标
	curs_set(0);
	//随机数
	srand(time(NULL));
}

void shutdown() {
	//ncurse清理
	endwin();
}

int main()
{
	initialize();

	char ch = 'n';
	do
	{
		move(5, 5);
		addch(ch);
		mvprintw(2, 2, "manazusorata");
		ch = getch();
	} while (ch != 'Q'&&ch != 'q');

	shutdown();
	return 0;
}

