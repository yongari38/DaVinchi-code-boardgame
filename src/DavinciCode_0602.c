#define _CRT_SECURE_NO_WARNINGS

#include "DavinciCode.h"
#include "DoubleLinkedList.h"
#include "DoubleEndedQueue.h"
#include "ComputerGuess.h"
#include "gameUI.h"

Deque BlockDeck;   // 플레이어가 블럭을 뽑아올 블럭덱(Deck)
Block p_Block;   // USER가 소유하고 있는 블럭 head
Block c_Block;   // COM가 소유하고 있는 블럭 head

int num_white = BLOCK_LEN;
int num_black = BLOCK_LEN;
int TURN = COM;
int TURN_num = 0;

/*
-------------------
@게임 진행 관련 함수
-------------------
*/

void makeArrayRandom(int * arr) {   // 매개변수로 전달받은 배열의 순서를 랜덤하게 만드는 함수
	int len = BLOCK_LEN;
	int rs[BLOCK_LEN];
	int n = 0;

	while (len != 0) {
		int idx = rand() % len;
		rs[n++] = arr[idx];

		for (int i = idx; i < len - 1; i++)
			arr[i] = arr[i + 1];

		len--;
	}

	for (int i = 0; i < BLOCK_LEN; i++) {
		arr[i] = rs[i];
	}
}
void initDeck() {   // BlockDeck을 초기화
	int arr[BLOCK_LEN] = { 0,1,2,3,4,5,6,7,8,9,10,11,JOKER };

	for (int j = 0; j <= WHITE; j++) {
		makeArrayRandom(arr);

		for (int i = 0; i < BLOCK_LEN; i++) {
			//printf("%d ", arr[i]);
			Block * bnode = (Block*)malloc(sizeof(Block));
			bnode->revealed = FALSE;
			bnode->color = j;
			bnode->number = arr[i];
			bnode->rlink = NULL;
			bnode->llink = NULL;

			for (int k = 0; k < 26; k++)
				bnode->score[k] = 50;

			if (j == 0)
				dq_addFront(&BlockDeck, bnode);
			else
				dq_addRear(&BlockDeck, bnode);
		}
		printf("\n");
	}
}

void InsertAndSort(Block * PlayerBlock, Block * newBlock, int Player) {   // newBlock을 PlayerBlock리스트의 적절한 위치에 삽입
	Block * before;
	int n = -1; // JOKER가 있는 경우 넣을 위치 선택 변수
	int count;
	int x = LENGTH / 2 - (BLOCK_WIDTH / 2);
	int row = 17;

	if (Player == COM)
		add_to_known(newBlock);

	if (newBlock->number == JOKER) { // 넣으려는 블럭이 조커인 경우
		Block * p = PlayerBlock;
		int i = 0;

		if (Player == USER) {
			gotoP(50, 18);   printf("조커를 삽입할 위치를 고르세요");
			n = whereJoker(&p_Block);
		}
		else if (Player == COM) { // Computer의 경우
			for (p = PlayerBlock->rlink; p != PlayerBlock; p = p->rlink, i++);
			n = rand() % (i + 1);
		}

		p = PlayerBlock;
		for (i = 0; i < n; i++) {
			p = p->rlink;
		}

		before = p;
	}

	else {   // 넣으려는 블록이 조커가 아닌 경우

		n = -1; // JOKER가 있는 경우 넣을 위치 선택 변수 초기화
		before = dll_find_index(PlayerBlock, newBlock);      // 삽입할 위치 앞 노드
															 //printf("<%d>", before->block.number);
		clearChat();
		if (before->number == JOKER && before->rlink->number == JOKER) {  // 조커가 연달아 2개 있는 경우

			count = 2;

			if (Player == USER) {

				gotoP(x - 15, row);
				printf("방금 뽑은 블럭을 어디에 넣으시겠습니까?\n");
				printBlock(newBlock, x, row + 2);

				printBlock(before, x, row + 12);
				printBlock(before->rlink, x + 10, row + 11);
				n = whereWithJoker(count, x, row + 8);
			}
			else if (Player == COM) {
				n = rand() % 3;
			}
		}
		else if (before->number == JOKER) {      // 삽입할 위치 앞에 JOKER가 1개 있는 경우

			count = 1;

			if (Player == USER) {

				gotoP(x - 15, row);
				printf("방금 뽑은 블럭을 어디에 넣으시겠습니까?\n");
				printBlock(newBlock, x, row + 2);

				printBlock(before, x, row + 11);
				n = whereWithJoker(count, x, row + 8);
			}
			else if (Player == COM) {
				n = rand() % 2;
			}
		}

		if (n == 0) {
			before = before->llink;
		}
		else if (n == 2) {
			before = before->rlink;
		}
	}
	dll_insert(before, newBlock);
}

