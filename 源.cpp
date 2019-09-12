#include <graphics.h>
#include <conio.h>
#include <easyx.h>
#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>
#include <process.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
IMAGE brick;
IMAGE iron;
IMAGE leaf;
IMAGE leaf2;
IMAGE water;
IMAGE heart;
IMAGE brokenheart;
IMAGE tank00;
IMAGE tank01;
IMAGE tank02;
IMAGE tank03;
IMAGE ai00;
IMAGE ai01;
IMAGE ai02;
IMAGE ai03;
IMAGE bullet00;//第一位方向 第二位类型 
IMAGE bullet01;
IMAGE bullet0x;
IMAGE bullet10;
IMAGE bullet11;
IMAGE bullet1x;
IMAGE bullet20;
IMAGE bullet21;
IMAGE bullet2x;
IMAGE bullet30;
IMAGE bullet31;
IMAGE bullet3x;
IMAGE boom;
IMAGE welcomebg;
IMAGE endgame0;
IMAGE endgame0x;
IMAGE endgame1;
IMAGE endgame1x;
IMAGE endgame2;
IMAGE endgame2x;

int initializewelcome();
int initializemenu();
void initializechart();
void initializeins();
int initializechosedif();
int initialplayground(int level, int * Score,char* Name);
void loadplayground(char * Name, int time, int * Score, int life, int **buffmap, int **leafmap, struct bullet * headbullet, int flag,int rate);
void move(int**buffmap, int direction, struct tank * tank);
struct bullet * fire(struct tank* tank, int ** buffmap, struct bullet* headbullet);
struct bullet * bulletmove(struct bullet* headbullet, int **buffmap, struct tank* headAI, int* Rate, int* Score, int * Life ,int level);
struct tank * newAI(struct tank* headAI, int ** buffmap);
struct tank * AIaction(struct tank* headAI, int ** buffmap, struct bullet* headbullet,int * Flag);
struct tank * AIdead(struct tank* headAI,int y,int x, int ** buffmap,int* Rate,int* Score, int level);
int endgame(int score, char* Name,int type);

struct tank {
	int tankx;//二维数组坐标
	int tanky;
	int shang = 76 + tanky * 20;//像素坐标
	int zuo = 100 + tankx * 20;
	int xia = shang + 40;
	int you = zuo + 40;
	int tankdir;//方向：0向上 1向左 2向下 3向右
	int type;//0 己方 1敌方
	int ismove = 0;//0：停止状态 1：正在移动
	int life = 1;//1： 存活 0：死亡
	tank * nexttank = NULL;
	clock_t startmove = 0, nextmove = 0;
	clock_t startfire = 0, nextfire = 0;
};

struct bullet {
	int x = 0;//像素
	int y = 0;
	int dir = -1;
	int type = 0;//0 己方 1敌方
	int bulletx1 = 0;//二维数组
	int bullety1 = 0;
	int bulletx2 = 0;
	int bullety2 = 0;
	int i = 0;
	int state;//1存活  0已废
	bullet * next = NULL;
};

struct player {
	char * Name;
	char *score;
};

