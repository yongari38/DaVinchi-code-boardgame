#include "gameUI.h"
#include "DoubleLinkedList.h"

int TURN;
int TURN_num;
int MAX_QUEUE_SIZE;
//=======儀梃婦溼 л熱==============================================
//臢蝶お, 寡唳儀 賅舒 滲唳 л熱
void setColor(int color, int bgcolor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((bgcolor & 0xf) << 4) | (color & 0xf));
}
//臢蝶お 儀鼻 滲唳 л熱
void setFontColor(int color) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (info.wAttributes & 0xf0) | (color & 0xf));
}
//寡唳 儀鼻 滲唳 л熱
void setBgColor(int bgcolor) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((bgcolor & 0xf) << 4) | (info.wAttributes & 0xf));
}
//臢蝶お 儀鼻 �僱� л熱
int getFontColor() {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	return info.wAttributes & 0xf;
}
//寡唳 儀鼻 �僱� л熱
int getBgColor() {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	return (info.wAttributes & 0xf0) >> 4;
}
//臢蝶お 鏽楝 晦獄高 
__inline void resetFontColor() {
	setFontColor(7);
}
//寡唳儀 晦獄高
__inline void resetBgColor() {
	setBgColor(0);
}
//臢蝶お, 寡唳儀 晦獄高
__inline void resetColor() {
	setColor(7, 0);
}
//======================================================================
void gotoP(int x, int y) {   // 陛煎 謝ル, 撮煎 謝ル
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
		printf("〩");
	}
	for (int i = 1; i < LINES_MAX; i++) {
		gotoP(0, i); printf("〩");
		gotoP(LENGTH - 2, i); printf("〩");
		//Sleep(1);	欺嬴頂晦 �膩�
	}
	for (int i = 0; i < LENGTH / 2; i++) {
		printf("〩");
	}
	resetColor();
}

void showChat() {

	gotoP(35, 13);
	for (int i = 0; i < 35; i++) {
		printf("十");
	}

	for (int i = 14; i < 38; i++) {
		gotoP(35, i); printf("十");
		gotoP(103, i); printf("十");
	}

	gotoP(35, 38);
	for (int i = 0; i < 35; i++) {
		printf("十");
	}
	// 濩棻и tip
	gotoP(6, 17); printf("旨收收收收收收收收收收收收收收收收收收收收收收旬");
	for (int i = 0; i < 7; i++) {
		gotoP(6, 18 + i); printf("早");   gotoP(6 + 23, 18 + i); printf("早");
	}
	gotoP(8, 19); printf("Ｙ: 奢偃 鼻鷓曖 綰楣");
	gotoP(8, 20); printf("Ⅸ: 寞旎 陛螳螞 綰楣");

	gotoP(8, 22); printf("綰楣檜 賅舒 奢偃腎賊");
	gotoP(8, 23); printf("\t  ぬ寡м棲棻");
	gotoP(6, 24); printf("曲收收收收收收收收收收收收收收收收收收收收收收旭");

	int line = 12;
	gotoP(6, 14 + line); printf("旨收收收收收收收收收收收收收收收收收收收收收收旬");
	for (int i = 0; i < 5; i++) {
		gotoP(6, 15 + line + i); printf("早"); gotoP(6 + 23, 15 + line + i); printf("早");
	}
	gotoP(8, 16 + line); printf("  策檜 賅舒 模霞腎賊");
	gotoP(8, 17 + line); printf("\t鼠蝓睡殮棲棻");
	gotoP(8, 18 + line); printf("   啪歜擊 謙猿м棲棻");
	gotoP(6, 20 + line); printf("曲收收收收收收收收收收收收收收收收收收收收收收旭");

	gotoP(LENGTH - 30, 15); printf("旨收收收收收收收收收收收收收收收收收收收收收收旬");
	for (int i = 0; i < 19; i++) {
		gotoP(LENGTH - 30, 16 + i); printf("早");   gotoP(LENGTH - 7, 16 + i); printf("早");
	}
	gotoP(LENGTH - 28, 17); printf("    濠猿掘褻 20褻");
	gotoP(LENGTH - 28, 18); printf("     Term Project");

	gotoP(LENGTH - 28, 20); printf("  Board Game,");
	gotoP(LENGTH - 28, 21); printf("      'DA VINCI-CODE'");

	gotoP(LENGTH - 28, 23); printf("    <羲й 碟氬>");

	gotoP(LENGTH - 28, 25); printf("瞪羹 偃婪 囀萄 掘⑷:");
	gotoP(LENGTH - 28, 26); printf("    2014140419 梯彌撩");
	gotoP(LENGTH - 28, 27); printf("    2017320132 濰翱戮");
	gotoP(LENGTH - 28, 29); printf("闡У攪 曖餌唸薑 掘⑷:");
	gotoP(LENGTH - 28, 30); printf("    2017320243 薑�ˋ�");
	gotoP(LENGTH - 28, 32); printf("醞除,晦蜓爾堅憮,嫦ル:");
	gotoP(LENGTH - 28, 33); printf("    2016250053 梯擎瓣");

	gotoP(LENGTH - 30, 35); printf("曲收收收收收收收收收收收收收收收收收收收收收收旭");
}

