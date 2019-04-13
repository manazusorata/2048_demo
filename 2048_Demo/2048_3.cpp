// 2048_Demo.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include "pch.h"
#include<string>
#include<vector>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include"curses.h"
#include <iostream>

#define N 4//������

#define WIDTH 5//ÿ�����ӵĳ���

//��Ϸ״̬
#define S_FAIL 0
#define S_WIN 1
#define S_NORMAL 2
#define S_QUIT 3

class Game2048 {
public:
	Game2048() {
		setTestData();
	}

	//�����Ϸ״̬
	int getStatus() {
		return status;
	}

	//��������
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
	//������Ϸ����
	void Draw() {
		clear();
		const int offset = 12;//����ƫ��
		for (int i = 0; i <= N; ++i)
		{
			for (int j = 0; j <= N; ++j)
			{
				//�ཻ��
				drawItem(i * 2, 1 + j * WIDTH + offset, '+');

				//����
				if (i != N)
				{
					drawItem(i * 2 + 1, 1 + j * WIDTH + offset, '|');
				}

				//����
				for (int k = 1; j != N && k < WIDTH; ++k)
				{
					drawItem(i * 2, 1 + j * WIDTH + k + offset, '-');
				}

				//ÿ�������������
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

	//���ó�ʼ����
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
	//��ʼ����Ļ
	initscr();
	//��������Ҫ����س�ֱ�ӽ���
	cbreak();
	//��������ʾ
	noecho();
	//���ع��
	curs_set(0);
	//�����
	srand(time(NULL));
}

void shutdown() {
	//ncurse����
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