//主函数流程控制
int main() {
	PlaySound("material\\New Divide.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	initgraph(1000, 750);
	setfillcolor(BLACK);
out1:int i1 = initializewelcome();//初始化开始页面
	int i2 = 0;//目录页返回值
	int i3 = 0;//选择难度返回值
	int i4 = 0;//死亡原因
	int i5 = 0;
	int score = 0;
	int * Score = &score;
	char Name[21] = {0};


	if (i1 == 0) {
out2:i2 = initializemenu();//目录页
	}
	else {
		closegraph();//程序结束
		EndBatchDraw();
		return 0;
	}

	if (i2 == 4) {
		goto out1;//回到开始页面
	}
	else if (i2 == 2) {
		initializeins();//操作指南
		goto out2;//回到目录
	}
	else if (i2 == 3) {
		initializechart();//排行榜
		goto out2;//回到目录
	}
	else {
		i3 = initializechosedif();
	}

	if (i3 == 0) {
		goto out2;//回到目录
	}
	else {
		i4= initialplayground(i3,Score,Name);
	}
	i5=endgame(score,  Name, i4);

	if (i5==1) {
		goto out1;
	}
	else {
		EndBatchDraw();
		return 0;
	}
}

//初始化开始页面
int	initializewelcome() {
	fillrectangle(100, 75, 900, 675);
	loadimage(&welcomebg, _T("material\\welcomebg5.jpg"), 799, 599);
	putimage(101, 76, &welcomebg);
	char welcomepg1[100] = { "TANK 00" };
	setbkmode(TRANSPARENT);
	settextstyle(130, 58, _T("Trajan Pro"));
	outtextxy(120, 95, welcomepg1);

	char welcomepg2[100] = { "START" };
	setbkmode(TRANSPARENT);
	settextstyle(90, 45, _T("Trajan Pro"));
	outtextxy(370, 400, welcomepg2);
	setlinestyle(NULL | NULL, 3);
	rectangle(300, 400, 685, 490);

	char welcomepg3[100] = { "EXIT" };
	setbkmode(TRANSPARENT);
	settextstyle(90, 45, _T("Trajan Pro"));
	outtextxy(400, 510, welcomepg3);
	rectangle(300, 510, 685, 600);

	char welcomepg4[100] = { "produced by KANXINGBO 18071105" };
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(20, 9, _T("Lithos Pro Regular"));
	outtextxy(110, 655, welcomepg4);

	MOUSEMSG m1 = GetMouseMsg();
	int i = 0;
	while (1) {
		if (MouseHit()) {
			m1 = GetMouseMsg();
			if (m1.uMsg == WM_LBUTTONDOWN) {
				if ((m1.x >= 300 && m1.x <= 685) && (m1.y >= 400 && m1.y <= 490)) {
					HRGN Area1;
					Area1 = CreateRectRgn(101, 76, 899, 674);
					setcliprgn(Area1);
					clearcliprgn();
					loadimage(&welcomebg, _T("material\\welcomebg5.jpg"), 799, 599);
					putimage(101, 76, &welcomebg);
					return 0;
				}
				if ((m1.x >= 300 && m1.x <= 685) && (m1.y >= 510 && m1.y <= 600)) {
					return 1;
				}
			}
		}
	}
}

//目录页
int initializemenu() {
	char menupg1[100] = { "MENU" };
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(200, 66, _T("Trajan Pro"));
	outtextxy(325, 75, menupg1);

	setlinestyle(NULL | NULL, 3);
	rectangle(200, 350, 800, 420);
	char menupg2[100] = { "Select difficulty level" };
	settextstyle(65, 28, _T("Trajan Pro"));
	outtextxy(210, 350, menupg2);

	rectangle(200, 430, 800, 500);
	char menupg3[100] = { "Instruction" };
	settextstyle(65, 28, _T("Trajan Pro"));
	outtextxy(350, 430, menupg3);

	rectangle(200, 510, 800, 580);
	char menupg4[100] = { "Ranking list" };
	settextstyle(65, 28, _T("Trajan Pro"));
	outtextxy(340, 510, menupg4);

	rectangle(200, 590, 800, 660);
	char menupg5[100] = { "Back" };
	settextstyle(65, 28, _T("Trajan Pro"));
	outtextxy(440, 590, menupg5);

	MOUSEMSG m1 = GetMouseMsg();
	int i = 0;
	while (1) {
		if (MouseHit()) {
			m1 = GetMouseMsg();
			if (m1.uMsg == WM_LBUTTONDOWN) {
				if ((m1.x >= 200 && m1.x <= 800) && (m1.y >= 350 && m1.y <= 420)) {
					i = 1;
					break;
				}
				else if ((m1.x >= 200 && m1.x <= 800) && (m1.y >= 430 && m1.y <= 500)) {
					i = 2;
					break;
				}
				else if ((m1.x >= 200 && m1.x <= 800) && (m1.y >= 510 && m1.y <= 580)) {
					i = 3;
					break;
				}
				else if ((m1.x >= 200 && m1.x <= 800) && (m1.y >= 590 && m1.y <= 660)) {
					HRGN Area1;
					Area1 = CreateRectRgn(101, 76, 899, 674);
					setcliprgn(Area1);
					clearcliprgn();
					i = 4;
					break;
				}
				else {
					continue;
				}
			}
		}
	}
	return i;
}

//排行榜
void initializechart() {
	HRGN Area1;
	IMAGE welcomebg;
	Area1 = CreateRectRgn(101, 76, 899, 674);
	setcliprgn(Area1);
	clearcliprgn();
	loadimage(&welcomebg, _T("material\\welcomebg5.jpg"), 799, 599);
	putimage(101, 76, &welcomebg);

	char chartpg1[100] = { "Ranking list" };
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(150, 48, _T("Trajan Pro"));
	outtextxy(220, 75, chartpg1);

	setlinestyle(NULL | NULL, 3);
	rectangle(790, 620, 895, 670);
	char chartpg2[100] = { "Back" };
	settextstyle(50, 20, _T("Trajan Pro"));
	outtextxy(800, 620, chartpg2);

	FILE * fp;
	errno_t err;
	err = fopen_s(&fp, "material\\rank.txt", "r");
	player r[9];
	char ch;
	int i = 0; int j = 0;
	ch = getc(fp);
	while (ch != EOF) {
		j = 0;
		r[i].Name = (char*)malloc(sizeof(char) * 10);
		r[i].score = (char*)malloc(sizeof(char) * 10);
		while (ch != '\n') {
			r[i].Name[j] = ch;
			j++;
			ch = getc(fp);
		}
		r[i].Name[j] = 0;

		j = 0;
		ch = getc(fp);
		while (ch != '\n') {
			r[i].score[j] = ch;
			j++;
			ch = getc(fp);
		}
		r[i].score[j] = 0;

		ch = getc(fp);
		i++;
	}
	fclose(fp);

	char chartpg3[100] = { "player" };
	settextstyle(75, 24, _T("Trajan Pro"));
	outtextxy(200, 200, chartpg3);

	char chartpg4[100] = { "score" };
	settextstyle(75, 24, _T("Trajan Pro"));
	outtextxy(600, 200, chartpg4);

	settextstyle(75, 24, _T("Courier New"));
	settextcolor(LIGHTCYAN);
	outtextxy(200, 270, r[0].Name);
	outtextxy(200, 350, r[1].Name);
	outtextxy(200, 430, r[2].Name);
	outtextxy(200, 510, r[3].Name);
	outtextxy(200, 590, r[4].Name);

	settextstyle(75, 24, _T("Trajan Pro"));
	settextcolor(WHITE);
	outtextxy(600, 270, r[0].score);
	outtextxy(600, 350, r[1].score);
	outtextxy(600, 430, r[2].score);
	outtextxy(600, 510, r[3].score);
	outtextxy(600, 590, r[4].score);

	MOUSEMSG m1 = GetMouseMsg();
	while (1) {
		if (MouseHit()) {
			m1 = GetMouseMsg();
			if (m1.uMsg == WM_LBUTTONDOWN) {
				if ((m1.x >= 800 && m1.x <= 900) && (m1.y >= 620 && m1.y <= 675)) {
					HRGN Area1;
					IMAGE welcomebg;
					Area1 = CreateRectRgn(101, 76, 899, 674);
					setcliprgn(Area1);
					clearcliprgn();
					loadimage(&welcomebg, _T("material\\welcomebg5.jpg"), 799, 599);
					putimage(101, 76, &welcomebg);
					return;
				}
				else {
					continue;
				}
			}
		}
	}
}

//操作提示
void initializeins() {
	HRGN Area1;
	IMAGE welcomebg;
	Area1 = CreateRectRgn(101, 76, 899, 674);
	setcliprgn(Area1);
	clearcliprgn();
	loadimage(&welcomebg, _T("material\\welcomebg5.jpg"), 799, 599);
	putimage(101, 76, &welcomebg);

	char instructionpg1[100] = { "Instruction" };
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(150, 48, _T("Trajan Pro"));
	outtextxy(220, 75, instructionpg1);

	setlinestyle(NULL | NULL, 3);
	rectangle(790, 620, 895, 670);
	char instructionpg2[100] = { "Back" };
	settextstyle(50, 20, _T("Trajan Pro"));
	outtextxy(800, 620, instructionpg2);

	char instructionpg3[200] = { "Use                to move your tank. " };
	settextstyle(50, 25, _T("Trajan Pro"));
	outtextxy(140, 300, instructionpg3);

	char instructionpg4[200] = { "Press      to attack." };
	settextstyle(50, 25, _T("Trajan Pro"));
	outtextxy(260, 350, instructionpg4);

	char instructionpg5[200] = { "Make sure your base is not under attack." };
	settextstyle(40, 20, _T("Trajan Pro"));
	outtextxy(100, 400, instructionpg5);

	char instructionpg6[200] = { "And keep your tank alive!" };
	settextstyle(50, 25, _T("Trajan Pro"));
	outtextxy(200, 450, instructionpg6);

	char instructionpg7[200] = { "WASD" };
	settextcolor(LIGHTCYAN);
	settextstyle(65, 35, _T("Trajan Pro"));
	outtextxy(230, 280, instructionpg7);

	char instructionpg8[200] = { "J" };
	settextstyle(60, 35, _T("Trajan Pro"));
	outtextxy(410, 340, instructionpg8);

	MOUSEMSG m1 = GetMouseMsg();
	while (1) {
		if (MouseHit()) {
			m1 = GetMouseMsg();
			if (m1.uMsg == WM_LBUTTONDOWN) {
				if ((m1.x >= 800 && m1.x <= 900) && (m1.y >= 620 && m1.y <= 675)) {
					HRGN Area1;
					IMAGE welcomebg;
					Area1 = CreateRectRgn(101, 76, 899, 674);
					setcliprgn(Area1);
					clearcliprgn();
					loadimage(&welcomebg, _T("material\\welcomebg5.jpg"), 799, 599);
					putimage(101, 76, &welcomebg);
					return;
				}
				else {
					continue;
				}
			}
		}
	}
}

//选择难度
int initializechosedif() {
	HRGN Area1;
	Area1 = CreateRectRgn(101, 76, 899, 674);
	setcliprgn(Area1);
	clearcliprgn();
	IMAGE welcomebg;
	loadimage(&welcomebg, _T("material\\welcomebg5.jpg"), 799, 599);
	putimage(101, 76, &welcomebg);

	setlinestyle(NULL | NULL, 3);
	rectangle(790, 620, 895, 670);
	char chosedifpg1[100] = { "Back" };
	settextstyle(50, 20, _T("Trajan Pro"));
	outtextxy(800, 620, chosedifpg1);

	char chosedifpg2[100] = { "Select difficuty level" };
	settextstyle(80, 40, _T("Trajan Pro"));
	outtextxy(110, 80, chosedifpg2);

	setlinestyle(NULL | NULL, 1);
	rectangle(250, 220, 750, 520);

	IMAGE level1;
	loadimage(&level1, _T("material\\level1.jpg"), 499, 299);
	putimage(251, 221, &level1);
	char chosedifpg3[100] = { "level1" };
	settextstyle(60, 30, _T("Trajan Pro"));
	outtextxy(255, 460, chosedifpg3);

	setlinestyle(NULL | NULL, 1);
	POINT pts1[] = { {210, 340}, {210,410}, {160, 375} };
	setfillcolor(WHITE);
	fillpolygon(pts1, 3);
	setlinestyle(NULL | NULL, 1);
	POINT pts2[] = { {790, 340}, {790,410}, {830, 375} };
	setfillcolor(WHITE);
	fillpolygon(pts2, 3);

	char chosedifpg4[100] = { "Select!" };
	settextstyle(70, 35, _T("Trajan Pro"));
	outtextxy(390, 560, chosedifpg4);
	setlinestyle(NULL | NULL, 3);
	rectangle(385, 560, 620, 630);

	int level = 1;
	MOUSEMSG m1 = GetMouseMsg();
	while (1) {
		while (1) {
			if (MouseHit()) {
				m1 = GetMouseMsg();
				if (m1.uMsg == WM_LBUTTONDOWN) {
					if ((m1.x >= 800 && m1.x <= 900) && (m1.y >= 620 && m1.y <= 675)) {
						HRGN Area1;
						IMAGE welcomebg;
						Area1 = CreateRectRgn(101, 76, 899, 674);
						setcliprgn(Area1);
						clearcliprgn();
						loadimage(&welcomebg, _T("material\\welcomebg5.jpg"), 799, 599);
						putimage(101, 76, &welcomebg);
						return 0;
					}
					if ((m1.x >= 160 && m1.x <= 210) && (m1.y >= 340 && m1.y <= 410)) {
						if (level == 1) {
							level = 3;
							break;
						}
						else {
							level--;
							break;
						}
					}
					if ((m1.x >= 790 && m1.x <= 830) && (m1.y >= 340 && m1.y <= 410)) {
						if (level == 3) {
							level = 1;
							break;
						}
						else {
							level++;
							break;
						}
					}
					if ((m1.x >= 385 && m1.x <= 620) && (m1.y >= 560 && m1.y <= 630)) {
						return level;
					}
				}
			}
		}
		if (level == 1) {
			HRGN Area2;
			Area2 = CreateRectRgn(251, 221, 749, 519);
			setcliprgn(Area2);
			clearcliprgn();
			IMAGE level1;
			loadimage(&level1, _T("material\\level1.jpg"), 499, 299);
			putimage(251, 221, &level1);
			outtextxy(255, 460, chosedifpg3);
		}
		else if (level == 2) {
			HRGN Area2;
			Area2 = CreateRectRgn(251, 221, 749, 519);
			setcliprgn(Area2);
			clearcliprgn();
			IMAGE level2;
			loadimage(&level2, _T("material\\level2.jpg"), 499, 299);
			putimage(251, 221, &level2);
			char chosedifpg4[100] = { "level2" };
			settextstyle(60, 30, _T("Trajan Pro"));
			outtextxy(255, 460, chosedifpg4);
		}

		else {
			HRGN Area2;
			Area2 = CreateRectRgn(251, 221, 749, 519);
			setcliprgn(Area2);
			clearcliprgn();
			IMAGE level3;
			loadimage(&level3, _T("material\\level3.jpg"), 499, 299);
			putimage(251, 221, &level3);
			char chosedifpg5[100] = { "level3" };
			settextstyle(60, 30, _T("Trajan Pro"));
			outtextxy(255, 460, chosedifpg5);
		}
	}
}

//主程序
int initialplayground(int level,int * Score,char * Name) {
	HRGN Area1;
	Area1 = CreateRectRgn(101, 76, 899, 674);
	setcliprgn(Area1);
	clearcliprgn();

	int ltime = 90;
	int life = 6;
	int rate=0;
	int * Rate=&rate;
	int * Life = &life;
	int type;

	char playpg1[100] = { "your name?" };
	setbkmode(TRANSPARENT);
	settextstyle(60, 30, _T("Trajan Pro"));
	outtextxy(350, 300, playpg1);

	//输入并显示姓名
	char ch;
	int i = 0;
	int x = 400;
	while (1) {
		HRGN Area1;
		Area1 = CreateRectRgn(101, 76, 899, 674);
		setcliprgn(Area1);
		ch = _getch();
		if (i == 20) {
			break;
		}

		//按回车
		if (ch == 13) {
			if (Name[0] == 0) {
				for (int i = 1; i <= 3; i++) {
					char playpg2[100] = { "!a blank name is not allowed!" };
					settextcolor(RED);
					setbkmode(TRANSPARENT);
					settextstyle(50, 25, _T("Trajan Pro"));
					outtextxy(180, 400, playpg2);
					Sleep(1000);
					HRGN Area2;
					Area2 = CreateRectRgn(170, 400, 899, 450);
 					clearcliprgn();
				}
				continue;
			}
			break;
		}

		//按退格
		if (ch == 8) {
			i = 0;
			Name[1] = 0;
			HRGN Area1;
			Area1 = CreateRectRgn(101, 76, 899, 674);
			setcliprgn(Area1);
			clearcliprgn();

			char playpg1[100] = { "your name?" };
			settextcolor(WHITE);
			setbkmode(TRANSPARENT);
			settextstyle(60, 30, _T("Trajan Pro"));
			outtextxy(350, 300, playpg1);
			x = 400;
			continue;
		}
		if (ch != ' ') {
			settextstyle(40, 20, _T("Courier New"));
			settextcolor(LIGHTCYAN);
			outtextxy(x, 390, ch);
			x += 20;
			Name[i] = ch;
			i++;
		}
	}

	setcliprgn(Area1);
	clearcliprgn();

	PlaySound("material\\开启新征程剪辑.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

	//输入地图
	//0：空格  1：砖墙  2：铁块  3：树丛  4：河流  5：核心  
	//6：我方坦克核心向上 11：我方坦克核心向左 12：我方坦克核心向下 13：我方坦克核心向右 10：我方坦克身体 
	//7：敌方坦克核心向上 21: 敌方坦克核心向左 22：敌方坦克核心向下 23：敌方坦克核心向右 20：敌方坦克身体 

	//地图
	int map[30][40] = { 0 };
	if (level == 1) {
		for (int i = 2; i <= 11; i++) {
			map[i][2] = 1; map[i][10] = 1;
			map[i][3] = 1; map[i][11] = 1;
			map[i][28] = 1; map[i][29] = 1;
			map[i][36] = 1; map[i][37] = 1;
		}
		for (int i = 2; i <= 15; i++) {
			map[i][6] = 1; map[i][7] = 1;
			map[i][32] = 1; map[i][33] = 1;
		}
		for (int i = 2; i <= 9; i++) {
			map[i][16] = 1; map[i][17] = 1; map[i][18] = 1;
			map[i][21] = 1; map[i][22] = 1; map[i][23] = 1;
		}
		for (int i = 16; i <= 23; i++) {
			map[12][i] = 1; map[13][i] = 1;
		}
		for (int i = 6; i <= 11; i++) {
			map[18][i] = 1; map[19][i] = 1;
		}
		for (int i = 28; i <= 33; i++) {
			map[18][i] = 1; map[19][i] = 1;
		}
		for (int i = 22; i <= 27; i++) {
			map[i][6] = 1; map[i][7] = 1;
			map[i][10] = 1; map[i][11] = 1;
			map[i][28] = 1; map[i][29] = 1;
			map[i][32] = 1; map[i][33] = 1;
		}
		for (int i = 18; i <= 23; i++) {
			map[i][16] = 1; map[i][17] = 1; map[i][18] = 1;
			map[i][21] = 1; map[i][22] = 1; map[i][23] = 1;
		}
		map[20][19] = 1; map[21][20] = 1;
		map[20][20] = 1; map[21][19] = 1;
		map[27][18] = 1; map[27][19] = 1; map[27][20] = 1; map[27][21] = 1;
		map[28][18] = 1; map[28][21] = 1;
		map[29][18] = 1; map[29][21] = 1;
		for (int i = 0; i <= 3; i++) {
			map[18][i] = 2; map[19][i] = 2;
		}
		for (int i = 36; i <= 39; i++) {
			map[18][i] = 2; map[19][i] = 2;
		}
		for (int i = 14; i <= 25; i++) {
			map[14][i] = 2; map[15][i] = 2;
		}
		map[28][19] = 5; map[28][20] = 8;
		map[29][19] = 8; map[29][20] = 8;
		map[28][16] = 6; map[28][17] = 10;
		map[29][16] = 10; map[29][17] = 10;
	}


	if (level == 2) {
		for (int i = 25; i <= 30; i++) {
			map[0][i] = 3; map[1][i] = 3;
		}
		for (int i = 2; i <= 14; i++) {
			map[i][2] = 1; map[i][3] = 1;
		}
		for (int i = 9; i <= 14; i++) {
			map[i][4] = 1; map[i][5] = 1;
		}
		for (int i = 2; i <= 11; i++) {
			map[i][8] = 2; map[i][9] = 2; map[i][12] = 1;
			map[i][28] = 1; map[i][29] = 3; map[i][30] = 3;
			map[i][38] = 3; map[i][39] = 3;
		}
		for (int i = 8; i <= 10; i++) {
			map[i][13] = 1;
		}
		map[11][12] = 2; map[11][13] = 2;
		map[12][12] = 2; map[12][13] = 2;
		for (int i = 11; i <= 14; i++) {
			map[i][14] = 1;
		}
		map[4][19] = 1; map[4][20] = 1;
		map[5][19] = 1; map[5][20] = 1;
		map[6][19] = 2; map[6][20] = 2;
		map[7][19] = 2; map[7][20] = 2;
		for (int i = 8; i <= 11; i++) {
			map[i][19] = 1; map[i][20] = 1;
		}
		for (int i = 10; i <= 16; i++) {
			map[i][17] = 3; map[i][18] = 3;
			map[i][21] = 3; map[i][22] = 3;
		}
		for (int i = 12; i <= 18; i++) {
			map[i][19] = 3; map[i][20] = 3;
		}
		for (int i = 15; i <= 18; i++) {
			map[17][i] = 1; map[18][i] = 1;
		}
		for (int i = 21; i <= 24; i++) {
			map[17][i] = 1; map[18][i] = 1;
		}
		for (int i = 2; i <= 7; i++) {
			map[31][i] = 1; map[34][i] = 1; map[35][i] = 1;
		}
		for (int i = 6; i <= 11; i++) {
			map[i][27] = 1;
		}
		for (int i = 12; i <= 15; i++) {
			map[i][29] = 2;
		}
		for (int i = 34; i <= 39; i++) {
			map[12][i] = 3; map[13][i] = 3;
		}
		for (int i = 36; i <= 39; i++) {
			map[14][i] = 1; map[15][i] = 1;
			map[16][i] = 1; map[17][i] = 1;
		}
		for (int i = 19; i <= 22; i++) {
			map[i][0] = 2; map[i][1] = 2;
		}
		for (int i = 25; i <= 29; i++) {
			map[i][0] = 3; map[i][1] = 3;
		}
		for (int i = 2; i <= 5; i++) {
			map[21][i] = 2; map[22][i] = 2;
			map[25][i] = 1; map[26][i] = 1;
		}
		for (int i = 16; i <= 23; i++) {
			map[21][i] = 1; map[22][i] = 1;
		}
		for (int i = 34; i <= 39; i++) {
			map[21][i] = 2; map[22][i] = 2;
		}
		for (int i = 22; i <= 25; i++) {
			map[i][11] = 1; map[i][12] = 1;
		}
		for (int i = 22; i <= 25; i++) {
			map[i][27] = 1; map[i][28] = 1;
		}
		map[26][13] = 1; map[26][14] = 1;
		map[26][25] = 1; map[26][26] = 1;
		for (int i = 23; i <= 29; i++) {
			map[i][34] = 3; map[i][35] = 3;
		}
		for (int i = 36; i <= 39; i++) {
			map[23][i] = 3; map[24][i] = 3;
			map[25][i] = 1; map[26][i] = 1;
			map[27][i] = 1; map[28][i] = 1;
			map[29][i] = 1;
		}
		for (int i = 29; i <= 33; i++) {
			map[24][i] = 3; map[25][i] = 3;
			map[28][i] = 1; map[29][i] = 1;
		}
		map[28][19] = 5; map[28][20] = 8;
		map[29][19] = 8; map[29][20] = 8;
		for (int i = 27; i <= 29; i++) {
			map[i][18] = 1; map[i][21] = 1;
		}
		map[27][19] = 1; map[27][20] = 1;
		map[28][16] = 6; map[28][17] = 10;
		map[29][16] = 10; map[29][17] = 10;
	}


	if (level == 3) {
		for (int i = 3; i <= 8; i++) {//纵向填充
			map[i][0] = 3; map[i][1] = 3;
		}
		for (int i = 2; i <= 6; i++) {//横向填充
			map[5][i] = 3; map[6][i] = 3;
		}
		for (int i = 2; i <= 7; i++) {//横向填充
			map[3][i] = 1; map[4][i] = 1;
		}
		for (int i = 0; i <= 2; i++) {//纵向填充
			map[i][4] = 1; map[i][5] = 1;
		}
		for (int i = 0; i <= 6; i++) {//纵向填充
			map[i][12] = 1; map[i][13] = 1;
			map[i][26] = 1; map[i][27] = 1;
		}
		for (int i = 2; i <= 8; i++) {//纵向填充
			map[i][17] = 1; map[i][18] = 1;
			map[i][21] = 1; map[i][22] = 1;
		}
		map[3][21] = 2; map[3][22] = 2;
		map[4][21] = 2; map[4][22] = 2;
		for (int i = 28; i <= 35; i++) {//横向填充
			map[2][i] = 1; map[3][i] = 1;
		}
		for (int i = 36; i <= 39; i++) {//横向填充
			map[7][i] = 1; map[8][i] = 1;
		}
		for (int i = 2; i <= 34; i++) {//横向填充
			map[9][i] = 4; map[10][i] = 4;
		}
		for (int i = 37; i <= 39; i++) {//横向填充
			map[9][i] = 4; map[10][i] = 4;
		}
		for (int i = 14; i <= 26; i++) {//横向填充
			map[13][i] = 1; map[14][i] = 1;
		}
		map[13][4] = 1; map[14][4] = 1;
		map[13][5] = 1; map[14][5] = 1;
		map[17][4] = 1; map[18][4] = 1;
		map[17][5] = 1; map[18][5] = 1;
		map[17][8] = 1; map[18][8] = 1;
		map[17][9] = 1; map[18][9] = 1;
		map[15][6] = 1; map[16][6] = 1;
		map[15][7] = 1; map[16][7] = 1;
		map[19][8] = 2; map[20][8] = 2;
		map[19][9] = 2; map[20][9] = 2;
		for (int i = 12; i <= 20; i++) {//横向填充
			map[20][i] = 2;
		}
		for (int i = 23; i <= 30; i++) {//横向填充
			map[19][i] = 3; map[20][i] = 3;
		}
		map[17][26] = 3; map[18][26] = 3;
		map[17][27] = 3; map[18][27] = 3;
		for (int i = 33; i <= 36; i++) {//横向填充
			map[17][i] = 2; map[18][i] = 2;
		}
		map[15][36] = 2; map[16][36] = 2;
		map[15][35] = 2; map[16][35] = 2;
		for (int y = 15; y <= 18; y++) {//区域填充
			for (int x = 37; x <= 39; x++) {
				map[y][x] = 1;
			}
		}
		for (int i = 0; i <= 5; i++) {//横向填充
			map[21][i] = 4; map[22][i] = 4;
		}
		for (int i = 8; i <= 25; i++) {//横向填充
			map[21][i] = 4; map[22][i] = 4;
		}
		for (int i = 28; i <= 39; i++) {//横向填充
			map[21][i] = 4; map[22][i] = 4;
		}
		for (int y = 23; y <= 26; y++) {//区域填充
			for (int x = 0; x <= 5; x++) {
				map[y][x] = 3;
			}
		}
		map[27][2] = 2; map[27][3] = 2;
		for (int i = 6; i <= 10; i++) {//横向填充
			map[25][i] = 1; map[26][i] = 1;
		}
		for (int i = 28; i <= 30; i++) {//横向填充
			map[26][i] = 2; map[27][i] = 2;
		}
		for (int i = 26; i <= 29; i++) {//纵向填充
			map[i][31] = 1; map[i][32] = 1;
		}
		for (int i = 23; i <= 27; i++) {//纵向填充
			map[i][35] = 1; map[i][36] = 1;
		}
		for (int i = 37; i <= 39; i++) {//横向填充
			map[26][i] = 1; map[27][i] = 1;
		}
		map[28][19] = 5; map[28][20] = 8;
		map[29][19] = 8; map[29][20] = 8;
		for (int i = 27; i <= 29; i++) {
			map[i][18] = 1; map[i][21] = 1;
		}
		map[27][19] = 1; map[27][20] = 1;
		map[28][16] = 6; map[28][17] = 10;
		map[29][16] = 10; map[29][17] = 10;
	}

	int ** buffmap;
	buffmap = (int **)malloc(sizeof(int*) * 30);
	for (int i = 0; i < 30; i++) {
		buffmap[i] = (int *)malloc(sizeof(int) * 40);
	}
	for (int y = 0; y <= 29; y++) {
		for (int x = 0; x <= 39; x++) {
			buffmap[y][x] = map[y][x];
		}
	}

	int ** leafmap;
	leafmap = (int **)malloc(sizeof(int*) * 30);
	for (int i = 0; i < 30; i++) {
		leafmap[i] = (int *)malloc(sizeof(int) * 40);
	}
	for (int y = 0; y <= 29; y++) {
		for (int x = 0; x <= 39; x++) {
			if (buffmap[y][x] == 3) { leafmap[y][x] = buffmap[y][x]; }
			else { leafmap[y][x] = 0; }
		}
	}

	loadimage(&brick, _T("material\\brick.png"), 20, 20);
	loadimage(&iron, _T("material\\iron.png"), 20, 20);
	loadimage(&leaf, _T("material\\leaf.png"), 20, 20);
	loadimage(&leaf2, _T("material\\leaf2.png"), 20, 20);
	loadimage(&water, _T("material\\water.png"), 20, 20);
	loadimage(&heart, _T("material\\heart.png"), 40, 40);
	loadimage(&brokenheart, _T("material\\brokenheart.png"), 40, 40);
	loadimage(&tank00, _T("material\\00.png"), 40, 40);
	loadimage(&tank01, _T("material\\01.png"), 40, 40);
	loadimage(&tank02, _T("material\\02.png"), 40, 40);
	loadimage(&tank03, _T("material\\03.png"), 40, 40);
	loadimage(&ai00, _T("material\\10.png"), 40, 40);
	loadimage(&ai01, _T("material\\11.png"), 40, 40);
	loadimage(&ai02, _T("material\\12.png"), 40, 40);
	loadimage(&ai03, _T("material\\13.png"), 40, 40);
	loadimage(&bullet00, _T("material\\bullet00.jpg"), 6, 20);
	loadimage(&bullet01, _T("material\\bullet01.jpg"), 6, 20);
	loadimage(&bullet0x, _T("material\\bullet0x.jpg"), 6, 20);
	loadimage(&bullet10, _T("material\\bullet10.jpg"), 20, 6);
	loadimage(&bullet11, _T("material\\bullet11.jpg"), 20, 6);
	loadimage(&bullet1x, _T("material\\bullet1x.jpg"), 20, 6);
	loadimage(&bullet20, _T("material\\bullet20.jpg"), 6, 20);
	loadimage(&bullet21, _T("material\\bullet21.jpg"), 6, 20);
	loadimage(&bullet2x, _T("material\\bullet2x.jpg"), 6, 20);
	loadimage(&bullet30, _T("material\\bullet30.jpg"), 20, 6);
	loadimage(&bullet31, _T("material\\bullet31.jpg"), 20, 6);
	loadimage(&bullet3x, _T("material\\bullet3x.jpg"), 20, 6);
	loadimage(&boom, _T("material\\boom.png"), 10, 10);
	//loadimage(&endgame0, _T("material\\endgame0.jpg"), 300, 300);
	loadimage(&endgame0x, _T("material\\endgame0x.jpg"), 300, 300);
	//loadimage(&endgame1, _T("material\\endgame1.jpg"), 300, 300);
	loadimage(&endgame1x, _T("material\\endgame1x.jpg"), 300,300);
	//loadimage(&endgame2, _T("material\\endgame2.jpg"), 300, 300);
	loadimage(&endgame2x, _T("material\\endgame2x.jpg"), 300, 300);

	tank * me = (tank*)malloc(sizeof(tank));
	me->tankx = 16; me->tanky = 28; me->tankdir = 0; me->type = 0; me->life = 1;
	bullet* headbullet = (bullet*)malloc(sizeof(bullet));
	tank * headAI = (tank*)malloc(sizeof(tank));
	headAI->nexttank = NULL; headAI->life = 0;
	clock_t startadd = 0, nextadd = 0;
	clock_t startrate = 0, nextrate = 0;
	startrate = clock();

	headbullet->next = NULL;
	int flag = 0;//有无第一个子弹
	int * Flag = &flag;
	int now1 = time(0);
	while (1) {
		if (ltime == 0) {
			type = 0;
			loadplayground(Name, ltime, Score, life, buffmap, leafmap, headbullet, flag, rate);
			PlaySound("material\\ding.wav", NULL, SND_ASYNC | SND_FILENAME);
			Sleep(3000);
			break;
		}
		if (life <= 0) {
			type = 1;
			buffmap[me->tanky][me->tankx] = 0; buffmap[me->tanky][me->tankx + 1] = 0; buffmap[me->tanky + 1] [me->tankx]= 0; buffmap[me->tanky + 1][me->tankx + 1] = 0;
			loadplayground(Name, ltime, Score, life, buffmap, leafmap, headbullet, flag, rate);
			PlaySound("material\\endgame.wav", NULL, SND_ASYNC | SND_FILENAME);
			Sleep(3000);
			break;
		}
		if (buffmap[28][19] != 5) {
			type = 2;
			loadplayground(Name, ltime, Score, life, buffmap, leafmap, headbullet, flag, rate);
			PlaySound("material\\endgame.wav", NULL, SND_ASYNC | SND_FILENAME);
			Sleep(3000);
			break;
		}

		if (life%2==1) {
			life--;
		}

		int now2 = time(0);
		ltime = 90 - now2 + now1;

		startadd = clock();
		char ch;
		if (_kbhit()) {
			ch = _getch();
			me->nextmove = clock();
			me->nextfire = clock();
			if ((me->nextmove - me->startmove) >= 100) {
				me->ismove = 0;
			}
			switch (ch)
			{
			case'w':
				if (me->ismove == 0) {
					move(buffmap, 0, me);
				}
				break;
			case'W':
				if (me->ismove == 0) {
					move(buffmap, 0, me);
				}
				break;
			case'a':
				if (me->ismove == 0) {
					move(buffmap, 1, me);
				}
				break;
			case'A':
				if (me->ismove == 0) {
					move(buffmap, 1, me);
				}
				break;
			case's':
				if (me->ismove == 0) {
					move(buffmap, 2, me);
				}
				break;
			case'S':
				if (me->ismove == 0) {
					move(buffmap, 2, me);
				}
				break;
			case'd':
				if (me->ismove == 0) {
					move(buffmap, 3, me);
				}
				break;
			case'D':
				if (me->ismove == 0) {
					move(buffmap, 3, me);
				}
				break;
			case'j':
				if ((me->nextfire - me->startfire) >= 500) {
					headbullet = fire(me, buffmap, headbullet);
					flag = 1;
					me->startfire = clock();
				}
				break;
			case'J':
				if ((me->nextfire - me->startfire) >= 500) {
					headbullet = fire(me, buffmap, headbullet);
					flag = 1;
					me->startfire = clock();
				}
				break;
			default:
				break;
			}
		}
		loadplayground(Name, ltime, Score, life, buffmap, leafmap, headbullet, flag,rate);
		if (flag == 1) {
			bulletmove(headbullet, buffmap,headAI, Rate, Score,Life,level);
		}

		nextrate = clock();
		if (rate > 0&&(nextrate-startrate)>=1000) {
			rate--;
			startrate = clock();
		}

		int AIaccount;
		AIaccount = 0;
		tank* current = headAI;
		while (current != NULL) {
			if (current->life == 1) {
				AIaccount++;
				current = current->nexttank;
			}
			else {
				current = current->nexttank;
			}
		}

		if (AIaccount < 4&&(startadd-nextadd>1000)) {
			newAI(headAI,buffmap);
			nextadd = clock();
		}
		AIaction(headAI, buffmap, headbullet,Flag);
	}

	return type;
}

//显示
void loadplayground(char * name, int ltime, int * Score, int life, int** buffmap, int **leafmap, struct bullet * headbullet, int flag,int rate) {
	HRGN Area3;
	Area3 = CreateRectRgn(1, 1, 1000, 750);
	setcliprgn(Area3);
	clearcliprgn();
	BeginBatchDraw();

	setlinestyle(NULL | NULL, 1);
	rectangle(100, 75, 900, 675);

	char timex[3];
	char scorex[7];
	char ratex[7];
	char lifex[3];
	sprintf_s(timex, "%d", ltime);
	sprintf_s(scorex, "%d", (*Score));
	sprintf_s(ratex, "%d", rate);
	sprintf_s(lifex, "%d", life/2);

	char playpg3[100] = { "player:" };
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(40, 20, _T("Trajan Pro"));
	outtextxy(100, 670, playpg3);

	settextstyle(40, 20, _T("Courier New"));
	settextcolor(LIGHTCYAN);
	outtextxy(100, 710, name);

	char playpg4[100] = { "score:" };
	settextcolor(WHITE);
	settextstyle(40, 20, _T("Trajan Pro"));
	outtextxy(400, 670, playpg4);
	outtextxy(400, 710, scorex);

	char playpg5[100] = { "time:" };
	outtextxy(700, 670, playpg5);
	if (ltime <= 10) {
		settextcolor(RED);
		outtextxy(700, 710, timex);
	}
	else {
		settextcolor(WHITE);
		outtextxy(700, 710, timex);
	}
	

	char playpg6[100] = { "rate:" };
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(40, 20, _T("Trajan Pro"));
	outtextxy(900, 400, playpg6);
	outtextxy(920, 440, ratex);

	char playpg7[100] = { "life:" };
	outtextxy(900, 200, playpg7);
	if (life/2 == 3) {
		settextcolor(GREEN);
		outtextxy(920, 240, lifex);
	}
	else if (life/2 == 2) {
		settextcolor(YELLOW);
		outtextxy(920, 240, lifex);
	}
	else if(life/2==1) {
		settextcolor(RED);
		outtextxy(920, 240, lifex);
	}
	else {
		settextcolor(LIGHTGRAY);
		outtextxy(920, 240, lifex);
	}
	

	DeleteObject(Area3);

	HRGN Area4;
	Area4 = CreateRectRgn(101, 76, 899, 674);
	setcliprgn(Area4);

	int mx = 101;
	int my = 76;

	//0：空格  1：砖墙  2：铁块  3：树丛  4：河流  5：核心  8：核心外围
	//6：我方坦克核心向上 11：我方坦克核心向左 12：我方坦克核心向下 13：我方坦克核心向右 10：我方坦克身体 
	//7：敌方坦克核心向上 21: 敌方坦克核心向左 22：敌方坦克核心向下 23：敌方坦克核心向右 20：敌方坦克身体 

	for (int y = 0; y <= 29; y++) {
		for (int x = 0; x <= 39; x++) {
			if (buffmap[y][x] == 0  || buffmap[y][x] == 10 || buffmap[y][x] == 3 || buffmap[y][x] == 20 || buffmap[y][x] == 8) {
				mx += 20;
			}
			if (buffmap[y][x] == 1) {
				putimage(mx, my, &brick);
				mx += 20;
			}
			if (buffmap[y][x] == 2) {
				putimage(mx, my, &iron);
				mx += 20;
			}
			if (buffmap[y][x] == 4) {
				putimage(mx, my, &water);
				mx += 20;
			}
			if (buffmap[y][x] == 5) {
				putimage(mx, my, &heart);
				mx += 20;
			}
			if (buffmap[y][x] == 9) {
				putimage(mx, my, &brokenheart);
				mx += 20;
			}
			if (buffmap[y][x] == 6) {
				putimage(mx, my, &tank00);
				mx += 20;
			}
			if (buffmap[y][x] == 11) {
				putimage(mx, my, &tank01);
				mx += 20;
			}
			if (buffmap[y][x] == 12) {
				putimage(mx, my, &tank02);
				mx += 20;
			}
			if (buffmap[y][x] == 13) {
				putimage(mx, my, &tank03);
				mx += 20;
			}
			if (buffmap[y][x] == 7) {
				putimage(mx, my, &ai00);
				mx += 20;
			}
			if (buffmap[y][x] == 21) {
				putimage(mx, my, &ai01);
				mx += 20;
			}
			if (buffmap[y][x] == 22) {
				putimage(mx, my, &ai02);
				mx += 20;
			}
			if (buffmap[y][x] == 23) {
				putimage(mx, my, &ai03);
				mx += 20;
			}
		}
		mx = 101;
		my += 20;
	}

	if (flag == 1) {
		bullet* current = headbullet->next;
		while (current != NULL) {
			if (current->state == 1) {
				if (current->type == 0) {
					if (current->dir == 0) {
						putimage(current->x, current->y, &bullet0x, SRCAND);
						putimage(current->x, current->y, &bullet00, SRCPAINT);
					}
					else if (current->dir == 1) {
						putimage(current->x, current->y, &bullet1x, SRCAND);
						putimage(current->x, current->y, &bullet10, SRCPAINT);
					}
					else if (current->dir == 2) {
						putimage(current->x, current->y, &bullet2x, SRCAND);
						putimage(current->x, current->y, &bullet20, SRCPAINT);
					}
					else {
						putimage(current->x, current->y, &bullet3x, SRCAND);
						putimage(current->x, current->y, &bullet30, SRCPAINT);
					}
				}
				else {
					if (current->dir == 0) {
						putimage(current->x, current->y, &bullet0x, SRCAND);
						putimage(current->x, current->y, &bullet01, SRCPAINT);
					}
					else if (current->dir == 1) {
						putimage(current->x, current->y, &bullet1x, SRCAND);
						putimage(current->x, current->y, &bullet11, SRCPAINT);
					}
					else if (current->dir == 2) {
						putimage(current->x, current->y, &bullet2x, SRCAND);
						putimage(current->x, current->y, &bullet21, SRCPAINT);
					}
					else {
						putimage(current->x, current->y, &bullet3x, SRCAND);
						putimage(current->x, current->y, &bullet31, SRCPAINT);
					}
				}
				current = current->next;
			}
			else {
				current = current->next;
			}
		}
	}

	mx = 101;
	my = 76;
	for (int y = 0; y <= 29; y++) {
		for (int x = 0; x <= 39; x++) {
			if ((buffmap[y][x] == 6 || buffmap[y][x] == 10 || buffmap[y][x] == 11 || buffmap[y][x] == 12 || buffmap[y][x] == 13) && leafmap[y][x] == 3) {
				putimage(mx, my, &leaf2);
				mx += 20;
			}
			else if ((buffmap[y][x] != 6 || buffmap[y][x] != 10 || buffmap[y][x] != 11 || buffmap[y][x] != 12 || buffmap[y][x] != 13) && leafmap[y][x] == 3) {
				putimage(mx, my, &leaf);
				mx += 20;
			}
			else {
				mx += 20;
			}
		}
		mx = 101;
		my += 20;
	}

	DeleteObject(Area4);
	FlushBatchDraw();
}

//坦克移动
void move(int**buffmap, int direction, tank * tank) {
	if (tank->type == 0) {
		if (tank->tankdir != direction) {
			switch (direction)
			{
			case 0:
				buffmap[tank->tanky][tank->tankx] = 6;
				tank->tankdir = 0;
				break;
			case 1:
				buffmap[tank->tanky][tank->tankx] = 11;
				tank->tankdir = 1;
				break;
			case 2:
				buffmap[tank->tanky][tank->tankx] = 12;
				tank->tankdir = 2;
				break;
			case 3:
				buffmap[tank->tanky][tank->tankx] = 13;
				tank->tankdir = 3;
				break;
			default:
				break;
			}
		}
		else {
			switch (direction) {
			case 0:
				if (tank->tanky != 0 && buffmap[tank->tanky - 1][tank->tankx] != 1 && buffmap[tank->tanky - 1][tank->tankx + 1] != 1 && buffmap[tank->tanky - 1][tank->tankx] != 2 && buffmap[tank->tanky - 1][tank->tankx + 1] != 2 && buffmap[tank->tanky - 1][tank->tankx] != 4 && buffmap[tank->tanky - 1][tank->tankx + 1] != 4 && buffmap[tank->tanky - 1][tank->tankx] != 5 && buffmap[tank->tanky - 1][tank->tankx + 1] != 5&&buffmap[tank->tanky - 1][tank->tankx] != 7 && buffmap[tank->tanky - 1][tank->tankx + 1] != 7 && buffmap[tank->tanky - 1][tank->tankx] != 20 && buffmap[tank->tanky - 1][tank->tankx + 1] != 20 && buffmap[tank->tanky - 1][tank->tankx] != 21 && buffmap[tank->tanky - 1][tank->tankx + 1] != 21 && buffmap[tank->tanky - 1][tank->tankx] != 22 && buffmap[tank->tanky - 1][tank->tankx + 1] != 22 && buffmap[tank->tanky - 1][tank->tankx] != 23 && buffmap[tank->tanky - 1][tank->tankx + 1] != 23 && buffmap[tank->tanky - 1][tank->tankx] != 8 && buffmap[tank->tanky - 1][tank->tankx + 1] != 8 && buffmap[tank->tanky - 1][tank->tankx] != 9 && buffmap[tank->tanky - 1][tank->tankx + 1] != 9) {
					buffmap[tank->tanky][tank->tankx] = 10; buffmap[tank->tanky + 1][tank->tankx] = 0; buffmap[tank->tanky + 1][tank->tankx + 1] = 0;
					tank->tanky--;
					tank->tankdir = 0;
					buffmap[tank->tanky][tank->tankx] = 6;
					buffmap[tank->tanky][tank->tankx + 1] = 10;
					tank->startmove = clock();
					tank->ismove = 1;
				}
				else {
					buffmap[tank->tanky][tank->tankx] = 6;
					tank->tankdir = 0;
				}
				break;


			case 1:
				if (buffmap[tank->tanky + 1][tank->tankx - 1] != 1 && buffmap[tank->tanky][tank->tankx - 1] != 1 && buffmap[tank->tanky + 1][tank->tankx - 1] != 2 && buffmap[tank->tanky][tank->tankx - 1] != 2 && buffmap[tank->tanky + 1][tank->tankx - 1] != 4 && buffmap[tank->tanky][tank->tankx - 1] != 4 && buffmap[tank->tanky + 1][tank->tankx - 1] != 5 && buffmap[tank->tanky][tank->tankx - 1] != 5 && tank->tankx != 0&&buffmap[tank->tanky + 1][tank->tankx - 1] != 7 && buffmap[tank->tanky][tank->tankx - 1] != 7 && buffmap[tank->tanky + 1][tank->tankx - 1] != 20 && buffmap[tank->tanky][tank->tankx - 1] != 20 && buffmap[tank->tanky + 1][tank->tankx - 1] != 21 && buffmap[tank->tanky][tank->tankx - 1] != 21 && buffmap[tank->tanky + 1][tank->tankx - 1] != 22 && buffmap[tank->tanky][tank->tankx - 1] != 22 && buffmap[tank->tanky + 1][tank->tankx - 1] != 23 && buffmap[tank->tanky][tank->tankx - 1] != 23 && buffmap[tank->tanky + 1][tank->tankx - 1] != 8 && buffmap[tank->tanky][tank->tankx - 1] != 8 && buffmap[tank->tanky + 1][tank->tankx - 1] != 9 && buffmap[tank->tanky][tank->tankx - 1] != 9) {
					buffmap[tank->tanky][tank->tankx] = 10; buffmap[tank->tanky][tank->tankx + 1] = 0; buffmap[tank->tanky + 1][tank->tankx + 1] = 0;
					tank->tankx--;
					tank->tankdir = 1;
					buffmap[tank->tanky][tank->tankx] = 11; buffmap[tank->tanky + 1][tank->tankx] = 10;
					tank->startmove = clock();
					tank->ismove = 1;
				}
				else {
					buffmap[tank->tanky][tank->tankx] = 11;
					tank->tankdir = 1;
				}
				break;


			case 2:
				if (tank->tanky != 28 && buffmap[tank->tanky + 2][tank->tankx] != 1 && buffmap[tank->tanky + 2][tank->tankx + 1] != 1 && buffmap[tank->tanky + 2][tank->tankx] != 2 && buffmap[tank->tanky + 2][tank->tankx + 1] != 2 && buffmap[tank->tanky + 2][tank->tankx] != 4 && buffmap[tank->tanky + 2][tank->tankx + 1] != 4 && buffmap[tank->tanky + 2][tank->tankx] != 5 && buffmap[tank->tanky + 2][tank->tankx + 1] != 5 && buffmap[tank->tanky + 2][tank->tankx] != 7 && buffmap[tank->tanky + 2][tank->tankx + 1] != 7 && buffmap[tank->tanky + 2][tank->tankx] != 20 && buffmap[tank->tanky + 2][tank->tankx + 1] != 20 && buffmap[tank->tanky + 2][tank->tankx] != 21 && buffmap[tank->tanky + 2][tank->tankx + 1] != 21 && buffmap[tank->tanky + 2][tank->tankx] != 22 && buffmap[tank->tanky + 2][tank->tankx + 1] != 22 && buffmap[tank->tanky + 2][tank->tankx] !=23 && buffmap[tank->tanky + 2][tank->tankx + 1] != 23 && buffmap[tank->tanky + 2][tank->tankx] != 8 && buffmap[tank->tanky + 2][tank->tankx + 1] != 8 && buffmap[tank->tanky + 2][tank->tankx] != 9 && buffmap[tank->tanky + 2][tank->tankx + 1] != 9) {
					buffmap[tank->tanky][tank->tankx] = 0; buffmap[tank->tanky][tank->tankx + 1] = 0;
					tank->tanky++;
					tank->tankdir = 2;
					buffmap[tank->tanky][tank->tankx] = 12; buffmap[tank->tanky + 1][tank->tankx] = 10; buffmap[tank->tanky + 1][tank->tankx + 1] = 10;
					tank->startmove = clock();
					tank->ismove = 1;
				}
				else {
					buffmap[tank->tanky][tank->tankx] = 12;
					tank->tankdir = 2;
				}
				break;


			case 3:
				if (buffmap[tank->tanky][tank->tankx + 2] != 1 && buffmap[tank->tanky + 1][tank->tankx + 2] != 1 && buffmap[tank->tanky][tank->tankx + 2] != 2 && buffmap[tank->tanky + 1][tank->tankx + 2] != 2 && buffmap[tank->tanky][tank->tankx + 2] != 4 && buffmap[tank->tanky + 1][tank->tankx + 2] != 4 && buffmap[tank->tanky][tank->tankx + 2] != 5 && buffmap[tank->tanky + 1][tank->tankx + 2] != 5 && tank->tankx != 38 && buffmap[tank->tanky][tank->tankx + 2] != 7 && buffmap[tank->tanky + 1][tank->tankx + 2] != 7 && buffmap[tank->tanky][tank->tankx + 2] != 20 && buffmap[tank->tanky + 1][tank->tankx + 2] != 20 && buffmap[tank->tanky][tank->tankx + 2] != 21 && buffmap[tank->tanky + 1][tank->tankx + 2] != 21 && buffmap[tank->tanky][tank->tankx + 2] != 22 && buffmap[tank->tanky + 1][tank->tankx + 2] != 22 && buffmap[tank->tanky][tank->tankx + 2] != 23 && buffmap[tank->tanky + 1][tank->tankx + 2] != 23 && buffmap[tank->tanky][tank->tankx + 2] != 8 && buffmap[tank->tanky + 1][tank->tankx + 2] != 8 && buffmap[tank->tanky][tank->tankx + 2] != 9 && buffmap[tank->tanky + 1][tank->tankx + 2] != 9) {
					buffmap[tank->tanky][tank->tankx] = 0; buffmap[tank->tanky + 1][tank->tankx] = 0;
					tank->tankx++;
					tank->tankdir = 3;
					buffmap[tank->tanky][tank->tankx] = 13; buffmap[tank->tanky][tank->tankx + 1] = 10; buffmap[tank->tanky + 1][tank->tankx + 1] = 10;
					tank->startmove = clock();
					tank->ismove = 1;
				}
				else {
					buffmap[tank->tanky][tank->tankx] = 13;
					tank->tankdir = 3;
				}
				break;
			default:
				break;
			}
		}
	}
	else {
		switch (direction) {
		/*case 0:
			if (tank->tanky != 0 && buffmap[tank->tanky - 1][tank->tankx] != 1 && buffmap[tank->tanky - 1][tank->tankx + 1] != 1 && buffmap[tank->tanky - 1][tank->tankx] != 2 && buffmap[tank->tanky - 1][tank->tankx + 1] != 2 && buffmap[tank->tanky - 1][tank->tankx] != 4 && buffmap[tank->tanky - 1][tank->tankx + 1] != 4 && buffmap[tank->tanky - 1][tank->tankx] != 5 && buffmap[tank->tanky - 1][tank->tankx + 1] != 5 && buffmap[tank->tanky - 1][tank->tankx] != 7 && buffmap[tank->tanky - 1][tank->tankx + 1] != 7 && buffmap[tank->tanky - 1][tank->tankx] != 20 && buffmap[tank->tanky - 1][tank->tankx + 1] != 20 && buffmap[tank->tanky - 1][tank->tankx] != 21 && buffmap[tank->tanky - 1][tank->tankx + 1] != 21 && buffmap[tank->tanky - 1][tank->tankx] != 22 && buffmap[tank->tanky - 1][tank->tankx + 1] != 22 && buffmap[tank->tanky - 1][tank->tankx] != 23 && buffmap[tank->tanky - 1][tank->tankx + 1] != 23 && buffmap[tank->tanky - 1][tank->tankx] != 6 && buffmap[tank->tanky - 1][tank->tankx + 1] != 6 && buffmap[tank->tanky - 1][tank->tankx] != 10 && buffmap[tank->tanky - 1][tank->tankx + 1] != 10 && buffmap[tank->tanky - 1][tank->tankx] != 11 && buffmap[tank->tanky - 1][tank->tankx + 1] != 11 && buffmap[tank->tanky - 1][tank->tankx] != 12 && buffmap[tank->tanky - 1][tank->tankx + 1] != 12 && buffmap[tank->tanky - 1][tank->tankx] != 13 && buffmap[tank->tanky - 1][tank->tankx + 1] != 13) {
				buffmap[tank->tanky][tank->tankx] = 20; buffmap[tank->tanky + 1][tank->tankx] = 0; buffmap[tank->tanky + 1][tank->tankx + 1] = 0;
				tank->tanky--;
				tank->tankdir = 0;
				buffmap[tank->tanky][tank->tankx] = 7;
				buffmap[tank->tanky][tank->tankx + 1] = 20;
				tank->startmove = clock();
				tank->ismove = 1;
			}
			else {
				buffmap[tank->tanky][tank->tankx] = 7;
				tank->tankdir = 0;
			}
			break;*/


		case 1:
			if (buffmap[tank->tanky + 1][tank->tankx - 1] != 1 && buffmap[tank->tanky][tank->tankx - 1] != 1 && buffmap[tank->tanky + 1][tank->tankx - 1] != 2 && buffmap[tank->tanky][tank->tankx - 1] != 2 && buffmap[tank->tanky + 1][tank->tankx - 1] != 4 && buffmap[tank->tanky][tank->tankx - 1] != 4 && buffmap[tank->tanky + 1][tank->tankx - 1] != 5 && buffmap[tank->tanky][tank->tankx - 1] != 5 && tank->tankx != 0 && buffmap[tank->tanky + 1][tank->tankx - 1] != 7 && buffmap[tank->tanky][tank->tankx - 1] != 7 && buffmap[tank->tanky + 1][tank->tankx - 1] != 20 && buffmap[tank->tanky][tank->tankx - 1] != 20 && buffmap[tank->tanky + 1][tank->tankx - 1] != 21 && buffmap[tank->tanky][tank->tankx - 1] != 21 && buffmap[tank->tanky + 1][tank->tankx - 1] != 22 && buffmap[tank->tanky][tank->tankx - 1] != 22 && buffmap[tank->tanky + 1][tank->tankx - 1] != 23 && buffmap[tank->tanky][tank->tankx - 1] != 23 && buffmap[tank->tanky + 1][tank->tankx - 1] != 6 && buffmap[tank->tanky][tank->tankx - 1] != 6 && buffmap[tank->tanky + 1][tank->tankx - 1] != 10 && buffmap[tank->tanky][tank->tankx - 1] != 10 && buffmap[tank->tanky + 1][tank->tankx - 1] != 11 && buffmap[tank->tanky][tank->tankx - 1] != 11 && buffmap[tank->tanky + 1][tank->tankx - 1] != 12 && buffmap[tank->tanky][tank->tankx - 1] != 12 && buffmap[tank->tanky + 1][tank->tankx - 1] != 13 && buffmap[tank->tanky][tank->tankx - 1] != 13 && buffmap[tank->tanky + 1][tank->tankx - 1] != 8 && buffmap[tank->tanky][tank->tankx - 1] != 8 && buffmap[tank->tanky + 1][tank->tankx - 1] != 9 && buffmap[tank->tanky][tank->tankx - 1] != 9) {
				buffmap[tank->tanky][tank->tankx] = 20; buffmap[tank->tanky][tank->tankx + 1] = 0; buffmap[tank->tanky + 1][tank->tankx + 1] = 0;
				tank->tankx--;
				tank->tankdir = 1;
				buffmap[tank->tanky][tank->tankx] = 21; buffmap[tank->tanky + 1][tank->tankx] = 20;
				tank->startmove = clock();
				tank->ismove = 1;
			}
			else {
				buffmap[tank->tanky][tank->tankx] = 21;
				tank->tankdir = 1;
			}
			break;


		case 2:
			if (tank->tanky != 28 && buffmap[tank->tanky + 2][tank->tankx] != 1 && buffmap[tank->tanky + 2][tank->tankx + 1] != 1 && buffmap[tank->tanky + 2][tank->tankx] != 2 && buffmap[tank->tanky + 2][tank->tankx + 1] != 2 && buffmap[tank->tanky + 2][tank->tankx] != 4 && buffmap[tank->tanky + 2][tank->tankx + 1] != 4 && buffmap[tank->tanky + 2][tank->tankx] != 5 && buffmap[tank->tanky + 2][tank->tankx + 1] != 5 && buffmap[tank->tanky + 2][tank->tankx] != 7 && buffmap[tank->tanky + 2][tank->tankx + 1] != 7 && buffmap[tank->tanky + 2][tank->tankx] != 20 && buffmap[tank->tanky + 2][tank->tankx + 1] != 20 && buffmap[tank->tanky + 2][tank->tankx] != 21 && buffmap[tank->tanky + 2][tank->tankx + 1] != 21 && buffmap[tank->tanky + 2][tank->tankx] != 22 && buffmap[tank->tanky + 2][tank->tankx + 1] != 22 && buffmap[tank->tanky + 2][tank->tankx] != 23 && buffmap[tank->tanky + 2][tank->tankx + 1] != 23 && buffmap[tank->tanky + 2][tank->tankx] != 6 && buffmap[tank->tanky + 2][tank->tankx + 1] != 6 && buffmap[tank->tanky + 2][tank->tankx] != 10 && buffmap[tank->tanky + 2][tank->tankx + 1] != 10 && buffmap[tank->tanky + 2][tank->tankx] != 11 && buffmap[tank->tanky + 2][tank->tankx + 1] != 11 && buffmap[tank->tanky + 2][tank->tankx] != 12 && buffmap[tank->tanky + 2][tank->tankx + 1] != 12 && buffmap[tank->tanky + 2][tank->tankx] != 13 && buffmap[tank->tanky + 2][tank->tankx + 1] != 13 && buffmap[tank->tanky + 2][tank->tankx] != 8 && buffmap[tank->tanky + 2][tank->tankx + 1] != 8 && buffmap[tank->tanky + 2][tank->tankx] != 9 && buffmap[tank->tanky + 2][tank->tankx + 1] != 9) {
				buffmap[tank->tanky][tank->tankx] = 0; buffmap[tank->tanky][tank->tankx + 1] = 0;
				tank->tanky++;
				tank->tankdir = 2;
				buffmap[tank->tanky][tank->tankx] = 22; buffmap[tank->tanky + 1][tank->tankx] = 20; buffmap[tank->tanky + 1][tank->tankx + 1] = 20;
				tank->startmove = clock();
				tank->ismove = 1;
			}
			else {
				buffmap[tank->tanky][tank->tankx] = 22;
				tank->tankdir = 2;
			}
			break;


		case 3:
			if (buffmap[tank->tanky][tank->tankx + 2] != 1 && buffmap[tank->tanky + 1][tank->tankx + 2] != 1 && buffmap[tank->tanky][tank->tankx + 2] != 2 && buffmap[tank->tanky + 1][tank->tankx + 2] != 2 && buffmap[tank->tanky][tank->tankx + 2] != 4 && buffmap[tank->tanky + 1][tank->tankx + 2] != 4 && buffmap[tank->tanky][tank->tankx + 2] != 5 && buffmap[tank->tanky + 1][tank->tankx + 2] != 5 && tank->tankx != 38 && buffmap[tank->tanky][tank->tankx + 2] != 7 && buffmap[tank->tanky + 1][tank->tankx + 2] != 7 && buffmap[tank->tanky][tank->tankx + 2] != 20 && buffmap[tank->tanky + 1][tank->tankx + 2] != 20 && buffmap[tank->tanky][tank->tankx + 2] != 21 && buffmap[tank->tanky + 1][tank->tankx + 2] != 21 && buffmap[tank->tanky][tank->tankx + 2] != 22 && buffmap[tank->tanky + 1][tank->tankx + 2] != 22 && buffmap[tank->tanky][tank->tankx + 2] != 23 && buffmap[tank->tanky + 1][tank->tankx + 2] != 23&&buffmap[tank->tanky][tank->tankx + 2] != 6 && buffmap[tank->tanky + 1][tank->tankx + 2] != 6&&buffmap[tank->tanky][tank->tankx + 2] != 10 && buffmap[tank->tanky + 1][tank->tankx + 2] != 10&& buffmap[tank->tanky][tank->tankx + 2] != 11 && buffmap[tank->tanky + 1][tank->tankx + 2] != 11&& buffmap[tank->tanky][tank->tankx + 2] != 12 && buffmap[tank->tanky + 1][tank->tankx + 2] != 12&&buffmap[tank->tanky][tank->tankx + 2] != 13 && buffmap[tank->tanky + 1][tank->tankx + 2] != 13 && buffmap[tank->tanky][tank->tankx + 2] != 8 && buffmap[tank->tanky + 1][tank->tankx + 2] != 8 && buffmap[tank->tanky][tank->tankx + 2] != 9 && buffmap[tank->tanky + 1][tank->tankx + 2] != 9) {
				buffmap[tank->tanky][tank->tankx] = 0; buffmap[tank->tanky + 1][tank->tankx] = 0;
				tank->tankx++;
				tank->tankdir = 3;
				buffmap[tank->tanky][tank->tankx] = 23; buffmap[tank->tanky][tank->tankx + 1] = 20; buffmap[tank->tanky + 1][tank->tankx + 1] = 20;
				tank->startmove = clock();
				tank->ismove = 1;
			}
			else {
				buffmap[tank->tanky][tank->tankx] = 23;
				tank->tankdir = 3;
			}
			break;
		default:
			break;
		}
	}
}

//开火，创建新子弹
struct bullet* fire(tank* tank, int ** buffmap, bullet* headbullet) {
	bullet * newbullet = (bullet*)malloc(sizeof(bullet));
	bullet * current = headbullet;

	if ((tank->tankx == 0 && tank->tankdir == 1) || (tank->tanky == 0 && tank->tankdir == 0) || (tank->tankx == 38 && tank->tankdir == 3) || (tank->tanky == 28 && tank->tankdir == 2)) {
		return headbullet;
	}

	tank->shang = 76 + tank->tanky * 20;
	tank->zuo = 100 + tank->tankx * 20;
	tank->xia = tank->shang + 40;
	tank->you = tank->zuo + 40;
	while (current != NULL) {
		if (current->next == NULL) {
			current->next = newbullet;
			newbullet->next = NULL;
			newbullet->dir = tank->tankdir;
			newbullet->state = 1;
			newbullet->i = 0;
			if (tank->tankdir == 0) {
				newbullet->x = tank->zuo + 17;
				newbullet->y = tank->shang - 20;
				newbullet->bulletx1 = tank->tankx;
				newbullet->bulletx2 = tank->tankx + 1;
				newbullet->bullety1 = tank->tanky - 1;
				newbullet->bullety2 = newbullet->bullety1;
			}
			else if (tank->tankdir == 1) {
				newbullet->x = tank->zuo - 20;
				newbullet->y = tank->shang + 17;
				newbullet->bullety1 = tank->tanky;
				newbullet->bullety2 = tank->tanky + 1;
				newbullet->bulletx1 = tank->tankx - 1;
				newbullet->bulletx2 = newbullet->bulletx1;
			}
			else if (tank->tankdir == 2) {
				newbullet->x = tank->zuo + 17;
				newbullet->y = tank->xia;
				newbullet->bulletx1 = tank->tankx;
				newbullet->bulletx2 = tank->tankx + 1;
				newbullet->bullety1 = tank->tanky + 1;
				newbullet->bullety2 = newbullet->bullety1;
			}
			else {
				newbullet->x = tank->you;
				newbullet->y = tank->shang + 17;
				newbullet->bullety1 = tank->tanky;
				newbullet->bullety2 = tank->tanky + 1;
				newbullet->bulletx1 = tank->tankx + 1;
				newbullet->bulletx2 = newbullet->bulletx1;
			}
			newbullet->type = tank->type;
			break;
		}
		else {
			current = current->next;
		}
	}


	return headbullet;
}

//子弹移动
struct bullet * bulletmove(struct bullet* headbullet, int **buffmap, struct tank* headAI, int* Rate, int* Score,int * Life,int level) {
	bullet* current = headbullet->next;
	while (current != NULL) {
		if (current->state == 1) {
			if (current->type == 0) {
				if (current->dir == 0) {
					current->y -= 1;
					if (current->i % 20 == 0) {
						if (buffmap[current->bullety1][current->bulletx1] == 1 || buffmap[current->bullety1][current->bulletx2] == 1 || buffmap[current->bullety1][current->bulletx1] == 2 || buffmap[current->bullety1][current->bulletx2] == 2 || buffmap[current->bullety1][current->bulletx1] == 5 || buffmap[current->bullety1][current->bulletx2] == 5 || current->bullety1 == 0 || buffmap[current->bullety1][current->bulletx1] == 7 || buffmap[current->bullety1][current->bulletx2] ==7 || buffmap[current->bullety1][current->bulletx1] == 20 || buffmap[current->bullety1][current->bulletx2] ==20 || buffmap[current->bullety1][current->bulletx1] == 21 || buffmap[current->bullety1][current->bulletx2] == 21 || buffmap[current->bullety1][current->bulletx1] == 22 || buffmap[current->bullety1][current->bulletx2] == 22 || buffmap[current->bullety1][current->bulletx1] == 23 || buffmap[current->bullety1][current->bulletx2] == 23) {
							if (buffmap[current->bullety1][current->bulletx1] == 1) {
								buffmap[current->bullety1][current->bulletx1] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx2] == 1) {
								buffmap[current->bullety1][current->bulletx2] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx2] == 2) {
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 2) {
								current->state = 0;
							}
							if (current->bullety1 == 0) {
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 7) {
								current->state = 0;
								AIdead(headAI,current->bullety1, current->bulletx1, buffmap,Rate,Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx2] == 7) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx2, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx1] == 20) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx2] == 20) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx2, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx1] == 21) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx2] == 21) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx2, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx1] == 22) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx2] == 22) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx2, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx1] == 23) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx2] == 23) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx2, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx2] == 5) {
								buffmap[28][19] = 9; buffmap[28][20] = 0;
								buffmap[29][19] = 0; buffmap[29][20] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 5) {
								buffmap[28][19] = 9; buffmap[28][20] = 0;
								buffmap[29][19] = 0; buffmap[29][20] = 0;
								current->state = 0;
							}
						}
						current->i = 0;
						current->bullety1--;
						current->bullety2 = current->bullety1;
					}
					current->i += 1;
				}
				else if (current->dir == 1) {
					current->x -= 1;
					if (current->i % 20 == 0) {
						if (buffmap[current->bullety1][current->bulletx1] == 1 || buffmap[current->bullety2][current->bulletx1] == 1 || buffmap[current->bullety1][current->bulletx1] == 2 || buffmap[current->bullety2][current->bulletx1] == 2 || buffmap[current->bullety1][current->bulletx1] == 5 || buffmap[current->bullety2][current->bulletx1] == 5 || current->bulletx1 == 0 || buffmap[current->bullety1][current->bulletx1] == 7 || buffmap[current->bullety2][current->bulletx1] == 7 || buffmap[current->bullety1][current->bulletx1] == 20 || buffmap[current->bullety2][current->bulletx1] == 20 || buffmap[current->bullety1][current->bulletx1] == 21 || buffmap[current->bullety2][current->bulletx1] == 21 || buffmap[current->bullety1][current->bulletx1] == 22 || buffmap[current->bullety2][current->bulletx1] == 22 || buffmap[current->bullety1][current->bulletx1] == 23 || buffmap[current->bullety2][current->bulletx1] == 23) {
							if (buffmap[current->bullety1][current->bulletx1] == 1) {
								buffmap[current->bullety1][current->bulletx1] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety2][current->bulletx1] == 1) {
								buffmap[current->bullety2][current->bulletx1] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 2) {
								current->state = 0;
							}
							if (buffmap[current->bullety2][current->bulletx1] == 2) {
								current->state = 0;
							}
							if (current->bulletx1 == 0) {
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 7) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety2][current->bulletx1] == 7) {
								current->state = 0;
								AIdead(headAI, current->bullety2, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx1] == 20) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety2][current->bulletx1] == 20) {
								current->state = 0;
								AIdead(headAI, current->bullety2, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx1] == 21) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety2][current->bulletx1] == 21) {
								current->state = 0;
								AIdead(headAI, current->bullety2, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx1] == 22) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety2][current->bulletx1] == 22) {
								current->state = 0;
								AIdead(headAI, current->bullety2, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx1] == 23) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety2][current->bulletx1] == 23) {
								current->state = 0;
								AIdead(headAI, current->bullety2, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx1] == 5) {
								buffmap[28][19] = 9; buffmap[28][20] = 0;
								buffmap[29][19] = 0; buffmap[29][20] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety2][current->bulletx1] == 5) {
								buffmap[28][19] = 9; buffmap[28][20] = 0;
								buffmap[29][19] = 0; buffmap[29][20] = 0;
								current->state = 0;
							}
						}
						current->i = 0;
						current->bulletx1--;
						current->bulletx2 = current->bulletx1;
					}
					current->i += 1;
				}
				else if (current->dir == 2) {
					current->y += 1;
					if (current->i % 20 == 0) {
						if (buffmap[current->bullety1][current->bulletx1] == 1 || buffmap[current->bullety1][current->bulletx2] == 1 ||
							buffmap[current->bullety1][current->bulletx1] == 2 || buffmap[current->bullety1][current->bulletx2] == 2 ||
							buffmap[current->bullety1][current->bulletx1] == 5 || buffmap[current->bullety1][current->bulletx2] == 5 || 
							current->bullety1 == 29||buffmap[current->bullety1][current->bulletx1] == 7 || buffmap[current->bullety1][current->bulletx2] == 7 || 
							buffmap[current->bullety1][current->bulletx1] == 20 || buffmap[current->bullety1][current->bulletx2] == 20 ||
							buffmap[current->bullety1][current->bulletx1] == 21 || buffmap[current->bullety1][current->bulletx2] == 21 ||
							buffmap[current->bullety1][current->bulletx1] == 22 || buffmap[current->bullety1][current->bulletx2] == 22 ||
							buffmap[current->bullety1][current->bulletx1] == 23 || buffmap[current->bullety1][current->bulletx2] == 23) {
							if (buffmap[current->bullety1][current->bulletx1] == 1) {
								buffmap[current->bullety1][current->bulletx1] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx2] == 1) {
								buffmap[current->bullety1][current->bulletx2] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx2] == 2) {
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 2) {
								current->state = 0;
							}
							if (current->bullety1 == 29) {
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx2] == 7) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx2, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx1] == 7) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx2] == 20) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx2, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx1] == 20) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx2] == 21) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx2, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx1] == 21) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx2] == 22) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx2, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx1] == 22) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx2] == 23) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx2, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx1] == 23) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx2] == 5) {
								buffmap[28][19] = 9; buffmap[28][20] = 0;
								buffmap[29][19] = 0; buffmap[29][20] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 5) {
								buffmap[28][19] = 9; buffmap[28][20] = 0;
								buffmap[29][19] = 0; buffmap[29][20] = 0;
								current->state = 0;
							}
						}
						current->i = 0;
						current->bullety1++;
						current->bullety2 = current->bullety1;
					}
					current->i += 1;
				}
				else {
					current->x += 1;
					if (current->i % 20 == 0) {
						if (buffmap[current->bullety1][current->bulletx1] == 1 || buffmap[current->bullety2][current->bulletx1] == 1 || buffmap[current->bullety1][current->bulletx1] == 2 || buffmap[current->bullety2][current->bulletx1] == 2 || buffmap[current->bullety1][current->bulletx1] == 5 || buffmap[current->bullety2][current->bulletx1] == 5 || current->bulletx1 == 39 || buffmap[current->bullety1][current->bulletx1] == 7 || buffmap[current->bullety2][current->bulletx1] == 7 || buffmap[current->bullety1][current->bulletx1] == 20 || buffmap[current->bullety2][current->bulletx1] == 20 || buffmap[current->bullety1][current->bulletx1] == 21 || buffmap[current->bullety2][current->bulletx1] == 21 || buffmap[current->bullety1][current->bulletx1] == 22 || buffmap[current->bullety2][current->bulletx1] == 22 || buffmap[current->bullety1][current->bulletx1] == 23 || buffmap[current->bullety2][current->bulletx1] == 23) {
							if (buffmap[current->bullety1][current->bulletx1] == 1) {
								buffmap[current->bullety1][current->bulletx1] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety2][current->bulletx1] == 1) {
								buffmap[current->bullety2][current->bulletx1] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 2) {
								current->state = 0;
							}
							if (buffmap[current->bullety2][current->bulletx1] == 2) {
								current->state = 0;
							}
							if (current->bulletx1 == 39) {
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 7) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety2][current->bulletx1] == 7) {
								current->state = 0;
								AIdead(headAI, current->bullety2, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx1] == 20) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety2][current->bulletx1] == 20) {
								current->state = 0;
								AIdead(headAI, current->bullety2, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx1] == 21) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety2][current->bulletx1] == 21) {
								current->state = 0;
								AIdead(headAI, current->bullety2, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx1] == 22) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety2][current->bulletx1] == 22) {
								current->state = 0;
								AIdead(headAI, current->bullety2, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx1] == 23) {
								current->state = 0;
								AIdead(headAI, current->bullety1, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety2][current->bulletx1] == 23) {
								current->state = 0;
								AIdead(headAI, current->bullety2, current->bulletx1, buffmap, Rate, Score, level);
							}
							if (buffmap[current->bullety1][current->bulletx1] == 5) {
								buffmap[28][19] = 9; buffmap[28][20] = 0;
								buffmap[29][19] = 0; buffmap[29][20] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety2][current->bulletx1] == 5) {
								buffmap[28][19] = 9; buffmap[28][20] = 0;
								buffmap[29][19] = 0; buffmap[29][20] = 0;
								current->state = 0;
							}
						}
						current->i = 0;
						current->bulletx1++;
						current->bulletx2 = current->bulletx1;
					}
					current->i += 1;
				}
			}
			else {
				if (current->dir == 0) {
					current->y -= 1;
					if (current->i % 20 == 0) {
						if (buffmap[current->bullety1][current->bulletx1] == 1 || buffmap[current->bullety1][current->bulletx2] == 1 || buffmap[current->bullety1][current->bulletx1] == 2 || buffmap[current->bullety1][current->bulletx2] == 2 || buffmap[current->bullety1][current->bulletx1] == 5 || buffmap[current->bullety1][current->bulletx2] == 5 || current->bullety1 == 0 || buffmap[current->bullety1][current->bulletx1] == 6 || buffmap[current->bullety1][current->bulletx2] == 6 || buffmap[current->bullety1][current->bulletx1] == 10 || buffmap[current->bullety1][current->bulletx2] == 10 || buffmap[current->bullety1][current->bulletx1] == 11 || buffmap[current->bullety1][current->bulletx2] == 11 || buffmap[current->bullety1][current->bulletx1] == 12 || buffmap[current->bullety1][current->bulletx2] == 12 || buffmap[current->bullety1][current->bulletx1] == 13 || buffmap[current->bullety1][current->bulletx2] == 13) {
							if (buffmap[current->bullety1][current->bulletx1] == 1) {
								buffmap[current->bullety1][current->bulletx1] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx2] == 1) {
								buffmap[current->bullety1][current->bulletx2] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx2] == 2) {
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 2) {
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx2] == 5) {
								buffmap[28][19] = 9; buffmap[28][20] = 0;
								buffmap[29][19] = 0; buffmap[29][20] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 5) {
								buffmap[28][19] = 9; buffmap[28][20] = 0;
								buffmap[29][19] = 0; buffmap[29][20] = 0;
								current->state = 0;
							}
							if (current->bullety1 == 0) {
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 6) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx2] == 6) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 10) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx2] == 10) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 11) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx2] == 11) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 12) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx2] == 12) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 13) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx2] == 13) {
								current->state = 0;
								(*Life)--;
							}
						}
						current->i = 0;
						current->bullety1--;
						current->bullety2 = current->bullety1;
					}
					current->i += 1;
				}
				else if (current->dir == 1) {
					current->x -= 1;
					if (current->i % 20 == 0) {
						if (buffmap[current->bullety1][current->bulletx1] == 1 || buffmap[current->bullety2][current->bulletx1] == 1 || buffmap[current->bullety1][current->bulletx1] == 2 || buffmap[current->bullety2][current->bulletx1] == 2 || buffmap[current->bullety1][current->bulletx1] == 5 || buffmap[current->bullety2][current->bulletx1] == 5 || current->bulletx1 == 0 || buffmap[current->bullety1][current->bulletx1] == 6 || buffmap[current->bullety2][current->bulletx1] == 6 || buffmap[current->bullety1][current->bulletx1] == 10 || buffmap[current->bullety2][current->bulletx1] == 10 || buffmap[current->bullety1][current->bulletx1] == 11 || buffmap[current->bullety2][current->bulletx1] == 11 || buffmap[current->bullety1][current->bulletx1] == 12 || buffmap[current->bullety2][current->bulletx1] == 12 || buffmap[current->bullety1][current->bulletx1] == 13 || buffmap[current->bullety2][current->bulletx1] == 13) {
							if (buffmap[current->bullety1][current->bulletx1] == 1) {
								buffmap[current->bullety1][current->bulletx1] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety2][current->bulletx1] == 1) {
								buffmap[current->bullety2][current->bulletx1] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 2) {
								current->state = 0;
							}
							if (buffmap[current->bullety2][current->bulletx1] == 2) {
								current->state = 0;
							}
							if (current->bulletx1 == 0) {
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 5) {
								buffmap[28][19] = 9; buffmap[28][20] = 0;
								buffmap[29][19] = 0; buffmap[29][20] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety2][current->bulletx1] == 5) {
								buffmap[28][19] = 9; buffmap[28][20] = 0;
								buffmap[29][19] = 0; buffmap[29][20] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 6) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety2][current->bulletx1] == 6) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 10) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety2][current->bulletx1] == 10) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 11) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety2][current->bulletx1] == 11) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 12) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety2][current->bulletx1] == 12) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 13) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety2][current->bulletx1] == 13) {
								current->state = 0;
								(*Life)--;
							}
						}
						current->i = 0;
						current->bulletx1--;
						current->bulletx2 = current->bulletx1;
					}
					current->i += 1;
				}
				else if (current->dir == 2) {
					current->y += 1;
					if (current->i % 20 == 0) {
						if (buffmap[current->bullety1][current->bulletx1] == 1 || buffmap[current->bullety1][current->bulletx2] == 1 || buffmap[current->bullety1][current->bulletx1] == 2 || buffmap[current->bullety1][current->bulletx2] == 2 || buffmap[current->bullety1][current->bulletx1] == 5 || buffmap[current->bullety1][current->bulletx2] == 5 || current->bullety1 == 29 || buffmap[current->bullety1][current->bulletx1] == 6 || buffmap[current->bullety1][current->bulletx2] == 6 || buffmap[current->bullety1][current->bulletx1] == 10 || buffmap[current->bullety1][current->bulletx2] == 10 || buffmap[current->bullety1][current->bulletx1] == 11 || buffmap[current->bullety1][current->bulletx2] == 11 || buffmap[current->bullety1][current->bulletx1] == 12 || buffmap[current->bullety1][current->bulletx2] == 12 || buffmap[current->bullety1][current->bulletx1] == 13 || buffmap[current->bullety1][current->bulletx2] == 13) {
							if (buffmap[current->bullety1][current->bulletx1] == 1) {
								buffmap[current->bullety1][current->bulletx1] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx2] == 1) {
								buffmap[current->bullety1][current->bulletx2] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx2] == 2) {
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 2) {
								current->state = 0;
							}
							if (current->bullety1 == 29) {
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx2] == 5) {
								buffmap[28][19] = 9; buffmap[28][20] = 0;
								buffmap[29][19] = 0; buffmap[29][20] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 5) {
								buffmap[28][19] = 9; buffmap[28][20] = 0;
								buffmap[29][19] = 0; buffmap[29][20] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx2] == 6) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 6) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx2] == 10) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 10) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx2] == 11) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 11) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx2] == 12) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 12) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx2] == 13) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 13) {
								current->state = 0;
								(*Life)--;
							}
						}
						current->i = 0;
						current->bullety1++;
						current->bullety2 = current->bullety1;
					}
					current->i += 1;
				}
				else {
					current->x += 1;
					if (current->i % 20 == 0) {
						if (buffmap[current->bullety1][current->bulletx1] == 1 || buffmap[current->bullety2][current->bulletx1] == 1 || buffmap[current->bullety1][current->bulletx1] == 2 || buffmap[current->bullety2][current->bulletx1] == 2 || buffmap[current->bullety1][current->bulletx1] == 5 || buffmap[current->bullety2][current->bulletx1] == 5 || current->bulletx1 == 39 || buffmap[current->bullety1][current->bulletx1] == 6 || buffmap[current->bullety2][current->bulletx1] == 6 || buffmap[current->bullety1][current->bulletx1] == 10 || buffmap[current->bullety2][current->bulletx1] == 10 || buffmap[current->bullety1][current->bulletx1] == 11 || buffmap[current->bullety2][current->bulletx1] == 11 || buffmap[current->bullety1][current->bulletx1] == 12 || buffmap[current->bullety2][current->bulletx1] == 12 || buffmap[current->bullety1][current->bulletx1] == 13 || buffmap[current->bullety2][current->bulletx1] == 13) {
							if (buffmap[current->bullety1][current->bulletx1] == 1) {
								buffmap[current->bullety1][current->bulletx1] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety2][current->bulletx1] == 1) {
								buffmap[current->bullety2][current->bulletx1] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 2) {
								current->state = 0;
							}
							if (buffmap[current->bullety2][current->bulletx1] == 2) {
								current->state = 0;
							}
							if (current->bulletx1 == 39) {
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 5) {
								buffmap[28][19] = 9; buffmap[28][20] = 0;
								buffmap[29][19] = 0; buffmap[29][20] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety2][current->bulletx1] == 5) {
								buffmap[28][19] = 9; buffmap[28][20] = 0;
								buffmap[29][19] = 0; buffmap[29][20] = 0;
								current->state = 0;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 6) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety2][current->bulletx1] == 6) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 10) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety2][current->bulletx1] == 10) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 11) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety2][current->bulletx1] == 11) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 12) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety2][current->bulletx1] == 12) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety1][current->bulletx1] == 13) {
								current->state = 0;
								(*Life)--;
							}
							if (buffmap[current->bullety2][current->bulletx1] == 13) {
								current->state = 0;
								(*Life)--;
							}
						}
						current->i = 0;
						current->bulletx1++;
						current->bulletx2 = current->bulletx1;
					}
					current->i += 1;
				}
			}
			current = current->next;
		}
		else {
			current = current->next;
		}
	}
	return headbullet;
}