Block * choiceColor(Deque * pd) {   // 검정, 흰 블럭 선택 후 덱에서 블럭 반환하는 함수

	int color = BLACK;
	int select;

	Block * newBlock = NULL;

	if (dq_isEmpty(pd)) {
		printf("더 이상 뽑아올 블럭이 없습니다.");
		printf("무승부입니다.");
		exit(1);
	}
	else
	{
		//while (getchar() != '\n');

		int x = 58, y = 20;
		int i;

		setColor(10, 0);   gotoP(x - 1 - 1, y - 1);   printf("┏━━━━━━━━━┓");
		gotoP(x - 1 + BLOCK_WIDTH / 2 - 3, y + 1); printf("남은블럭");
		gotoP(x - 1 + BLOCK_WIDTH / 2, y + 3); printf("%d", num_black);
		setColor(15, 0);   gotoP(x - 1 - 1 + 16, y - 1);   printf("┏━━━━━━━━━┓");
		gotoP(x + 16 - 1 + BLOCK_WIDTH / 2 - 3, y + 1); printf("남은블럭");
		gotoP(x + 16 - 1 + BLOCK_WIDTH / 2, y + 3); printf("%d", num_white);

		// ↓이렇게하면 가운데 덮어씌워지니까
		//gotoP(x - 1, y + 0);   printf("#       #");
		//gotoP(x - 1, y + 1);   printf("#       #");
		//gotoP(x - 1, y + 2);   printf("#       #");
		//gotoP(x - 1, y + 3);   printf("#       #");
		//gotoP(x - 1, y + 4);   printf("#       #");
		// ↓이렇게 한다

		for (i = 0; i < 5; i++) {

			setColor(10, 0);
			gotoP(x - 1 - 1, y + i);   printf("┃");
			gotoP(x + BLOCK_WIDTH, y + i);   printf("┃");

			setColor(15, 0);
			gotoP(x - 1 - 1 + 16, y + i);   printf("┃");
			gotoP(x + BLOCK_WIDTH + 16, y + i);   printf("┃");
		}

		setColor(10, 0);   gotoP(x - 1 - 1, y + 5);   printf("┗━━━━━━━━━┛");
		setColor(15, 0);   gotoP(x - 1 - 1 + 16, y + 5);   printf("┗━━━━━━━━━┛");

		resetColor();

		gotoP(x - 1 - 1 + 4, y + 6); printf(" ▲ ");

		gotoP(x - 1 - 1 - 9, y + 10); printf("방향키로 선택 후 Enter 또는 Space키를 누르세요.\n");

		while (TRUE) {
			select = getch();
			if (select == ENTER || select == ' ')
				break;

			if (select == 0 || select == 0xe0) {
				select = getch();
				if (select == LEFT) { // 왼쪽 방향키

					color = BLACK;

					gotoP(x - 1 - 1 + 20, y + 6); printf("   ");
					gotoP(x - 1 - 1 + 4, y + 6); printf(" ▲");
				}
				else if (select == RIGHT) { // 오른쪽 방향키

					color = WHITE;

					gotoP(x - 1 - 1 + 4, y + 6); printf("   ");
					gotoP(x - 1 - 1 + 20, y + 6); printf(" ▲");
				}
			}
		}

		//getchar();

		//gotoP(40, 20);

		switch (color) {
		case BLACK:
			newBlock = dq_deleteFront(pd);
			if (newBlock == NULL) {
				color = -1;
				break;
			}
			/*if (newBlock->number == JOKER) {
			printf("뽑은 블럭 : 검은색 조커                                     \n");
			printf("                                                            ", newBlock->number);
			}
			else {
			printf("뽑은 블럭 : 검은색 %d                                      \n", newBlock->number);
			printf("                                                            ", newBlock->number);
			}*/

			break;
		case WHITE:
			newBlock = dq_deleteRear(pd);
			if (newBlock == NULL) {
				color = -1;
				break;
			}
			/*if (newBlock->number == JOKER){
			printf("뽑은 블럭 : 흰색 조커                                       \n");
			printf("                                                            ", newBlock->number);
			}
			else {
			printf("뽑은 블럭 : 흰색 %d                                        \n");
			printf("                                                            ", newBlock->number);
			}*/

			break;
		}

		gotoP(x - 1 - 1 - 9, y + 14);

	}
	return newBlock;
}
Block * choiceColor_COM(Deque * pd) {   // COM이 검정, 흰 블럭 선택 후 덱에서 블럭 반환하는 함수
	int color = -1;
	Block * newBlock = NULL;

	if (dq_isEmpty(&BlockDeck)) {
		printf("더 이상 뽑아올 블럭이 없습니다.");
		printf("무승부입니다.");
		exit(1);
	}
	else
	{
		while (color != BLACK && color != WHITE)
		{
			if (dq_isEmpty(pd))               // 덱이 비었을때
				printf("블럭이 모두 소진되었습니다. 게임을 종료합니다.\n");
			else if (dq_isFrontEmpty(pd))      // 검정이 비었을때
				color = WHITE;
			else if (dq_isRearEmpty(pd))      // 하양이 비었을 떄
				color = BLACK;
			else {
				Block* b;
				Block* tmp;
				tmp = &c_Block;

				int B_count = 0, W_count = 0;
				for (b = tmp->rlink; b != tmp; b = b->rlink) {
					if (b->color == BLACK)
						B_count++;
					else if (b->color == WHITE)
						W_count++;
				}
				// BLACK 많으면 WHITE 뽑고 WHITE 많으면 BLACK뽑는다
				// 같을땐 WHITE 뽑는다
				color = (B_count >= W_count ? WHITE : BLACK);
			}

			switch (color) {
			case BLACK:
				newBlock = dq_deleteFront(pd);
				if (newBlock == NULL) {
					color = -1;
					break;
				}
				break;
			case WHITE:
				newBlock = dq_deleteRear(pd);
				if (newBlock == NULL) {
					color = -1;
					break;
				}
				break;
			}
		}
	}
	return newBlock;
}



