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

#define N 4//格子数

#define WIDTH 5//每个格子的长度

//游戏状态
#define S_FAIL 0
#define S_WIN 1
#define S_NORMAL 2
#define S_QUIT 3

class Game2048 {
public:
	Game2048() {
		setTestData();
	}

	//获得游戏状态
	int getStatus() {
		return status;
	}

	//处理按键
	void processInput() {
		char ch = getch();
		if (ch >= 'a'&&ch <= 'z')
		{
			ch -= 32;
		}
		if (ch == 'Q')
		{
			status = S_QUIT;
		}
		else
		{
			status = (status + 1) % 3;
		}
	}
	//绘制游戏界面
	void Draw() {
		clear();
		const int offset = 12;//居中偏移
		for (int i = 0; i <= N; ++i)
		{
			for (int j = 0; j <= N; ++j)
			{
				//相交点
				drawItem(i * 2, 1 + j * WIDTH + offset, '+');

				//竖线
				if (i != N)
				{
					drawItem(i * 2 + 1, 1 + j * WIDTH + offset, '|');
				}

				//横线
				for (int k = 1; j != N && k < WIDTH; ++k)
				{
					drawItem(i * 2, 1 + j * WIDTH + k + offset, '-');
				}

				//每个格子里面的数
				if (i != N && j != N)
				{
					drawNum(i * 2 + 1, (j + 1)*WIDTH + offset, data[i][j]);
				}
			}
		}
		mvprintw(2 * N + 2, (5 * (N - 4) - 1) / 2, "W(UP),S(DOWN),A(LEFT),D(RIGHT),R(RESTART),Q(QUIT)");

		if (status == S_WIN)
		{
			mvprintw(N, 5 * N / 2 - 1, " YOU WIN,PRESS R TO CONTINUE ");
		}
		else if (status == S_FAIL) {
			mvprintw(N, 5 * N / 2 - 1, " YOU LOSE,PRESS R TO CONTINUE ");
		}
	}

	//设置初始数据
	void setTestData() {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				data[i][j] = 16 << i << j;
				/*
				data[i][0] = 2;
				data[i][1] = 4;
				data[i][2] = 8;
				data[i][3] = 16;*/
			}
		}
	}

private:
	void drawItem(int row, int col, char c) {
		move(row, col);
		addch(c);
	}
	void drawNum(int row, int col, int num) {
		while (num > 0)
		{
			drawItem(row, col, num % 10 + '0');
			num /= 10;
			--col;
		}
	}
private:
	int data[N][N];
	int status;
};

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


	Game2048 game;
	char ch = 'n';
	do
	{
		game.Draw();
		game.processInput();
	} while (S_QUIT != game.getStatus());

	shutdown();
	return 0;
}