//新建AI
tank * newAI(tank * headAI, int ** buffmap) {
	tank * currenttank = headAI;
	srand(time(0));
	int location = rand() % 3;
	while (currenttank != NULL) {
		if (currenttank->nexttank == NULL) {
			if (location == 0) {
				if (buffmap[0][0] == 0 && buffmap[1][0] == 0 && buffmap[0][1] == 0 && buffmap[1][1] == 0) {
					tank * newtank = (tank*)malloc(sizeof(tank));
					currenttank->nexttank = newtank;
					newtank->nexttank = NULL;
					newtank->ismove = 0;
					newtank->tankdir = 2;
					newtank->tankx = 0;
					newtank->tanky = 0;
					newtank->type = 1;
					newtank->life = 1;
					newtank->nextmove = clock();
					newtank->nextfire = clock();
					newtank->startmove = 0;
					buffmap[0][0] = 22;
					buffmap[1][0] = 20; buffmap[0][1] = 20; buffmap[1][1] = 20;
				}
				else
				{
					break;
				}
			}
			else if (location == 1) {
				if (buffmap[0][19] == 0 && buffmap[1][19] == 0 && buffmap[0][20] == 0 && buffmap[1][20] == 0) {
					tank * newtank = (tank*)malloc(sizeof(tank));
					currenttank->nexttank = newtank;
					newtank->nexttank = NULL;
					newtank->ismove = 0;
					newtank->tankdir = 2;
					newtank->tankx = 19;
					newtank->tanky = 0;
					newtank->type = 1;
					newtank->life = 1;
					newtank->nextmove = clock();
					newtank->nextfire = clock();
					newtank->startmove = 0;
					buffmap[0][19] = 22; 
					buffmap[1][19] = 20; buffmap[0][20] = 20; buffmap[1][20] = 20;
				}
				else {
					break;
				}
			}
			else {
				if (buffmap[0][38] == 0 && buffmap[1][38] == 0 && buffmap[0][39] == 0 && buffmap[1][39] == 0) {
					tank * newtank = (tank*)malloc(sizeof(tank));
					currenttank->nexttank = newtank;
					newtank->nexttank = NULL;
					newtank->ismove = 0;
					newtank->tankdir = 2;
					newtank->tankx = 38;
					newtank->tanky = 0;
					newtank->type = 1;
					newtank->life = 1;
					newtank->nextmove = clock();
					newtank->nextfire = clock();
					newtank->startmove = 0;
					buffmap[0][38] = 22;  
					buffmap[1][38] = 20; buffmap[0][39] = 20; buffmap[1][39] = 20;
				}
				else {
					break;
				}
			}
		}
		else {
			currenttank = currenttank->nexttank;
		}
	}
	return headAI;
}