void currentDeck() {   // 현재 블럭 DECK에 남아있는 흰색, 검은색 블럭의 개수를 출력
	printf("\n%d개의 검은 블럭과 %d개의 흰 블럭이 남아있습니다.\n\n", num_black, num_white);
}
void showBlocks() {
	CLEAR();
	showEdge();
	showChat();

	printHand(&c_Block);
	printHand(&p_Block);
}

char replay = FALSE;	// 유저가 맞췄을 때 게임을 계속 진행할 지
char replay_COM = FALSE;// 컴퓨터가 맞췄을 때 게임을 계속 진행할 지 
Block * newBlock = NULL;

void play() {
	if (TURN == USER) {

		showBlocks();
		showChat();
		gotoP(LENGTH / 2 - 10, 13); printf("당신의 차례입니다.");
		if (replay == FALSE) {
			gotoP(LENGTH / 2 - 20, 16);  printf("새로운 블럭을 가져옵니다.");
			newBlock = choiceColor(&BlockDeck);
			TURN_num++;
			init_score(newBlock, &p_Block);
			InsertAndSort(&p_Block, newBlock, USER);
			printHand(&p_Block);

		}
		gotoP(LENGTH / 2 - 25, 16);  printf("                         ");	// "새로운 블럭을 가져옵니다." 지우기
		// 박싱 테스트 BlockBoxing(LENGTH / 2 - (BLOCK_WIDTH + 2) * (4 / 2), 3 + 3);


		Block * selected_Block;		// USER가 guess할 블럭
		int choiceNumber = -1;	// USER가 guess한 수


		do {
			clearChat();
			selected_Block = selectBlock(&c_Block);

			if (selected_Block->revealed == TRUE) {
				gotoP(LENGTH / 2 - 30, 18);  printf("이미 공개된 블럭입니다. 다른 블럭을 추측하세요.");
				gotoP(LENGTH / 2 - 30, 19);	printf("(계속하려면 엔터)");
				getchar();
			}
			else
				break;

		} while (TRUE);

		clearChat();
		choiceNumber = choose_guessNumber();

		insert_USER_guess(2 * choiceNumber + selected_Block->color);

		if (selected_Block->number == choiceNumber) {
			selected_Block->revealed = TRUE;
			add_to_known(selected_Block);
			while (TRUE) {
				clearChat();

				gotoP(LENGTH / 2 - 25, 16); printf("맞췄습니다. 계속하시겠습니까? [Y/N] : ");
				scanf("%c", &replay);
				while (getchar() != '\n');

				if (replay == 'N' || replay == 'n') {
					gotoP(LENGTH / 2 - 25, 18); printf("계속하지 않겠다고 결정.");
					replay = FALSE;
					TURN = COM;
					gotoP(LENGTH / 2 - 25, 20); printf("한 턴이 끝났습니다.(계속하려면 엔터)");
					getchar();
					return;
				}

				else if (replay == 'Y' || replay == 'y') {
					gotoP(LENGTH / 2 - 25, 18); printf("계속하겠다고 결정.");
					replay = TRUE;
					TURN = USER;
					gotoP(LENGTH / 2 - 25, 20); printf("(계속하려면 엔터)");
					getchar();
					return;
				}
			}
		}


		else {
			gotoP(LENGTH / 2 - 25, 16); printf("틀렸습니다. 이번 차례에 가져온 블럭을 공개합니다.");
			gotoP(LENGTH / 2 - 25, 17); printf("(계속하려면 엔터)");
			newBlock->revealed = TRUE;
			add_to_known(newBlock);
			did_USER_lie(newBlock);
			TURN = COM;
			replay = FALSE;
			getchar();
			return;
		}
	}

	else if (TURN == COM) {

		clearChat();
		showBlocks();
		gotoP(LENGTH / 2 - 10, 13); printf("컴퓨터의 차례입니다. ");


		if (replay_COM == FALSE) {      // 컴퓨터의 첫 차례인 경우 draw
			gotoP(LENGTH / 2 - 25, 20); printf("새로운 블럭을 가져옵니다.\n");
			// 컴퓨터가 draw하는 함수.
			newBlock = choiceColor_COM(&BlockDeck);
			newBlock->get_turn = ++TURN_num;
			InsertAndSort(&c_Block, newBlock, COM);
		}


		gotoP(LENGTH / 2 - 25, 18); printf("Computer is thinking");
		for (int i = 0; i < 6; i++) {
			if (i < 3) {
				printf(".");
				Sleep(200);
			}
			else {
				printf("\b \b");
				Sleep(200);
			}
		}
		printf("..DONE!");

		int *  rs = guess(&p_Block);

		//gotoP(LENGTH / 2 - 25, 20); printf("게스 결과: %d %d %d\n", rs[0], rs[1], rs[2]);

		int choicePosition = rs[0];
		int choiceNumber = rs[1] / 2;
		int computerWantsToGo = rs[2];

		Block * p = dll_getNodeAt(&p_Block, choicePosition);

		if (p->number == choiceNumber) {
			p->revealed = TRUE;
			gotoP(LENGTH / 2 - 25, 20); printf("컴퓨터가 당신의 %d번 블럭의 숫자를 맞췄습니다.", choicePosition);
			add_to_known(p);
			did_USER_lie(p);

			if (!computerWantsToGo) {
				gotoP(LENGTH / 2 - 25, 21); printf("컴퓨터가 차례를 당신에게 넘겼습니다.");
				gotoP(LENGTH / 2 - 25, 23); printf("한 턴이 끝났습니다.(계속하려면 엔터)");
				getchar();
				TURN = USER;
				replay_COM = FALSE;
			}

			else {
				gotoP(LENGTH / 2 - 25, 21); printf("컴퓨터가 계속 플레이 하겠다고 결정했습니다.");
				gotoP(LENGTH / 2 - 25, 23); printf("(계속하려면 엔터)");
				getchar();
				TURN = COM;
				replay_COM = TRUE;
			}
		}

		else {
			gotoP(LENGTH / 2 - 25, 20); printf("컴퓨터가 당신의 %d번 블럭이 \"%d\" 이라 예상했으나,", choicePosition, choiceNumber);
			gotoP(LENGTH / 2 - 25, 21); printf("틀렸습니다.", choicePosition, choiceNumber);
			gotoP(LENGTH / 2 - 25, 23); printf("한 턴이 끝났습니다.(계속하려면 엔터)");
			newBlock->revealed = TRUE;
			add_to_known(newBlock);
			getchar();
			TURN = USER;
			replay_COM = FALSE;
		}
	}
}
int isEndUser(Block * p_Block) {   // 게임이 끝났는지 판별
	Block * p;

	for (p = p_Block->rlink; p != p_Block; p = p->rlink) {
		if (p->revealed == FALSE)
			return FALSE;
	}
	return TRUE;
}
int isEndCom(Block * c_Block) {
	Block * p;
	for (p = c_Block->rlink; p != c_Block; p = p->rlink) {
		if (p->revealed == FALSE) {
			return FALSE;
		}
	}
	return TRUE;
}