void clearChat() {
	for (int i = 14; i < 38; i++) {
		for (int j = 37; j < 102; j++) {
			gotoP(j, i); printf(" ");
		}
	}
	//gotoP(14, 38);	// 棻擠 殮溘擊 衛濛й 睡碟戲煎 醴憮 檜翕.
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
	gotoP(LENGTH / 2 - 40, 14 + i); printf("                    旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬                \n");
	gotoP(LENGTH / 2 - 40, 15 + i); printf("                    早                               早                \n");
	gotoP(LENGTH / 2 - 40, 16 + i); printf("                    早   .-----.---.-.-----.--.--.   早                \n");
	gotoP(LENGTH / 2 - 40, 17 + i); printf("                    早   |  -__|  _  |__ --|  |  |   早                \n");
	gotoP(LENGTH / 2 - 40, 18 + i); printf("                    早   |_____|___._|_____|___  |   早                \n");
	gotoP(LENGTH / 2 - 40, 19 + i); printf("                    早                     |_____|   早                \n");
	gotoP(LENGTH / 2 - 40, 20 + i); printf("                    早                               早                \n");
	gotoP(LENGTH / 2 - 40, 21 + i); printf("                    曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭                \n");
	setColor(12, 0);
	gotoP(LENGTH / 2 - 40, 24 + i); printf("                                                                      \n");
	gotoP(LENGTH / 2 - 40, 25 + i); printf("                         __                  __                       \n");
	gotoP(LENGTH / 2 - 40, 26 + i); printf("                        |  |--.---.-.----.--|  |                      \n");
	gotoP(LENGTH / 2 - 40, 27 + i); printf("                        |     |  _  |   _|  _  |                      \n");
	gotoP(LENGTH / 2 - 40, 28 + i); printf("                        |__|__|___._|__| |_____|                      \n");
	gotoP(LENGTH / 2 - 40, 29 + i); printf("                                                                      \n");
	gotoP(LENGTH / 2 - 40, 30 + i); printf("                                                                      \n");
	resetColor();
	gotoP(LENGTH / 2 - 40, 35 + i); printf("               寞щ酈煎 摹鷗 �� Enter 傳朝 Space酈蒂 援腦撮蹂.              \n");

	//while (getch() != 0) getch();	// 鎬疏晦 殮溘幗ぷ 綠辦晦

	int selectLevel; // 寞щ酈 嫡朝 滲熱
	int UD = UP_CHOSEN;         // 餌辨濠陛 嶺薹, 嬴概薹 摹鷗 罹睡 滲熱

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
			if (selectLevel == UP) { // 嶺薹 寞щ酈

				UD = UP_CHOSEN;	

				setColor(14,0);
				gotoP(LENGTH / 2 - 40, 14 + i); printf("                    旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬                \n");
				gotoP(LENGTH / 2 - 40, 15 + i); printf("                    早                               早                \n");
				gotoP(LENGTH / 2 - 40, 16 + i); printf("                    早   .-----.---.-.-----.--.--.   早                \n");
				gotoP(LENGTH / 2 - 40, 17 + i); printf("                    早   |  -__|  _  |__ --|  |  |   早                \n");
				gotoP(LENGTH / 2 - 40, 18 + i); printf("                    早   |_____|___._|_____|___  |   早                \n");
				gotoP(LENGTH / 2 - 40, 19 + i); printf("                    早                     |_____|   早                \n");
				gotoP(LENGTH / 2 - 40, 20 + i); printf("                    早                               早                \n");
				gotoP(LENGTH / 2 - 40, 21 + i); printf("                    曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭                \n");
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
			else if (selectLevel == DOWN) { // 嬴概薹 寞щ酈

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
				gotoP(LENGTH / 2 - 40, 24 + i); printf("                    旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬                \n");
				gotoP(LENGTH / 2 - 40, 25 + i); printf("                    早    __                  __     早                  \n");
				gotoP(LENGTH / 2 - 40, 26 + i); printf("                    早   |  |--.---.-.----.--|  |    早                 \n");
				gotoP(LENGTH / 2 - 40, 27 + i); printf("                    早   |     |  _  |   _|  _  |    早                 \n");
				gotoP(LENGTH / 2 - 40, 28 + i); printf("                    早   |__|__|___._|__| |_____|    早                 \n");
				gotoP(LENGTH / 2 - 40, 29 + i); printf("                    早                               早                 \n");
				gotoP(LENGTH / 2 - 40, 30 + i); printf("                    曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭                \n");
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

	int select;       // 寞щ酈, 縛攪 摹鷗 滲熱


	//srand((int)time(NULL));
	int firstLR = rand() % 2;         // 豭薹, 螃艇薹 試盪ж朝 唳辦曖 蘋萄 唸薑 滲熱

	int i = 5;


	gotoP(LENGTH / 2 - 40, 1 + i); printf("           :'#######::'########::'########::'########:'########::  \n");
	gotoP(LENGTH / 2 - 40, 2 + i); printf("           '##.... ##: ##.... ##: ##.... ##: ##.....:: ##.... ##:  \n");
	gotoP(LENGTH / 2 - 40, 3 + i); printf("            ##:::: ##: ##:::: ##: ##:::: ##: ##::::::: ##:::: ##:  \n");
	gotoP(LENGTH / 2 - 40, 4 + i); printf("            ##:::: ##: ########:: ##:::: ##: ######::: ########::  \n");
	gotoP(LENGTH / 2 - 40, 5 + i); printf("            ##:::: ##: ##.. ##::: ##:::: ##: ##...:::: ##.. ##:::  \n");
	gotoP(LENGTH / 2 - 40, 6 + i); printf("            ##:::: ##: ##::. ##:: ##:::: ##: ##::::::: ##::. ##::  \n");
	gotoP(LENGTH / 2 - 40, 7 + i); printf("           . #######:: ##::: .##: ########:: ########: ##::: .##:   \n");
	gotoP(LENGTH / 2 - 40, 8 + i); printf("           : .......:: : ..:::: : ..::........:: : ........::..::  \n");

	gotoP(LENGTH / 2 - 40, 14 + i); printf("          旨收收收收收收收收收收收收收收收收收收收收收收旬   \t 旨收收收收收收收收收收收收收收收收收收收收收收旬   \n");
	gotoP(LENGTH / 2 - 40, 15 + i); printf("          早 /////////////////////早   \t 早 /////////////////////早   \n");
	gotoP(LENGTH / 2 - 40, 16 + i); printf("          早 /////////////////////早   \t 早 /////////////////////早   \n");
	gotoP(LENGTH / 2 - 40, 17 + i); printf("          早 /////////////////////早   \t 早 /////////////////////早   \n");
	gotoP(LENGTH / 2 - 40, 18 + i); printf("          早 /////////////////////早   \t 早 /////////////////////早   \n");
	gotoP(LENGTH / 2 - 40, 19 + i); printf("          早 /////////////////////早   \t 早 /////////////////////早   \n");
	gotoP(LENGTH / 2 - 40, 20 + i); printf("          早 /////////////////////早   \t 早 /////////////////////早   \n");
	gotoP(LENGTH / 2 - 40, 21 + i); printf("          早 /////////////////////早   \t 早 /////////////////////早   \n");
	gotoP(LENGTH / 2 - 40, 22 + i); printf("          早 /////////////////////早   \t 早 /////////////////////早   \n");
	gotoP(LENGTH / 2 - 40, 23 + i); printf("          早 /////////////////////早   \t 早 /////////////////////早   \n");
	gotoP(LENGTH / 2 - 40, 24 + i); printf("          早 /////////////////////早   \t 早 /////////////////////早   \n");
	gotoP(LENGTH / 2 - 40, 25 + i); printf("          早 /////////////////////早   \t 早 /////////////////////早   \n");
	gotoP(LENGTH / 2 - 40, 26 + i); printf("          早 /////////////////////早   \t 早 /////////////////////早   \n");
	gotoP(LENGTH / 2 - 40, 27 + i); printf("          早 /////////////////////早   \t 早 /////////////////////早   \n");
	gotoP(LENGTH / 2 - 40, 28 + i); printf("          曲收收收收收收收收收收收收收收收收收收收收收收旭   \t 曲收收收收收收收收收收收收收收收收收收收收收收旭   \n");

	gotoP(LENGTH / 2 - 40, 31 + i); printf("                      ∼             \t                           \n");
	gotoP(LENGTH / 2 - 40, 32 + i); printf("                     ∼∼             \t                           \n");
	gotoP(LENGTH / 2 - 40, 33 + i); printf("                    ∼∼∼             \t                           \n");

	gotoP(LENGTH / 2 - 40, 36 + i); printf("                 寞щ酈煎 摹鷗 �� Enter 傳朝 Space酈蒂 援腦撮蹂.         \n");

	//while (getch() != 0) getch();   // 鎬疏晦 殮溘幗ぷ 綠辦晦

	int LR = LEFT_CHOSEN;         // 餌辨濠陛 豭薹, 螃艇薹 摹鷗 罹睡 滲熱

	while (TRUE) {
		select = getch();
		if (select == ENTER || select == ' ') {
			if (firstLR == LEFT_CHOSEN) {
				gotoP(LENGTH / 2 - 40, 14 + i); printf("          旨收收收收收收收收收收收收收收收收收收收收收收旬   \t 旨收收收收收收收收收收收收收收收收收收收收收收旬   \n");
				gotoP(LENGTH / 2 - 40, 15 + i); printf("          早                      早   \t 早                      早   \n");
				gotoP(LENGTH / 2 - 40, 16 + i); printf("          早                      早   \t 早                      早   \n");
				gotoP(LENGTH / 2 - 40, 17 + i); printf("          早                      早   \t 早                      早   \n");
				gotoP(LENGTH / 2 - 40, 18 + i); printf("          早    #                 早   \t 早  ####                早   \n");
				gotoP(LENGTH / 2 - 40, 19 + i); printf("          早   ##    ####  #####  早   \t 早 #    # #    # #####  早   \n");
				gotoP(LENGTH / 2 - 40, 20 + i); printf("          早  # #   #        #    早   \t 早      # ##   # #    # 早   \n");
				gotoP(LENGTH / 2 - 40, 21 + i); printf("          早    #    ####    #    早   \t 早  ####  # #  # #    # 早   \n");
				gotoP(LENGTH / 2 - 40, 22 + i); printf("          早    #        #   #    早   \t 早 #      #  # # #    # 早   \n");
				gotoP(LENGTH / 2 - 40, 23 + i); printf("          早    #   #    #   #    早   \t 早 #      #   ## #    # 早   \n");
				gotoP(LENGTH / 2 - 40, 24 + i); printf("          早  #####  ####    #    早   \t 早 ###### #    # #####  早   \n");
				gotoP(LENGTH / 2 - 40, 25 + i); printf("          早                      早   \t 早                      早   \n");
				gotoP(LENGTH / 2 - 40, 26 + i); printf("          早                      早   \t 早                      早   \n");
				gotoP(LENGTH / 2 - 40, 27 + i); printf("          早                      早   \t 早                      早   \n");
				gotoP(LENGTH / 2 - 40, 28 + i); printf("          早                      早   \t 早                      早   \n");
				gotoP(LENGTH / 2 - 40, 29 + i); printf("          曲收收收收收收收收收收收收收收收收收收收收收收旭   \t 曲收收收收收收收收收收收收收收收收收收收收收收旭   \n");
			}
			else if (firstLR == RIGHT_CHOSEN) {
				gotoP(LENGTH / 2 - 40, 14 + i); printf("          旨收收收收收收收收收收收收收收收收收收收收收收旬   \t 旨收收收收收收收收收收收收收收收收收收收收收收旬   \n");
				gotoP(LENGTH / 2 - 40, 15 + i); printf("          早                      早   \t 早                      早   \n");
				gotoP(LENGTH / 2 - 40, 16 + i); printf("          早                      早   \t 早                      早   \n");
				gotoP(LENGTH / 2 - 40, 17 + i); printf("          早                      早   \t 早                      早   \n");
				gotoP(LENGTH / 2 - 40, 18 + i); printf("          早  ####                早   \t 早    #                 早   \n");
				gotoP(LENGTH / 2 - 40, 19 + i); printf("          早 #    # #    # #####  早   \t 早   ##    ####  #####  早   \n");
				gotoP(LENGTH / 2 - 40, 20 + i); printf("          早      # ##   # #    # 早   \t 早  # #   #        #    早   \n");
				gotoP(LENGTH / 2 - 40, 21 + i); printf("          早  ####  # #  # #    # 早   \t 早    #    ####    #    早   \n");
				gotoP(LENGTH / 2 - 40, 22 + i); printf("          早 #      #  # # #    # 早   \t 早    #        #   #    早   \n");
				gotoP(LENGTH / 2 - 40, 23 + i); printf("          早 #      #   ## #    # 早   \t 早    #   #    #   #    早   \n");
				gotoP(LENGTH / 2 - 40, 24 + i); printf("          早 ###### #    # #####  早   \t 早  #####  ####    #    早   \n");
				gotoP(LENGTH / 2 - 40, 25 + i); printf("          早                      早   \t 早                      早   \n");
				gotoP(LENGTH / 2 - 40, 26 + i); printf("          早                      早   \t 早                      早   \n");
				gotoP(LENGTH / 2 - 40, 27 + i); printf("          早                      早   \t 早                      早   \n");
				gotoP(LENGTH / 2 - 40, 28 + i); printf("          早                      早   \t 早                      早   \n");
				gotoP(LENGTH / 2 - 40, 29 + i); printf("          曲收收收收收收收收收收收收收收收收收收收收收收旭   \t 曲收收收收收收收收收收收收收收收收收收收收收收旭   \n");
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
			if (select == LEFT) { // 豭薹 寞щ酈

				LR = LEFT_CHOSEN;

				gotoP(LENGTH / 2 - 40, 31 + i); printf("                      ∼             \t                           \n");
				gotoP(LENGTH / 2 - 40, 32 + i); printf("                     ∼∼             \t                           \n");
				gotoP(LENGTH / 2 - 40, 33 + i); printf("                    ∼∼∼             \t                           \n");

				//gotoP(LENGTH / 2 - 40, 36 + i); printf("                 寞щ酈煎 摹鷗 �� Enter 傳朝 Space酈蒂 援腦撮蹂.         \n");
			}
			else if (select == RIGHT) { // 螃艇薹 寞щ酈

				LR = RIGHT_CHOSEN;

				gotoP(LENGTH / 2 - 40, 31 + i); printf("                                     \t             ∼            \n");
				gotoP(LENGTH / 2 - 40, 32 + i); printf("                                     \t            ∼∼            \n");
				gotoP(LENGTH / 2 - 40, 33 + i); printf("                                     \t           ∼∼∼            \n");

				//gotoP(LENGTH / 2 - 40, 36 + i); printf("                 寞щ酈煎 摹鷗 �� Enter 傳朝 Space酈蒂 援腦撮蹂.         \n");
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
	gotoP(LENGTH / 2 - 6, 30); printf("  啪歜 衛濛  ");
	gotoP(LENGTH / 2 - 6, 33); printf("  啪歜 謙猿  ");
	resetColor();

	gotoP(LENGTH / 2 - 9, 30); printf("Ⅱ");
	gotoP(LENGTH / 2 - 9, 33); printf("  ");

	int chosen = TRUE;

	while (TRUE) {
		select = getch();
		if (select == ENTER || select == ' ') {
			if (chosen == TRUE) {
				MAX_QUEUE_SIZE = showLevel();
				TURN = showOrder();
				// 啪歜 霞ч
				return;
			}
			else if (chosen == FALSE)
				exit(0);
		}
		if (select == 0 || select == 0xe0) {
			select = getch();
			if (select == UP) { // 嬪薹 寞щ酈
				chosen = TRUE;
				gotoP(LENGTH / 2 - 9, 30); printf("Ⅱ");
				gotoP(LENGTH / 2 - 9, 33); printf("  ");
				gotoP(LENGTH, 50);
			}
			else if (select == DOWN) { // 嬴楚薹 寞щ酈
				chosen = FALSE;
				gotoP(LENGTH / 2 - 9, 30); printf("  ");
				gotoP(LENGTH / 2 - 9, 33); printf("Ⅱ");
				gotoP(LENGTH, 50);
			}
		}
	}
}

void SetCursorInvisible() {	// 醴憮蒂 癱貲ж啪 虜萄朝 л熱
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
	if (b->revealed == TRUE)	printf("   Ｙ   ");	// 奢偃脹 綰楣
	else						printf("        ");
	gotoP(x, y + 4);
	if (b->get_turn == TURN_num)printf("   Ⅸ   ");	// 檜廓欐縑 drawи 綰楣					// 檜剪 薯渠煎 轎溘 寰脾!!!
	else						printf("        ");
	resetColor();
}

void printHand(Block* head) {

	int row;
	if (head == &p_Block) {			// USER ぬ 轎溘
		row = 40;
		gotoP(LENGTH / 2 - 5, row);	printf("PLAYER HAND");
	}
	else if (head == &c_Block) {	// COM ぬ 轎溘
		row = 3;
		gotoP(LENGTH / 2 - 5, row);	printf("COMPUTER HAND");
	}
	else {
		printf("printHandл熱 螃盟");
	}

	// ぬ曖 綰楣 偎熱 count
	int count = 0;
	for (Block* b = head->rlink; b != head; b = b->rlink) {
		count++;
	}
	// 陛遴等 薑溺.
	int x = LENGTH / 2 - (BLOCK_WIDTH + 2) * (count / 2);		// и綰楣 й渡觼晦: (BLOCK_WIDTH + 2), 棺溥撿ж釭? 嬴葆 棺溥撿й蛭.
	int y = 3 + row;
	for (Block *b = head->rlink; b != head; b = b->rlink) {
		if(head==&p_Block||b->revealed==1)	// USER曖 綰楣 or COM曖 奢偃脹 綰楣
			printBlock(b, x, y);
		else {	// COM曖 綠奢偃 綰楣
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
			if (select == RIGHT && index < count) { // 螃艇薹 寞щ酈 && 螃艇薹部
				whereJoker_unbar(x + (BLOCK_WIDTH + 2)*index, 3 + row);	// 瞪縑疏 雖辦堅
				index++;
				whereJoker_bar(x + (BLOCK_WIDTH + 2)*index, 3 + row);		// 億剪 噥辦堅
			}
			else if (select == LEFT && index > 0) { // 豭薹 寞щ酈 && 豭薹部
				whereJoker_unbar(x + (BLOCK_WIDTH + 2)*index, 3 + row);
				index--;
				whereJoker_bar(x + (BLOCK_WIDTH + 2)*index, 3 + row);
			}
		}
		else if (select == ENTER || select == ' ') {
			whereJoker_unbar(x + (BLOCK_WIDTH + 2)*index, 3 + row); // 瞪縑疏 雖辦堅
			return index;
		}
	}

	printf("selectHandл熱 螃盟_2\n");
	return NULL;	// 螃盟嫦儅.
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
			if (select == RIGHT && index < count) { // 螃艇薹 寞щ酈 && 螃艇薹部
				whereJoker_unbar(x + (BLOCK_WIDTH + 2)*index, 3 + row);   // 瞪縑疏 雖辦堅
				index++;
				whereJoker_bar(x + (BLOCK_WIDTH + 2)*index, 3 + row);      // 億剪 噥辦堅
			}
			else if (select == LEFT && index > 0) { // 豭薹 寞щ酈 && 豭薹部
				whereJoker_unbar(x + (BLOCK_WIDTH + 2)*index, 3 + row);
				index--;
				whereJoker_bar(x + (BLOCK_WIDTH + 2)*index, 3 + row);
			}
		}
		else if (select == ENTER || select == ' ') {
			whereJoker_unbar(x + (BLOCK_WIDTH + 2)*index, 3 + row); // 瞪縑疏 雖辦堅
			return index;
		}
	}
}
void whereJoker_bar(int x, int y) {
	setColor(9,9);
	for (int i = -1; i < 6; i++) {
		gotoP(x - 1 - 1, y +i);	printf("早");
	}
	resetColor();
}
void whereJoker_unbar(int x, int y) {
	for (int i = -1; i < 6; i++) {
		gotoP(x - 1 - 1, y +i);	printf(" ");
	}
}

void BlockBoxing(int x, int y) {
	gotoP(x - 1-1, y - 1);	printf("旨收收收收收收收收收旬");
	// ⊿檜溢啪ж賊 陛遴等 竣橫噥錶雖棲梱
	//gotoP(x - 1, y + 0);	printf("#       #");
	//gotoP(x - 1, y + 1);	printf("#       #");
	//gotoP(x - 1, y + 2);	printf("#       #");
	//gotoP(x - 1, y + 3);	printf("#       #");
	//gotoP(x - 1, y + 4);	printf("#       #");
	// ⊿檜溢啪 и棻
	for (int i = 0; i < 5; i++) {
		gotoP(x - 1-1, y + i);	printf("早");
		gotoP(x + BLOCK_WIDTH, y + i);	printf("早");
	}
	gotoP(x - 1-1, y + 5);	printf("曲收收收收收收收收收旭");
}
void BlockUnboxing(int x, int y) {
	gotoP(x - 1-1, y - 1);	printf("           ");
	for (int i = 0; i < 5; i++) {
		gotoP(x - 1-1, y + i);	printf(" ");
		gotoP(x + BLOCK_WIDTH, y + i);	printf(" ");
	}
	gotoP(x - 1-1, y + 5);	printf("           ");
}

Block* selectBlock(Block*head) {	// output: 摹鷓 綰楣 index
	int row;
	if (head == &p_Block) {			// USER ぬ 轎溘
		row = 40;
	}
	else if (head == &c_Block) {	// COM ぬ 轎溘
		row = 3;
	}
	else {
		printf("selectHandл熱 螃盟");
	}

	// ぬ曖 綰楣 偎熱 count
	int count = dll_count(head);

	int x = LENGTH / 2 - (BLOCK_WIDTH + 2) * (count / 2);

	int index = 0;
	int select;

	BlockBoxing(x + (BLOCK_WIDTH + 2)*index, 3 + row);
	while (TRUE) {
		select = getch();

		
		if (select == 0 || select == 0xe0) {
			select = getch();
			if (select == RIGHT && index < count - 1) { // 螃艇薹 寞щ酈 && 螃艇薹部綰楣 嬴棍陽
				BlockUnboxing(x + (BLOCK_WIDTH + 2)*index, 3 + row);	// 瞪縑疏 雖辦堅
				index++;
				BlockBoxing(x + (BLOCK_WIDTH + 2)*index, 3 + row);		// 億剪 噥辦堅
			}
			else if (select == LEFT && index > 0) { // 豭薹 寞щ酈 && 豭薹部綰楣 嬴棍陽
				BlockUnboxing(x + (BLOCK_WIDTH + 2)*index, 3 + row);
				index--;
				BlockBoxing(x + (BLOCK_WIDTH + 2)*index, 3 + row);
			}
		}
		else if (select == ENTER || select == ' ') {
			//BlockUnboxing(x + (BLOCK_WIDTH + 2)*index, 3 + row); // 瞪縑疏 雖辦堅
			break;
		}
	}
	

	int find = 0;
	for (Block* b = head->rlink; b != head; b = b->rlink, find++) {
		if (find == index) {
			gotoP(LENGTH / 2 - 10, 13);
			printf("block[%d] 綰楣摹鷗 諫猿", index);	// 罹晦梱雖 諫猿�蝝臏� 憲晦嬪п 轎溘
			return b;
		}	
	}

	printf("selectHandл熱 螃盟_2\n");
	return NULL;	// 螃盟嫦儅.
}

int choose_guessNumber() {
	int count = dll_count(&p_Block);
	//BlockBoxing(LENGTH / 2 - (BLOCK_WIDTH + 2) * (count / 2) + (BLOCK_WIDTH + 2)*block_index, 3 + 3);	// 橫蛤綰楣 摹鷗醞檣雖 耀瞰ж啪 ル衛.


	int choice = 0;

	gotoP(LENGTH / 2 - 20, 20);
	setColor(0,15);
	printf("0");	// 籀擠 熱朝 ж曄儀戲煎 轎溘. 籀擠 enter援腦賊 檜剪 摹鷗腎棲梱.
	resetColor();
	printf("  1  2  3  4  5  6  7  8  9  10  11  J");
	
	int select;
	//int select = getch();

	while (TRUE) {
		select = getch();
		if (select == 0 || select == 0xe0) {
			select = getch();
			if (select == RIGHT && choice < 12) {		// 螃艇薹 寞щ酈 && 螃艇薹部
				choice++;
			}
			else if (select == LEFT && choice > 0) {	// 豭薹 寞щ酈 && 豭薹部
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