//AI行动
tank * AIaction(tank * headAI, int ** buffmap, bullet * headbullet,int * Flag)
{
	tank* current = headAI;
	srand(time(0));
	while (current != NULL) {
		if (current->life == 1) {
			int direction = rand() % 4;
			if (current->nextmove - current->startmove>=200) {
				move(buffmap, direction, current);
			}
			if (current->nextfire-current->startfire>=2000) {
				fire(current,buffmap,headbullet);
				(*Flag) = 1;
				current->startfire = clock();
			}
			current->nextmove = clock();
			current->nextfire = clock();
			current = current->nexttank;
		}
		else {
			current = current->nexttank;
		}
	}
	return headAI;
}

//AI死亡
tank * AIdead(tank * headAI,int y, int x, int ** buffmap, int* Rate, int* Score,int level){
	tank* current = headAI;
	while (current != NULL) {
		if (current->life == 1) {
			if ((current->tankx == x && current->tanky == y) || (current->tankx + 1 == x && current->tanky == y) || (current->tankx == x && current->tanky + 1 == y) || (current->tankx + 1 == x && current->tanky + 1 == y)) {
				current->life = 0;
				buffmap[current->tanky][current->tankx] = 0;
				buffmap[current->tanky][current->tankx+1] = 0;
				buffmap[current->tanky+1][current->tankx] = 0;
				buffmap[current->tanky+1][current->tankx+1] = 0;
				if(level==3){ 
					(*Rate) += 10; 
				}
				else if (level == 2) {
					(*Rate) += 9;
				}
				else {
					(*Rate) += 8;
				}
				(*Score) += (*Rate);
			}
			current = current->nexttank;
		}
		else {
			current = current->nexttank;
		}
	}
	return headAI;
}

