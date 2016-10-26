#include<iostream>
#include<time.h>
#include<conio.h>
#include<windows.h>
//-1真雷标志
//-2临时移动标志
//-3真雷输出●雷标
//-4显雷标示数字
//-5假雷输出●
//-6-7-8
using namespace std;
class SL
{
public:
	SL()
	{
		int i, j;
		for (i = 0; i < 16; i++)
		{
			for (j = 0; j < 16; j++)
			{
				zi[i][j] = 0;
				gb[i][j] = 0;
			}
		}
	}
    friend void gotoXY(int x, int y);
	void jp();                    //接受键盘信息
    void map();
	void start();
private:
	int g = 0;
	char c;                       //判断是否继续新游戏
	int d;                        //产生雷数
	int zz=0;                     //真正雷数
	int k = 0;                    //雷中数字
	int gb[16][16];           //显示雷数组
	int NUM;         //标志的剩余雷数
	int qi = 0;       //1为标记雷，0为未标记雷
	int zi[16][16];   //雷盘
};
void gotoXY(int x, int y)
{
	COORD coord;           //定义一个坐标结构变量 
	HANDLE hscr;           //定义一个句柄 
	coord.X = x;             //给坐标赋值 
	coord.Y = y;
	hscr = GetStdHandle(STD_OUTPUT_HANDLE);  //获得标准输出句柄（就是显示器） 
	SetConsoleCursorPosition(hscr, coord);  //设置光标台坐标到指定坐标 
}
void SL::map()
{
	int hang, lie;
	for (hang = 0; hang < 16; hang++)
	{
		for (lie = 0; lie < 16; lie++)
		{
			if (zi[hang][lie] == -3 || zi[hang][lie] == -5)
				cout << "●";
			else if (zi[hang][lie] == -1)
			{
				cout << "○";
				g++;
			}
			else if (zi[hang][lie] == -2)
				cout << "⊙";
			else if (zi[hang][lie] == -4)
				cout <<" "<< gb[hang][lie];
			else 
				cout << "□";
		}
		cout << endl;
	}
	if (NUM >= 10)
	{
		gotoXY(60, 5);
		cout << "剩余雷数（仅供参考）：" << NUM;

	}
	else
	{
		gotoXY(61, 5);
		cout << "剩余雷数（仅供参考）：" << NUM;

	}
}
void SL::start()
{
m: int x = 0, y = 0;
	int i, j;                   //控制雷数循环输入,判断循环
	int hang, lie;               //随机坐标
	int s;                        //临时存数组
	int keyCode;
	gotoXY(25, 2);
	cout << "欢迎进入扫雷游戏!" << endl;
	gotoXY(3, 8);
	cout << "游戏说明：p键为标雷，o键位取消标雷，回车键为开雷，wsad键控制上下左右，⊙为移动标志，●为雷的标志，按任意键开始游戏";
	_getch();
	system("cls");
	gotoXY(25, 5);
I:cout << "（本地图16*16建议40颗雷！）请输入你想要设置的雷数（1--255）:";

	cin >> d;
	NUM = d;
	//zz = d;
	if (d<1 || d>255)
	{
		goto I;
	}
	    srand((unsigned)time(NULL));
		for (i = 0; i < d; i++)
		{
			hang = rand() % 16;
			lie = rand() % 16;
			zi[hang][lie] = -1;
			gb[hang][lie] = -1;
		}
		for (x = 0; x < 16; x++)
		{
			for (y = 0; y < 16; y++)
			{
				if (zi[x][y] == -1)
					continue;
				else
				{
					for (i = x; i >= x - 1 && i >= 0; i--)
					{
						for (j = y; j >= y - 1 && j >= 0; j--)
						{
							if (zi[i][j] == -1)
								k++;
							//左上
						}
					}
					for (i = x; i >= x - 1 && i >= 0; i--)
					{
						for (j = y + 1; j <= y + 1 && j < 16; j++)
						{
							if (zi[i][j] == -1)
								k++;
							//右上
						}
					}
					for (i = x + 1; i <= x + 1 && i <= 16; i++)
					{
						for (j = y; j >= y - 1 && j >= 0; j--)
						{
							if (zi[i][j] == -1)
								k++;
							//左下
						}
					}
					for (i = x + 1; i <= x + 1 && i < 16; i++)
					{
						for (j = y + 1; j <= y + 1 && j < 16; j++)
						{
							if (zi[i][j] == -1)
								k++;
							//右下
						}
					}
					zi[x][y] = k;
					gb[x][y] = k;
					k = 0;
				}
			}
		}
		s = zi[0][0];
		zi[0][0] = -2;
		system("cls");
		map();
		zi[0][0] = s;
		x = 0;
		y = 0;
		while (1)
		{
			keyCode = _getch();
			if (keyCode == 119)
			{
				x = x - 1;
				if (x < 0)
					x = 0;
				gotoXY(y * 2, x);
				s = zi[x][y];
				zi[x][y] = -2;
				gotoXY(0, 0);
				map();
				zi[x][y] = s;
				//printf("w键");
			}
			else if (keyCode == 115)
			{
				x++;
				if (x > 15)
					x = 15;
				gotoXY(y * 2, x);
				s = zi[x][y];
				zi[x][y] = -2;
				gotoXY(0, 0);
				map();
				zi[x][y] = s;
				//printf("s键");
			}
			else if (keyCode == 97)
			{
				y = y - 1;
				if (y < 0)
					y = 0;
				gotoXY(y * 2, x);
				s = zi[x][y];
				zi[x][y] = -2;
				gotoXY(0, 0);
				map();
				zi[x][y] = s;
				//printf("a键");
			}
			else if (keyCode == 100)
			{
				y++;
				if (y > 15)
					y = 15;
				gotoXY(x, y * 2);
				s = zi[x][y];
				zi[x][y] = -2;
				gotoXY(0, 0);
				map();
				zi[x][y] = s;
				//printf("d键");
			}
			else if (keyCode == 13)
			{
				gotoXY(y * 2, x);
				if (zi[x][y] != -5)
				{
					if (zi[x][y] == -1 || zi[x][y] == -3)
					{
						cout << "不幸！你踩到雷了，ＧＡＭＥＯＶＥＲ！是否要再来一局？!（y/n）";
						cin >> c;
						if (c == 'y' || c == 'Y')
						{
							goto m;
						}
						else
							exit(1);
					}
					if (zi[x][y] == 0)
					{
						zi[x][y] = -4;
						for (i = x - 1; i <= x + 1 && i >= 0 && i < 16; i++)
						{
							for (j = y - 1; j <= y + 1 && j >= 0 && j < 16; j++)
							{
								zi[i][j] = -4;
							}
						}
					}
					if (zi[x][y] != 0)
						zi[x][y] = -4;
					gotoXY(0, 0);
					map();
				}
				else
					cout << "●";
				//printf("回车键");
			}
			else if (keyCode == 112)
			{
				gotoXY(y * 2, x);
				if (zi[x][y] != -4)
				{
					if (zi[x][y] != -5 && zi[x][y] != -3)
					{
						if (NUM > 0)
						{
							if (zi[x][y] == -1)
								zi[x][y] = -3;
							else
							{
								zi[x][y] = -5;
							}
						}
						if (NUM <= 0)
							NUM = 0;
						if (NUM > 0)
							NUM--;
						gotoXY(0, 0);
						map();
						for (i = 0; i < 16; i++)
						{
							for (j = 0; j < 16; j++)
							{
								if (zi[i][j] == -1)
									zz++;
							}
						}
						if (zz == 0)
						{
							gotoXY(60, 7);
							cout << "所有雷全部找出，你赢了！是否要再来一局？!（y/n）";
							cin >> c;
							if (c == 'y' || c == 'Y')
							{
								goto m;
							}
							else
								exit(1);
						}
						zz = 0;
					}
				}
				else
					cout << " " << gb[x][y];
				//p键  标雷
			}
			else if (keyCode == 111)
			{
				gotoXY(y * 2,x);
				if (zi[x][y] == -3 || zi[x][y] == -5)
				{
					zi[x][y] = gb[x][y];
					if (NUM <= d)
						NUM++;
					gotoXY(0, 0);
					map();
				}
				//o键
			}
		}
	}
int main()
{
	SL sl;
	sl.start();
	return 0;
}


