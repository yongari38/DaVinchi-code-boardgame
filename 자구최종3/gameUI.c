#include "gameUI.h"
#include "DoubleLinkedList.h"

int TURN;
int TURN_num;
int MAX_QUEUE_SIZE;
//=======색깔관련 함수==============================================
//텍스트, 배경색 모두 변경 함수
void setColor(int color, int bgcolor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((bgcolor & 0xf) << 4) | (color & 0xf));
}
//텍스트 색상 변경 함수
void setFontColor(int color) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (info.wAttributes & 0xf0) | (color & 0xf));
}
//배경 색상 변경 함수
void setBgColor(int bgcolor) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((bgcolor & 0xf) << 4) | (info.wAttributes & 0xf));
}
//텍스트 색상 획득 함수
int getFontColor() {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	return info.wAttributes & 0xf;
}
//배경 색상 획득 함수
int getBgColor() {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	return (info.wAttributes & 0xf0) >> 4;
}
//텍스트 컬러 기본값 
__inline void resetFontColor() {
	setFontColor(7);
}
//배경색 기본값
__inline void resetBgColor() {
	setBgColor(0);
}
//텍스트, 배경색 기본값
__inline void resetColor() {
	setColor(7, 0);
}
//======================================================================
void gotoP(int x, int y) {   // 가로 좌표, 세로 좌표
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void showEdge() {
	gotoP(0, 0);
	if (MAX_QUEUE_SIZE == HARD)
		setColor(0, 12);
	else if (MAX_QUEUE_SIZE == EASY)
		setColor(0, 14);

	for (int i = 0; i < LENGTH / 2; i++) {
		printf("▦");
	}
	for (int i = 1; i < LINES_MAX; i++) {
		gotoP(0, i); printf("▦");
		gotoP(LENGTH - 2, i); printf("▦");
		//Sleep(1);	닦아내기 효과
	}
	for (int i = 0; i < LENGTH / 2; i++) {
		printf("▦");
	}
	resetColor();
}

void showChat() {

	gotoP(35, 13);
	for (int i = 0; i < 35; i++) {
		printf("▩");
	}

	for (int i = 14; i < 38; i++) {
		gotoP(35, i); printf("▩");
		gotoP(103, i); printf("▩");
	}

	gotoP(35, 38);
	for (int i = 0; i < 35; i++) {
		printf("▩");
	}
	// 잡다한 tip
	gotoP(6, 17); printf("┏━━━━━━━━━━━━━━━━━━━━━━┓");
	for (int i = 0; i < 7; i++) {
		gotoP(6, 18 + i); printf("┃");   gotoP(6 + 23, 18 + i); printf("┃");
	}
	gotoP(8, 19); printf("®: 공개 상태의 블럭");
	gotoP(8, 20); printf("⊙: 방금 가져온 블럭");

	gotoP(8, 22); printf("블럭이 모두 공개되면");
	gotoP(8, 23); printf("\t  패배합니다");
	gotoP(6, 24); printf("┗━━━━━━━━━━━━━━━━━━━━━━┛");

	int line = 12;
	gotoP(6, 14 + line); printf("┏━━━━━━━━━━━━━━━━━━━━━━┓");
	for (int i = 0; i < 5; i++) {
		gotoP(6, 15 + line + i); printf("┃"); gotoP(6 + 23, 15 + line + i); printf("┃");
	}
	gotoP(8, 16 + line); printf("  덱이 모두 소진되면");
	gotoP(8, 17 + line); printf("\t무승부입니다");
	gotoP(8, 18 + line); printf("   게임을 종료합니다");
	gotoP(6, 20 + line); printf("┗━━━━━━━━━━━━━━━━━━━━━━┛");

	gotoP(LENGTH - 30, 15); printf("┏━━━━━━━━━━━━━━━━━━━━━━┓");
	for (int i = 0; i < 19; i++) {
		gotoP(LENGTH - 30, 16 + i); printf("┃");   gotoP(LENGTH - 7, 16 + i); printf("┃");
	}
	gotoP(LENGTH - 28, 17); printf("    자료구조 20조");
	gotoP(LENGTH - 28, 18); printf("     Term Project");

	gotoP(LENGTH - 28, 20); printf("  Board Game,");
	gotoP(LENGTH - 28, 21); printf("      'DA VINCI-CODE'");

	gotoP(LENGTH - 28, 23); printf("    <역할 분담>");

	gotoP(LENGTH - 28, 25); printf("전체 개괄 코드 구현:");
	gotoP(LENGTH - 28, 26); printf("    2014140419 김윤성");
	gotoP(LENGTH - 28, 27); printf("    2017320132 장연석");
	gotoP(LENGTH - 28, 29); printf("컴퓨터 의사결정 구현:");
	gotoP(LENGTH - 28, 30); printf("    2017320243 정호용");
	gotoP(LENGTH - 28, 32); printf("중간,기말보고서,발표:");
	gotoP(LENGTH - 28, 33); printf("    2016250053 김은채");

	gotoP(LENGTH - 30, 35); printf("┗━━━━━━━━━━━━━━━━━━━━━━┛");
}

void clearChat() {
	for (int i = 14; i < 38; i++) {
		for (int j = 37; j < 102; j++) {
			gotoP(j, i); printf(" ");
		}
	}
	//gotoP(14, 38);	// 다음 입력을 시작할 부분으로 커서 이동.
}

int showLevel() {
	CLEAR();
	showEdge();

	int i = 5;

	gotoP(LENGTH / 2 - 40, 1 + i); printf("            '##:::::::'########:'##::::'##:'########:'##:::::::        \n");
	gotoP(LENGTH / 2 - 40, 2 + i); printf("             ##::::::: ##.....:: ##:::: ##: ##.....:: ##:::::::        \n");
	gotoP(LENGTH / 2 - 40, 3 + i); printf("             ##::::::: ##::::::: ##:::: ##: ##::::::: ##:::::::        \n");
	gotoP(LENGTH / 2 - 40, 4 + i); printf("             ##::::::: ######::: ##:::: ##: ######::: ##:::::::        \n");
	gotoP(LENGTH / 2 - 40, 5 + i); printf("             ##::::::: ##...::::. ##:: ##:: ##...:::: ##:::::::        \n");
	gotoP(LENGTH / 2 - 40, 6 + i); printf("             ##::::::: ##::::::::. ## ##::: ##::::::: ##:::::::        \n");
	gotoP(LENGTH / 2 - 40, 7 + i); printf("             ########: ########:::. ###:::: ########: ########:        \n");
	gotoP(LENGTH / 2 - 40, 8 + i); printf("            ........::........:::::...:::::........::........::        \n");

	setColor(14, 0);
	gotoP(LENGTH / 2 - 40, 14 + i); printf("                    ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓                \n");
	gotoP(LENGTH / 2 - 40, 15 + i); printf("                    ┃                               ┃                \n");
	gotoP(LENGTH / 2 - 40, 16 + i); printf("                    ┃   .-----.---.-.-----.--.--.   ┃                \n");
	gotoP(LENGTH / 2 - 40, 17 + i); printf("                    ┃   |  -__|  _  |__ --|  |  |   ┃                \n");
	gotoP(LENGTH / 2 - 40, 18 + i); printf("                    ┃   |_____|___._|_____|___  |   ┃                \n");
	gotoP(LENGTH / 2 - 40, 19 + i); printf("                    ┃                     |_____|   ┃                \n");
	gotoP(LENGTH / 2 - 40, 20 + i); printf("                    ┃                               ┃                \n");
	gotoP(LENGTH / 2 - 40, 21 + i); printf("                    ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛                \n");
	setColor(12, 0);
	gotoP(LENGTH / 2 - 40, 24 + i); printf("                                                                      \n");
	gotoP(LENGTH / 2 - 40, 25 + i); printf("                         __                  __                       \n");
	gotoP(LENGTH / 2 - 40, 26 + i); printf("                        |  |--.---.-.----.--|  |                      \n");
	gotoP(LENGTH / 2 - 40, 27 + i); printf("                        |     |  _  |   _|  _  |                      \n");
	gotoP(LENGTH / 2 - 40, 28 + i); printf("                        |__|__|___._|__| |_____|                      \n");
	gotoP(LENGTH / 2 - 40, 29 + i); printf("                                                                      \n");
	gotoP(LENGTH / 2 - 40, 30 + i); printf("                                                                      \n");
	resetColor();
	gotoP(LENGTH / 2 - 40, 35 + i); printf("               방향키로 선택 후 Enter 또는 Space키를 누르세요.              \n");

	//while (getch() != 0) getch();	// 찌꺼기 입력버퍼 비우기

	int selectLevel; // 방향키 받는 변수
	int UD = UP_CHOSEN;         // 사용자가 윗쪽, 아랫쪽 선택 여부 변수

	while (TRUE) {
		selectLevel = getch();
		if (selectLevel == ENTER || selectLevel == ' ') {
			if (UD == UP_CHOSEN)
				return EASY;
			else if (UD == DOWN_CHOSEN)
				return HARD;
		}
		if (selectLevel == 0 || selectLevel == 0xe0) {
			selectLevel = getch();
			if (selectLevel == UP) { // 윗쪽 방향키

				UD = UP_CHOSEN;	

				setColor(14,0);
				gotoP(LENGTH / 2 - 40, 14 + i); printf("                    ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓                \n");
				gotoP(LENGTH / 2 - 40, 15 + i); printf("                    ┃                               ┃                \n");
				gotoP(LENGTH / 2 - 40, 16 + i); printf("                    ┃   .-----.---.-.-----.--.--.   ┃                \n");
				gotoP(LENGTH / 2 - 40, 17 + i); printf("                    ┃   |  -__|  _  |__ --|  |  |   ┃                \n");
				gotoP(LENGTH / 2 - 40, 18 + i); printf("                    ┃   |_____|___._|_____|___  |   ┃                \n");
				gotoP(LENGTH / 2 - 40, 19 + i); printf("                    ┃                     |_____|   ┃                \n");
				gotoP(LENGTH / 2 - 40, 20 + i); printf("                    ┃                               ┃                \n");
				gotoP(LENGTH / 2 - 40, 21 + i); printf("                    ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛                \n");
				setColor(12, 0);
				gotoP(LENGTH / 2 - 40, 24 + i); printf("                                                                      \n");
				gotoP(LENGTH / 2 - 40, 25 + i); printf("                         __                  __                       \n");
				gotoP(LENGTH / 2 - 40, 26 + i); printf("                        |  |--.---.-.----.--|  |                      \n");
				gotoP(LENGTH / 2 - 40, 27 + i); printf("                        |     |  _  |   _|  _  |                      \n");
				gotoP(LENGTH / 2 - 40, 28 + i); printf("                        |__|__|___._|__| |_____|                      \n");
				gotoP(LENGTH / 2 - 40, 29 + i); printf("                                                                      \n");
				gotoP(LENGTH / 2 - 40, 30 + i); printf("                                                                      \n");
				resetColor();
				MAX_QUEUE_SIZE = EASY;
				showEdge();
			}
			else if (selectLevel == DOWN) { // 아랫쪽 방향키

				UD = DOWN_CHOSEN;
				setColor(14, 0);
				gotoP(LENGTH / 2 - 40, 14 + i); printf("                                                                      \n");
				gotoP(LENGTH / 2 - 40, 15 + i); printf("                                                                      \n");
				gotoP(LENGTH / 2 - 40, 16 + i); printf("                        .-----.---.-.-----.--.--.                     \n");
				gotoP(LENGTH / 2 - 40, 17 + i); printf("                        |  -__|  _  |__ --|  |  |                     \n");
				gotoP(LENGTH / 2 - 40, 18 + i); printf("                        |_____|___._|_____|___  |                     \n");
				gotoP(LENGTH / 2 - 40, 19 + i); printf("                                          |_____|                     \n");
				gotoP(LENGTH / 2 - 40, 20 + i); printf("                                                                      \n");
				gotoP(LENGTH / 2 - 40, 21 + i); printf("                                                                      \n");
				setColor(12, 0);
				gotoP(LENGTH / 2 - 40, 24 + i); printf("                    ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓                \n");
				gotoP(LENGTH / 2 - 40, 25 + i); printf("                    ┃    __                  __     ┃                  \n");
				gotoP(LENGTH / 2 - 40, 26 + i); printf("                    ┃   |  |--.---.-.----.--|  |    ┃                 \n");
				gotoP(LENGTH / 2 - 40, 27 + i); printf("                    ┃   |     |  _  |   _|  _  |    ┃                 \n");
				gotoP(LENGTH / 2 - 40, 28 + i); printf("                    ┃   |__|__|___._|__| |_____|    ┃                 \n");
				gotoP(LENGTH / 2 - 40, 29 + i); printf("                    ┃                               ┃                 \n");
				gotoP(LENGTH / 2 - 40, 30 + i); printf("                    ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛                \n");
				resetColor();
				MAX_QUEUE_SIZE = HARD;
				showEdge();
			}
		}
	}
}

int showOrder()
{
	CLEAR();
	showEdge();

	int select;       // 방향키, 엔터 선택 변수


	//srand((int)time(NULL));
	int firstLR = rand() % 2;         // 왼쪽, 오른쪽 먼저하는 경우의 카드 결정 변수

	int i = 5;


	gotoP(LENGTH / 2 - 40, 1 + i); printf("           :'#######::'########::'########::'########:'########::  \n");
	gotoP(LENGTH / 2 - 40, 2 + i); printf("           '##.... ##: ##.... ##: ##.... ##: ##.....:: ##.... ##:  \n");
	gotoP(LENGTH / 2 - 40, 3 + i); printf("            ##:::: ##: ##:::: ##: ##:::: ##: ##::::::: ##:::: ##:  \n");
	gotoP(LENGTH / 2 - 40, 4 + i); printf("            ##:::: ##: ########:: ##:::: ##: ######::: ########::  \n");
	gotoP(LENGTH / 2 - 40, 5 + i); printf("            ##:::: ##: ##.. ##::: ##:::: ##: ##...:::: ##.. ##:::  \n");
	gotoP(LENGTH / 2 - 40, 6 + i); printf("            ##:::: ##: ##::. ##:: ##:::: ##: ##::::::: ##::. ##::  \n");
	gotoP(LENGTH / 2 - 40, 7 + i); printf("           . #######:: ##::: .##: ########:: ########: ##::: .##:   \n");
	gotoP(LENGTH / 2 - 40, 8 + i); printf("           : .......:: : ..:::: : ..::........:: : ........::..::  \n");

	gotoP(LENGTH / 2 - 40, 14 + i); printf("          ┏━━━━━━━━━━━━━━━━━━━━━━┓   \t ┏━━━━━━━━━━━━━━━━━━━━━━┓   \n");
	gotoP(LENGTH / 2 - 40, 15 + i); printf("          ┃ /////////////////////┃   \t ┃ /////////////////////┃   \n");
	gotoP(LENGTH / 2 - 40, 16 + i); printf("          ┃ /////////////////////┃   \t ┃ /////////////////////┃   \n");
	gotoP(LENGTH / 2 - 40, 17 + i); printf("          ┃ /////////////////////┃   \t ┃ /////////////////////┃   \n");
	gotoP(LENGTH / 2 - 40, 18 + i); printf("          ┃ /////////////////////┃   \t ┃ /////////////////////┃   \n");
	gotoP(LENGTH / 2 - 40, 19 + i); printf("          ┃ /////////////////////┃   \t ┃ /////////////////////┃   \n");
	gotoP(LENGTH / 2 - 40, 20 + i); printf("          ┃ /////////////////////┃   \t ┃ /////////////////////┃   \n");
	gotoP(LENGTH / 2 - 40, 21 + i); printf("          ┃ /////////////////////┃   \t ┃ /////////////////////┃   \n");
	gotoP(LENGTH / 2 - 40, 22 + i); printf("          ┃ /////////////////////┃   \t ┃ /////////////////////┃   \n");
	gotoP(LENGTH / 2 - 40, 23 + i); printf("          ┃ /////////////////////┃   \t ┃ /////////////////////┃   \n");
	gotoP(LENGTH / 2 - 40, 24 + i); printf("          ┃ /////////////////////┃   \t ┃ /////////////////////┃   \n");
	gotoP(LENGTH / 2 - 40, 25 + i); printf("          ┃ /////////////////////┃   \t ┃ /////////////////////┃   \n");
	gotoP(LENGTH / 2 - 40, 26 + i); printf("          ┃ /////////////////////┃   \t ┃ /////////////////////┃   \n");
	gotoP(LENGTH / 2 - 40, 27 + i); printf("          ┃ /////////////////////┃   \t ┃ /////////////////////┃   \n");
	gotoP(LENGTH / 2 - 40, 28 + i); printf("          ┗━━━━━━━━━━━━━━━━━━━━━━┛   \t ┗━━━━━━━━━━━━━━━━━━━━━━┛   \n");

	gotoP(LENGTH / 2 - 40, 31 + i); printf("                      ▲             \t                           \n");
	gotoP(LENGTH / 2 - 40, 32 + i); printf("                     ▲▲             \t                           \n");
	gotoP(LENGTH / 2 - 40, 33 + i); printf("                    ▲▲▲             \t                           \n");

	gotoP(LENGTH / 2 - 40, 36 + i); printf("                 방향키로 선택 후 Enter 또는 Space키를 누르세요.         \n");

	//while (getch() != 0) getch();   // 찌꺼기 입력버퍼 비우기

	int LR = LEFT_CHOSEN;         // 사용자가 왼쪽, 오른쪽 선택 여부 변수

	while (TRUE) {
		select = getch();
		if (select == ENTER || select == ' ') {
			if (firstLR == LEFT_CHOSEN) {
				gotoP(LENGTH / 2 - 40, 14 + i); printf("          ┏━━━━━━━━━━━━━━━━━━━━━━┓   \t ┏━━━━━━━━━━━━━━━━━━━━━━┓   \n");
				gotoP(LENGTH / 2 - 40, 15 + i); printf("          ┃                      ┃   \t ┃                      ┃   \n");
				gotoP(LENGTH / 2 - 40, 16 + i); printf("          ┃                      ┃   \t ┃                      ┃   \n");
				gotoP(LENGTH / 2 - 40, 17 + i); printf("          ┃                      ┃   \t ┃                      ┃   \n");
				gotoP(LENGTH / 2 - 40, 18 + i); printf("          ┃    #                 ┃   \t ┃  ####                ┃   \n");
				gotoP(LENGTH / 2 - 40, 19 + i); printf("          ┃   ##    ####  #####  ┃   \t ┃ #    # #    # #####  ┃   \n");
				gotoP(LENGTH / 2 - 40, 20 + i); printf("          ┃  # #   #        #    ┃   \t ┃      # ##   # #    # ┃   \n");
				gotoP(LENGTH / 2 - 40, 21 + i); printf("          ┃    #    ####    #    ┃   \t ┃  ####  # #  # #    # ┃   \n");
				gotoP(LENGTH / 2 - 40, 22 + i); printf("          ┃    #        #   #    ┃   \t ┃ #      #  # # #    # ┃   \n");
				gotoP(LENGTH / 2 - 40, 23 + i); printf("          ┃    #   #    #   #    ┃   \t ┃ #      #   ## #    # ┃   \n");
				gotoP(LENGTH / 2 - 40, 24 + i); printf("          ┃  #####  ####    #    ┃   \t ┃ ###### #    # #####  ┃   \n");
				gotoP(LENGTH / 2 - 40, 25 + i); printf("          ┃                      ┃   \t ┃                      ┃   \n");
				gotoP(LENGTH / 2 - 40, 26 + i); printf("          ┃                      ┃   \t ┃                      ┃   \n");
				gotoP(LENGTH / 2 - 40, 27 + i); printf("          ┃                      ┃   \t ┃                      ┃   \n");
				gotoP(LENGTH / 2 - 40, 28 + i); printf("          ┃                      ┃   \t ┃                      ┃   \n");
				gotoP(LENGTH / 2 - 40, 29 + i); printf("          ┗━━━━━━━━━━━━━━━━━━━━━━┛   \t ┗━━━━━━━━━━━━━━━━━━━━━━┛   \n");
			}
			else if (firstLR == RIGHT_CHOSEN) {
				gotoP(LENGTH / 2 - 40, 14 + i); printf("          ┏━━━━━━━━━━━━━━━━━━━━━━┓   \t ┏━━━━━━━━━━━━━━━━━━━━━━┓   \n");
				gotoP(LENGTH / 2 - 40, 15 + i); printf("          ┃                      ┃   \t ┃                      ┃   \n");
				gotoP(LENGTH / 2 - 40, 16 + i); printf("          ┃                      ┃   \t ┃                      ┃   \n");
				gotoP(LENGTH / 2 - 40, 17 + i); printf("          ┃                      ┃   \t ┃                      ┃   \n");
				gotoP(LENGTH / 2 - 40, 18 + i); printf("          ┃  ####                ┃   \t ┃    #                 ┃   \n");
				gotoP(LENGTH / 2 - 40, 19 + i); printf("          ┃ #    # #    # #####  ┃   \t ┃   ##    ####  #####  ┃   \n");
				gotoP(LENGTH / 2 - 40, 20 + i); printf("          ┃      # ##   # #    # ┃   \t ┃  # #   #        #    ┃   \n");
				gotoP(LENGTH / 2 - 40, 21 + i); printf("          ┃  ####  # #  # #    # ┃   \t ┃    #    ####    #    ┃   \n");
				gotoP(LENGTH / 2 - 40, 22 + i); printf("          ┃ #      #  # # #    # ┃   \t ┃    #        #   #    ┃   \n");
				gotoP(LENGTH / 2 - 40, 23 + i); printf("          ┃ #      #   ## #    # ┃   \t ┃    #   #    #   #    ┃   \n");
				gotoP(LENGTH / 2 - 40, 24 + i); printf("          ┃ ###### #    # #####  ┃   \t ┃  #####  ####    #    ┃   \n");
				gotoP(LENGTH / 2 - 40, 25 + i); printf("          ┃                      ┃   \t ┃                      ┃   \n");
				gotoP(LENGTH / 2 - 40, 26 + i); printf("          ┃                      ┃   \t ┃                      ┃   \n");
				gotoP(LENGTH / 2 - 40, 27 + i); printf("          ┃                      ┃   \t ┃                      ┃   \n");
				gotoP(LENGTH / 2 - 40, 28 + i); printf("          ┃                      ┃   \t ┃                      ┃   \n");
				gotoP(LENGTH / 2 - 40, 29 + i); printf("          ┗━━━━━━━━━━━━━━━━━━━━━━┛   \t ┗━━━━━━━━━━━━━━━━━━━━━━┛   \n");
			}

			if (firstLR == LR) {
				gotoP(LENGTH / 2 - 40, 36 + i); printf("   db    db  .d88b.  db    db        d88888b d888888b d8888b. .d8888. d888888b   \n");
				gotoP(LENGTH / 2 - 40, 37 + i); printf("   `8b  d8' .8P  Y8. 88    88        88'       `88'   88  `8D 88'  YP `~~88~~'   \n");
				gotoP(LENGTH / 2 - 40, 38 + i); printf("    `8bd8'  88    88 88    88        88ooo      88    88oobY' `8bo.      88      \n");
				gotoP(LENGTH / 2 - 40, 39 + i); printf("      88    88    88 88    88        88~~~      88    88`8b     `Y8b.    88      \n");
				gotoP(LENGTH / 2 - 40, 40 + i); printf("      88    `8b  d8' 88b  d88        88        .88.   88 `88. db   8D    88      \n");
				gotoP(LENGTH / 2 - 40, 41 + i); printf("      YP     `Y88P'  ~Y8888P'        YP      Y888888P 88   YD `8888Y'    YP      \n");

				//gotoP(LENGTH / 2 - 40, 38 + i); printf("                             PRESS ANY KEY");
				//getch();

				return USER;
			}
			else {
				gotoP(LENGTH / 2 - 40, 36 + i); printf("    .o88b.  .d88b.  .88b  d88.        d88888b d888888b d8888b. .d8888. d888888b  \n");
				gotoP(LENGTH / 2 - 40, 37 + i); printf("   d8P  Y8 .8P  Y8. 88'YbdP`88        88'       `88'   88  `8D 88'  YP `~~88~~'  \n");
				gotoP(LENGTH / 2 - 40, 38 + i); printf("   8P      88    88 88  88  88        88ooo      88    88oobY' `8bo.      88     \n");
				gotoP(LENGTH / 2 - 40, 39 + i); printf("   8b      88    88 88  88  88        88~~~      88    88`8b     `Y8b.    88     \n");
				gotoP(LENGTH / 2 - 40, 40 + i); printf("   Y8b  d8 `8b  d8' 88  88  88        88        .88.   88 `88. db   8D    88     \n");
				gotoP(LENGTH / 2 - 40, 41 + i); printf("    `Y88P'  `Y88P'  YP  YP  YP        YP      Y888888P 88   YD `8888Y'    YP     \n");

				//gotoP(LENGTH / 2 - 40, 38 + i); printf("                             PRESS ANY KEY");
				//getch();

				return COM;
			}
		}
		if (select == 0 || select == 0xe0) {
			select = getch();
			if (select == LEFT) { // 왼쪽 방향키

				LR = LEFT_CHOSEN;

				gotoP(LENGTH / 2 - 40, 31 + i); printf("                      ▲             \t                           \n");
				gotoP(LENGTH / 2 - 40, 32 + i); printf("                     ▲▲             \t                           \n");
				gotoP(LENGTH / 2 - 40, 33 + i); printf("                    ▲▲▲             \t                           \n");

				//gotoP(LENGTH / 2 - 40, 36 + i); printf("                 방향키로 선택 후 Enter 또는 Space키를 누르세요.         \n");
			}
			else if (select == RIGHT) { // 오른쪽 방향키

				LR = RIGHT_CHOSEN;

				gotoP(LENGTH / 2 - 40, 31 + i); printf("                                     \t             ▲            \n");
				gotoP(LENGTH / 2 - 40, 32 + i); printf("                                     \t            ▲▲            \n");
				gotoP(LENGTH / 2 - 40, 33 + i); printf("                                     \t           ▲▲▲            \n");

				//gotoP(LENGTH / 2 - 40, 36 + i); printf("                 방향키로 선택 후 Enter 또는 Space키를 누르세요.         \n");
			}
		}
	}
}

void showMain() {

	int select;
	int whoIsFirst = 0;

	int i = 5;
	gotoP(LENGTH / 2 - 40, 1 + i); printf("      "); printf(":::::::-.    :::.    :::      .::.::::::.    :::.  .,-:::::  ::: \n");
	gotoP(LENGTH / 2 - 40, 2 + i); printf("      "); printf(" ;;,   `';,  ;;`;;   ';;,   ,;;;' ;;;`;;;;,  `;;;,;;;'````'  ;;; \n");
	gotoP(LENGTH / 2 - 40, 3 + i); printf("      "); printf(" `[[     [[ ,[[ '[[,  \\[[  .[[/   [[[  [[[[[. '[[[[[         [[[ \n");
	gotoP(LENGTH / 2 - 40, 4 + i); printf("      "); printf("  $$,    $$c$$$cc$$$c  Y$c.$$\"    $$$  $$$ \"Y$c$$$$$         $$$ \n");
	gotoP(LENGTH / 2 - 40, 5 + i); printf("      "); printf("  888_,o8P' 888   888,  Y88P      888  888    Y88`88bo,__,o, 888 \n");
	gotoP(LENGTH / 2 - 40, 6 + i); printf("      "); printf("  MMMMP\"`   YMM   \"\"`    MP       MMM  MMM     YM  \"YUMMMMMP\"MMM \n");


	gotoP(LENGTH / 2 - 40, 10 + i); printf("                 "); printf("  .,-:::::     ...    :::::::-.  .,::::::  \n");
	gotoP(LENGTH / 2 - 40, 11 + i); printf("                 "); printf(",;;;'````'  .;;;;;;;.  ;;,   `';,;;;;''''  \n");
	gotoP(LENGTH / 2 - 40, 12 + i); printf("                 "); printf("[[[        ,[[     \\[[,`[[     [[ [[cccc   \n");
	gotoP(LENGTH / 2 - 40, 13 + i); printf("                 "); printf("$$$        $$$,     $$$ $$,    $$ $$\"\"\"\"   \n");
	gotoP(LENGTH / 2 - 40, 14 + i); printf("                 "); printf("`88bo,__,o,\"888,_ _,88P 888_,o8P' 888oo,__ \n");
	gotoP(LENGTH / 2 - 40, 15 + i); printf("                 "); printf("  \"YUMMMMMP\" \"YMMMMMP\"  MMMMP\"`   \"\"\"\"YUMMM ");

	setColor(0, 15);
	gotoP(LENGTH / 2 - 6, 30); printf("  게임 시작  ");
	gotoP(LENGTH / 2 - 6, 33); printf("  게임 종료  ");
	resetColor();

	gotoP(LENGTH / 2 - 9, 30); printf("▶");
	gotoP(LENGTH / 2 - 9, 33); printf("  ");

	int chosen = TRUE;

	while (TRUE) {
		select = getch();
		if (select == ENTER || select == ' ') {
			if (chosen == TRUE) {
				MAX_QUEUE_SIZE = showLevel();
				TURN = showOrder();
				// 게임 진행
				return;
			}
			else if (chosen == FALSE)
				exit(0);
		}
		if (select == 0 || select == 0xe0) {
			select = getch();
			if (select == UP) { // 위쪽 방향키
				chosen = TRUE;
				gotoP(LENGTH / 2 - 9, 30); printf("▶");
				gotoP(LENGTH / 2 - 9, 33); printf("  ");
				gotoP(LENGTH, 50);
			}
			else if (select == DOWN) { // 아래쪽 방향키
				chosen = FALSE;
				gotoP(LENGTH / 2 - 9, 30); printf("  ");
				gotoP(LENGTH / 2 - 9, 33); printf("▶");
				gotoP(LENGTH, 50);
			}
		}
	}
}

void SetCursorInvisible() {	// 커서를 투명하게 만드는 함수
	HANDLE HCursor = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(HCursor, &info);
}

void printBlock(Block* b, int x, int y) {
	char joker = 'J';
	if (b->color == GREEN)		setColor(0, 10);
	else if (b->color == WHITE)	setColor(0, 15);
	else						setColor(12, 12);	// print red box if wrong color
	gotoP(x, y + 0);		printf("        ");
	gotoP(x, y + 1);
	if (b->number == 12)		printf("    %-4c",  'J');
	else						printf("   %2d   ", b->number);
	gotoP(x, y + 2);		printf("        ");
	gotoP(x, y + 3);
	if (b->revealed == TRUE)	printf("   ®   ");	// 공개된 블럭
	else						printf("        ");
	gotoP(x, y + 4);
	if (b->get_turn == TURN_num)printf("   ⊙   ");	// 이번턴에 draw한 블럭					// 이거 제대로 출력 안됨!!!
	else						printf("        ");
	resetColor();
}

void printHand(Block* head) {

	int row;
	if (head == &p_Block) {			// USER 패 출력
		row = 40;
		gotoP(LENGTH / 2 - 5, row);	printf("PLAYER HAND");
	}
	else if (head == &c_Block) {	// COM 패 출력
		row = 3;
		gotoP(LENGTH / 2 - 5, row);	printf("COMPUTER HAND");
	}
	else {
		printf("printHand함수 오류");
	}

	// 패의 블럭 갯수 count
	int count = 0;
	for (Block* b = head->rlink; b != head; b = b->rlink) {
		count++;
	}
	// 가운데 정렬.
	int x = LENGTH / 2 - (BLOCK_WIDTH + 2) * (count / 2);		// 한블럭 할당크기: (BLOCK_WIDTH + 2), 늘려야하나? 아마 늘려야할듯.
	int y = 3 + row;
	for (Block *b = head->rlink; b != head; b = b->rlink) {
		if(head==&p_Block||b->revealed==1)	// USER의 블럭 or COM의 공개된 블럭
			printBlock(b, x, y);
		else {	// COM의 비공개 블럭
			if (b->color == GREEN)			setColor(0, 10);
			else if (b->color == WHITE)		setColor(0, 15);
			else							setColor(12, 12);	// print red box if wrong color
			for (int i = 0; i < 5; i++) {
				gotoP(x, y + i);	printf("        ");
			}
			resetColor();
		}

		x += (BLOCK_WIDTH + 2);
	}
}

int whereJoker(Block*head) {
	int count = dll_count(head);
	if (count == 0)
		return 0;
	int index = 0, select;

	int row = 40;

	int x = LENGTH / 2 - (BLOCK_WIDTH + 2) * (count / 2);

	whereJoker_bar(x + (BLOCK_WIDTH + 2)*index, 3 + row);

	while (TRUE) {
		select = getch();


		if (select == 0 || select == 0xe0) {
			select = getch();
			if (select == RIGHT && index < count) { // 오른쪽 방향키 && 오른쪽끝
				whereJoker_unbar(x + (BLOCK_WIDTH + 2)*index, 3 + row);	// 전에꺼 지우고
				index++;
				whereJoker_bar(x + (BLOCK_WIDTH + 2)*index, 3 + row);		// 새거 씌우고
			}
			else if (select == LEFT && index > 0) { // 왼쪽 방향키 && 왼쪽끝
				whereJoker_unbar(x + (BLOCK_WIDTH + 2)*index, 3 + row);
				index--;
				whereJoker_bar(x + (BLOCK_WIDTH + 2)*index, 3 + row);
			}
		}
		else if (select == ENTER || select == ' ') {
			whereJoker_unbar(x + (BLOCK_WIDTH + 2)*index, 3 + row); // 전에꺼 지우고
			return index;
		}
	}

	printf("selectHand함수 오류_2\n");
	return NULL;	// 오류발생.
}


int whereWithJoker(int count, int x, int row) {
	if (count == 0)
		return 0;

	int index = 0, select;

	whereJoker_bar(x + (BLOCK_WIDTH + 2)*index, 3 + row);

	while (TRUE) {
		select = getch();

		if (select == 0 || select == 0xe0) {
			select = getch();
			if (select == RIGHT && index < count) { // 오른쪽 방향키 && 오른쪽끝
				whereJoker_unbar(x + (BLOCK_WIDTH + 2)*index, 3 + row);   // 전에꺼 지우고
				index++;
				whereJoker_bar(x + (BLOCK_WIDTH + 2)*index, 3 + row);      // 새거 씌우고
			}
			else if (select == LEFT && index > 0) { // 왼쪽 방향키 && 왼쪽끝
				whereJoker_unbar(x + (BLOCK_WIDTH + 2)*index, 3 + row);
				index--;
				whereJoker_bar(x + (BLOCK_WIDTH + 2)*index, 3 + row);
			}
		}
		else if (select == ENTER || select == ' ') {
			whereJoker_unbar(x + (BLOCK_WIDTH + 2)*index, 3 + row); // 전에꺼 지우고
			return index;
		}
	}
}
void whereJoker_bar(int x, int y) {
	setColor(9,9);
	for (int i = -1; i < 6; i++) {
		gotoP(x - 1 - 1, y +i);	printf("┃");
	}
	resetColor();
}
void whereJoker_unbar(int x, int y) {
	for (int i = -1; i < 6; i++) {
		gotoP(x - 1 - 1, y +i);	printf(" ");
	}
}

void BlockBoxing(int x, int y) {
	gotoP(x - 1-1, y - 1);	printf("┏━━━━━━━━━┓");
	// ↓이렇게하면 가운데 덮어씌워지니까
	//gotoP(x - 1, y + 0);	printf("#       #");
	//gotoP(x - 1, y + 1);	printf("#       #");
	//gotoP(x - 1, y + 2);	printf("#       #");
	//gotoP(x - 1, y + 3);	printf("#       #");
	//gotoP(x - 1, y + 4);	printf("#       #");
	// ↓이렇게 한다
	for (int i = 0; i < 5; i++) {
		gotoP(x - 1-1, y + i);	printf("┃");
		gotoP(x + BLOCK_WIDTH, y + i);	printf("┃");
	}
	gotoP(x - 1-1, y + 5);	printf("┗━━━━━━━━━┛");
}
void BlockUnboxing(int x, int y) {
	gotoP(x - 1-1, y - 1);	printf("           ");
	for (int i = 0; i < 5; i++) {
		gotoP(x - 1-1, y + i);	printf(" ");
		gotoP(x + BLOCK_WIDTH, y + i);	printf(" ");
	}
	gotoP(x - 1-1, y + 5);	printf("           ");
}

Block* selectBlock(Block*head) {	// output: 선태 블럭 index
	int row;
	if (head == &p_Block) {			// USER 패 출력
		row = 40;
	}
	else if (head == &c_Block) {	// COM 패 출력
		row = 3;
	}
	else {
		printf("selectHand함수 오류");
	}

	// 패의 블럭 갯수 count
	int count = dll_count(head);

	int x = LENGTH / 2 - (BLOCK_WIDTH + 2) * (count / 2);

	int index = 0;
	int select;

	BlockBoxing(x + (BLOCK_WIDTH + 2)*index, 3 + row);
	while (TRUE) {
		select = getch();

		
		if (select == 0 || select == 0xe0) {
			select = getch();
			if (select == RIGHT && index < count - 1) { // 오른쪽 방향키 && 오른쪽끝블럭 아닐때
				BlockUnboxing(x + (BLOCK_WIDTH + 2)*index, 3 + row);	// 전에꺼 지우고
				index++;
				BlockBoxing(x + (BLOCK_WIDTH + 2)*index, 3 + row);		// 새거 씌우고
			}
			else if (select == LEFT && index > 0) { // 왼쪽 방향키 && 왼쪽끝블럭 아닐때
				BlockUnboxing(x + (BLOCK_WIDTH + 2)*index, 3 + row);
				index--;
				BlockBoxing(x + (BLOCK_WIDTH + 2)*index, 3 + row);
			}
		}
		else if (select == ENTER || select == ' ') {
			//BlockUnboxing(x + (BLOCK_WIDTH + 2)*index, 3 + row); // 전에꺼 지우고
			break;
		}
	}
	

	int find = 0;
	for (Block* b = head->rlink; b != head; b = b->rlink, find++) {
		if (find == index) {
			gotoP(LENGTH / 2 - 10, 13);
			printf("block[%d] 블럭선택 완료", index);	// 여기까지 완료됬는지 알기위해 출력
			return b;
		}	
	}

	printf("selectHand함수 오류_2\n");
	return NULL;	// 오류발생.
}

int choose_guessNumber() {
	int count = dll_count(&p_Block);
	//BlockBoxing(LENGTH / 2 - (BLOCK_WIDTH + 2) * (count / 2) + (BLOCK_WIDTH + 2)*block_index, 3 + 3);	// 어디블럭 선택중인지 친절하게 표시.


	int choice = 0;

	gotoP(LENGTH / 2 - 20, 20);
	setColor(0,15);
	printf("0");	// 처음 수는 하양색으로 출력. 처음 enter누르면 이거 선택되니까.
	resetColor();
	printf("  1  2  3  4  5  6  7  8  9  10  11  J");
	
	int select;
	//int select = getch();

	while (TRUE) {
		select = getch();
		if (select == 0 || select == 0xe0) {
			select = getch();
			if (select == RIGHT && choice < 12) {		// 오른쪽 방향키 && 오른쪽끝
				choice++;
			}
			else if (select == LEFT && choice > 0) {	// 왼쪽 방향키 && 왼쪽끝
				choice--;
			}
		}
		else if (select == ENTER || select == ' ') {
			//BlockUnboxing(LENGTH / 2 - (BLOCK_WIDTH + 2) * (count / 2) + (BLOCK_WIDTH + 2)*block_index, 3 + 40);
			return choice;
		}
		gotoP(LENGTH / 2 - 20, 20);

		for (int i = 0; i < 13; i++) {
			if (i == choice) {
				setColor(0, 15);
				if (i == 12)
					printf("J");
				else
					printf("%d", i);
				resetColor();
				printf("  ");
			}
			else {
				if(i == 12)
					printf("J");
				else
					printf("%d  ", i);
			}
		}
	}
}