//游戏结束
int endgame(int score, char* Name, int type)
{
	HRGN Area;
	Area = CreateRectRgn(1, 1, 1000, 750);
	setcliprgn(Area);
	cleardevice();
	EndBatchDraw();

	fillrectangle(100, 75, 900, 675);
	putimage(101, 76, &welcomebg);
	Sleep(500);

	char endgame1t[100] = { "Gooood game!" };
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(150, 48, _T("Trajan Pro"));
	outtextxy(180, 75, endgame1t);
	Sleep(300);

	char endgame2t[100] = { "player:" };
	settextstyle(75, 24, _T("Trajan Pro"));
	outtextxy(300, 250, endgame2t);
	settextstyle(75, 24, _T("Courier New"));
	settextcolor(LIGHTCYAN);
	outtextxy(500, 250, Name);
	Sleep(300);

	char endgame3t[100] = { "score:" };
	settextstyle(75, 24, _T("Trajan Pro"));
	settextcolor(WHITE);
	outtextxy(300, 350, endgame3t);
	char scorex[7];
	sprintf_s(scorex, "%d", score);
	outtextxy(500, 350, scorex);
	Sleep(300);

	if (type == 0) {
		putimage(600, 200, &endgame0x, SRCAND);
		putimage(600, 200, &endgame0, SRCPAINT);
	}
	else if (type == 1) {
		putimage(600, 200, &endgame1x, SRCAND);
		putimage(600, 200, &endgame1, SRCPAINT);
	}
	else {
		putimage(600, 200, &endgame2x, SRCAND);
		putimage(600, 200, &endgame2, SRCPAINT);
	}
	Sleep(300);

	setlinestyle(NULL | NULL, 3);
	rectangle(250, 500, 450, 570);
	char endgame4t[100] = { "return" };
	settextstyle(65, 28, _T("Trajan Pro"));
	outtextxy(260, 500, endgame4t);
	rectangle(550, 500, 750, 570);
	char endgame5t[100] = { "exit" };
	outtextxy(600, 500, endgame5t);

	FILE * fp;
	errno_t err;
	err = fopen_s(&fp, "material\\rank.txt", "r");
	player r[5];
	char ch;
	int i = 0; int j = 0;
	ch = getc(fp);
	while (ch != EOF) {
		j = 0;
		r[i].Name = (char*)malloc(sizeof(char) * 21);
		r[i].score = (char*)malloc(sizeof(char) * 10);
		while (ch != '\n') {
			r[i].Name[j] = ch;
			j++;
			ch = getc(fp);
		}
		r[i].Name[j] = 0;

		j = 0;
		ch = getc(fp);
		while (ch != '\n') {
			r[i].score[j] = ch;
			j++;
			ch = getc(fp);
		}
		r[i].score[j] = 0;

		ch = getc(fp);
		i++;
	}
	fclose(fp);

	int SCORE[5] = { 0 };

	for (int i = 0; i <= 4; i++) {
		if (r[i].score[0] != 'N') {
			int j = 0;
			char s[10];
			while (r[i].score[j] >= '0' && r[i].score[j] <= '9') {
				s[j] = r[i].score[j];
				j++;
			}
			s[j] = 0;
			SCORE[i] = atoi(s);
		}
	}

	if (score > SCORE[4]) {
		SCORE[4] = score;
		r[4].Name = Name;
		r[4].score = scorex;
	}

	int m, n, k, tempx;
	char* tempy;
	char* tempz;

	for (m = 1; m < 5; m++)
	{
		for (n = m - 1; n >= 0; n--)
		{
			if (SCORE[n + 1] > SCORE[n])
			{
				tempx = SCORE[n + 1];
				SCORE[n + 1] = SCORE[n];
				SCORE[n] = tempx;

				tempy = r[n + 1].Name;
				r[n + 1].Name = r[n].Name;
				r[n].Name = tempy;

				tempz = r[n + 1].score;
				r[n + 1].score = r[n].score;
				r[n].score = tempz;
			}
			else
			{
				break;
			}
		}
	}

	err = fopen_s(&fp, "material//rank.txt", "w");
	for (i = 0; i <= 4; i++) {
		fputs(r[i].Name, fp);
		putc('\n', fp);

		fputs(r[i].score, fp);
		putc('\n', fp);
	}
	fclose(fp);

	MOUSEMSG m1 = GetMouseMsg();
	int result = 0;
	while (1) {
		if (MouseHit()) {
			m1 = GetMouseMsg();
			if (m1.uMsg == WM_LBUTTONDOWN) {
				if ((m1.x >= 250 && m1.x <= 450) && (m1.y >= 500 && m1.y <= 570)) {
					result = 1;//回到开始
					break;
				}
				else if ((m1.x >= 550 && m1.x <= 750) && (m1.y >= 500 && m1.y <= 570)) {
					result = 0;//退出游戏
					break;
				}
				else {
					continue;
				}
			}
		}
	}

	EndBatchDraw();
	PlaySound("material\\New Divide.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	return result;
}

/*------------------------------------

	于2019.4.3完成初版TANK 00
	告一段落吧......这段时间有点累了
		                    阚兴博注

------------------------------------*/