int main() {
	//srand((int)time(NULL));
	srand(4);

	SetCursorInvisible();
	system("title Da Vinci Code");
	system("mode con: cols=140 lines=51");
	showEdge();
	showMain();
	init(&USER_guess);

	dq_init(&BlockDeck);
	initDeck();
	dll_init(&p_Block);
	dll_init(&c_Block);

	Sleep(2000);

	CLEAR();
	showEdge();
	showChat();

	for (int i = 0; i < INIT_BLOCK; i++) {   // 처음 패 나눠주기(COM)
		int n = rand() % 2;
		if (n == BLACK)
			InsertAndSort(&c_Block, dq_deleteFront(&BlockDeck), COM);
		else if (n == WHITE)
			InsertAndSort(&c_Block, dq_deleteRear(&BlockDeck), COM);
	}
	printHand(&c_Block);


	for (int i = 0; i < INIT_BLOCK; i++) {  // 처음 패 나눠주기(USER)
		clearChat();
		gotoP(LENGTH / 2 - 5, 14);	printf("초기 드로우");
		InsertAndSort(&p_Block, choiceColor(&BlockDeck), USER);
		printHand(&p_Block);
	}
	printHand(&c_Block);
	// 처음 패 나눠주기 완료

	while (!isEndUser(&p_Block) && !isEndCom(&c_Block)) {
		play();

		if (isEndUser(&p_Block) && isEndCom(&c_Block)) {
			setColor(0, 15);
			clearChat();
			gotoP(LENGTH / 2 - 25, 25);	printf("무승부입니다.");
			gotoP(LENGTH / 2 - 25, 26);
			PAUSE();
			getchar();
			exit(1);
		}
		else if (isEndUser(&p_Block)) {
			setColor(12, 15);
			clearChat();
			gotoP(LENGTH / 2 - 25, 25);	printf("컴퓨터가 승리하였습니다.");
			gotoP(LENGTH / 2 - 25, 26);
			PAUSE();
			getchar();
			exit(1);
		}
		else if (isEndCom(&c_Block)) {
			setColor(9, 15);
			clearChat();
			gotoP(LENGTH / 2 - 25, 25);	printf("당신이 승리하였습니다.");
			gotoP(LENGTH / 2 - 25, 26);
			PAUSE();
			getchar();
			exit(1);
		}

		if (dq_isEmpty(&BlockDeck)) {
			setColor(0, 15);
			clearChat();
			gotoP(LENGTH / 2 - 25, 25);  printf("더 이상 뽑아올 블럭이 없습니다.");
			gotoP(LENGTH / 2 - 25, 26);  printf("무승부입니다.");
			gotoP(LENGTH / 2 - 25, 27);
			exit(1);
		}
	}
	Sleep(5000);
}