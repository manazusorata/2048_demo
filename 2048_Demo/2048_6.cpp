// 2048_Demo.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include "pch.h"
#include"curses.h"
#include<vector>
#include<string>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include <iostream>
using namespace std;

//������
#define N 6
//ÿ�����ӵĳ���
#define WIDTH 10

//��Ϸ״̬
#define S_FAIL 0
#define S_WIN 1
#define S_NORMAL 2
#define S_QUIT 3

//ʤ������
#define TARGET 2048

class Game2048 {
public:
	Game2048():status(S_NORMAL) {
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
		if (status == S_NORMAL)
		{
			bool updated = false;
			if (ch == 'A')
			{
				updated = moveLeft();
			}
			else if (ch=='S')
			{	//�����ƶ�
				rotate();
				rotate();
				rotate();
				updated = moveLeft();
				rotate();
			}
			else if (ch=='D')
			{	//�����ƶ�
				rotate();
				rotate();
				updated = moveLeft();
				rotate();
				rotate();
			}
			else if (ch=='W')
			{	//�����ƶ�
				rotate();
				updated = moveLeft();
				rotate();
				rotate();
				rotate();
			}

			if (updated)
			{
				randNew();
				if (isOver())
				{
					status = S_FAIL;
				}
			}
		}
		if (ch == 'Q')
		{
			status = S_QUIT;
		}
		else if (ch == 'R')
		{
			restart();
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
				data[i][j] = 2 << (1 + rand() % 7);
			}
		}
	}

private:
	//�ж���Ϸ�Ƿ����
	bool isOver() {
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if ((j + 1 < N) && (data[i][j] * data[i][j + 1] == 0 || data[i][j] == data[i][j + 1]))
				{
					return false;
				}
				if ((i + 1 < N) && (data[i][j] * data[i + 1][j] == 0 || data[i][j] == data[i + 1][j]))
				{

				}
			}
		}
		return true;
	}

	//�����ƶ�
	bool moveLeft() {
		int temp[N][N];
		//���д���
		for (int i = 0; i < N; i++)
		{
			int currentWritePos = 0;
			int lastValue = 0;
			for (int j = 0; j < N; j++)
			{
				temp[i][j] = data[i][j];
				if (data[i][j] == 0)
				{
					continue;
				}
				if (lastValue == 0)
				{
					lastValue = data[i][j];
				}
				else
				{
					if (lastValue == data[i][j])
					{
						data[i][currentWritePos] = lastValue * 2;
						lastValue = 0;
						//�ж��Ƿ�ʤ��
						if (data[i][currentWritePos] == TARGET)
						{
							status = S_WIN;
						}
					}
					else
					{
						data[i][currentWritePos] = lastValue;
						lastValue = data[i][j];
					}
					++currentWritePos;
				}
				data[i][j] = 0;
			}
			if (lastValue != 0)
			{
				data[i][currentWritePos] = lastValue;
			}
		}
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (data[i][j]!=temp[i][j])
				{
					return true;
				}
			}
		}
		return false;
	}

	//������ʱ����ת90��
	void rotate() {
		int temp[N][N] = { 0 };
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				temp[i][j] = data[j][N - i - 1];
			}
		}
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				data[i][j] = temp[i][j];
			}
		}
	}

	//���¿�ʼ��Ϸ
	void restart() {
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				data[i][j] = 0;
			}
		}

		randNew();
		randNew();
		status = S_NORMAL;
	}

	//�漴����һ���µ�����
	bool randNew() {

		vector<int> emptyPos;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (data[i][j] == 0)
				{
					emptyPos.push_back(i*N + j);
				}
			}
		}

		if (emptyPos.size() == 0)
		{
			return false;
		}

		//�漴�Ҹ���λ
		int value = emptyPos[rand() % emptyPos.size()];
		//10%�ĸ��ʵõ�4
		data[value / N][value%N] = rand() % 10 == 1 ? 4 : 2;
		return true;
	}

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
	do
	{
		game.Draw();
		game.processInput();
	} while (S_QUIT != game.getStatus());

	shutdown();
	return 0;
}
