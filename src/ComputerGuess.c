#include "DavinciCode.h"
#include "ComputerGuess.h"

int user_reliability = 60;
int LEAST_SCORE_TO_GUESS = 100;
int known_block[26] = { 1, };
QueueType USER_guess;

void init(QueueType *q) {      // 초기화 함수
	q->front = 0;
	q->rear = 0;
	q->queue = (element*)malloc(sizeof(element) * MAX_QUEUE_SIZE);
	element dummy = { -1,-1 };
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
		q->queue[i] = dummy;   // 다 쓰레기값 넣어준다
	}
}

void enqueue(QueueType *q, element item) {   // 삽입 함수
											 // is_full인지 검사할필요가 없다. 어차피 꽉찼으면 덮어쓰기할꺼니까
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

//=====================원형 큐 끝==============================//


void add_to_known(Block* b) {                  // COM이 draw하거나 USER의 패가 공개됬을 때 호출
											   // 공개된 카드들은 1, 아닌건 0
	known_block[2 * b->number + b->color] = 1;
}
void insert_USER_guess(int guess_num) {      // 새로운 guess을 큐에 삽입
											 // input: USER가 guess한 number
	element guess;
	guess.guess_turn = TURN;
	guess.guess_number = guess_num;

	enqueue(&USER_guess, guess);
}

void weight_init(Block * head) {      // input: 상대방(USER)의 블럭 head

	for (Block* b = head->rlink; b != head; b = b->rlink) {
		if (b->revealed == TRUE) {			// 공개 상태 블럭의 가중치 모두 0
			for (int i = 0; i < 26; i++)
				b->score[i] = 0;
		}
		else if (b->revealed == FALSE) {      // 블럭이 비공개 상태면~
			for (int i = 0; i < 26; i++)      // 그 블럭의 가중치배열의 이미 알려진 놈들의 가중치를 0으로 만들어준다
				if (known_block[i] == TRUE)
					b->score[i] = 0;

			// 다른 색깔 경우의 수 0으로 만들어주기
			if (b->color == BLACK) {      // 홀수 0 만들어주기
				for (int i = 1; i < 26; i += 2)
					b->score[i] = 0;
			}
			else {
				for (int i = 0; i < 26; i += 2)      // 짝수 0 만들어주기
					b->score[i] = 0;
			}
		}
	}
	// 이제 USER 패의 공개된 블럭들을 기준으로 불가능한 경우의 수의 가중치를 0으로 만들어준다.
	for (Block* b = head->rlink; b != head; b = b->rlink)
	{
		// b가 공개된 블럭이라면 && 조커가 아니라면
		if (b->revealed == TRUE && b->number != 12)
		{
			// 앞에있는 블럭들의 가중치값 정리
			for (Block* front = head->rlink; front != b; front = front->rlink)
				// b 앞의 '자신보다 큰 경우의 수' 가중치 0만들기
				for (int i = 2 * b->number + b->color; i < 24; i++)   // i=24,25은 조커자리이므로 건드리지 않습니다
					front->score[i] = 0;

			// 뒤에있는 블럭들의 가중치값 정리
			for (Block* back = b->rlink; back != head; back = back->rlink)
				// b 뒤의 '자신보다 작은 경우의 수' 가중치 0만들기
				for (int i = 0; i <= 2 * b->number + b->color; i++)
					back->score[i] = 0;
		}
	}
}
void weight_add(Block* OpponentBlock_head) {

	// 공개 상태의 블럭 current_block, current_block2 사이의 count개의 블럭들의 가중치 더해줘
	for (Block* current_block = OpponentBlock_head->rlink; current_block != OpponentBlock_head; current_block = current_block->rlink)
	{
		if (current_block->revealed == FALSE)
		{
			int count = 0;
			for (int i = 0; i < 26; i++)
				if (current_block->score[i] != 0) count++;      // final candidatesd들이 가중치를 나눠갖도록 하려면 우선 몇개인지 알아야

			for (int i = 0; i < 26; i++)
				if (current_block->score[i] != 0)            // 가중치가 0이 아니면~
				{
					int is_it_recent_guess = 0;      // 1: 방금 turn USER의 guess이다.
													 // 0: 아니다.

					int index = USER_guess.rear;
					do {
						if (USER_guess.queue[index].guess_number == current_block->number) {
							is_it_recent_guess = 1;
						}
						index--;
					} while (USER_guess.queue[index].guess_turn == USER_guess.queue[USER_guess.rear].guess_turn);
					// 방금전 턴 guess 전부 검사
					if (is_it_recent_guess)         // USER가 방금 guess한 number면
						current_block->score[i] += (100 - user_reliability) / count;
					else                     // 아니면
						current_block->score[i] += (user_reliability) / count;

				}
		}
	}
}

int* weight_getMax(Block* OpponentBlock_head) {      // 가중치가 가장 큰 guess 를 찾고 리턴

	int * output = (int *)malloc(sizeof(int) * 3);                  // [position][guess_number][score]
	output[0] = output[1] = output[2] = -1;

	int index_of_max = 0;
	for (Block* current_block = OpponentBlock_head->rlink; current_block != OpponentBlock_head; current_block = current_block->rlink) {
		for (int i = 0; i < 26; i++) {
			if (current_block->score[i] > output[2]) {
				output[0] = index_of_max;
				output[1] = i;
				output[2] = current_block->score[i];
			}
		}
		index_of_max++;
	}
	return output;
}


void after_guess(Block* OpponentBlock_head, int guess[2]) {         // guess를 했으니 그 블럭에서 그 경우의 수를 없애주는 함수
																	// input: p_head, [index_of_max][guess_number(0~25)]
	Block* block_of_guess;
	int i = 0;
	for (block_of_guess = OpponentBlock_head->rlink; i < guess[0]; i++)
		block_of_guess = block_of_guess->rlink;

	block_of_guess->score[guess[1]] = 0;
}

int* guess(Block* OpponentBlock_head) {            // COM의 차례에 드로우 이후 호출
												   // input: 상대방의 블럭 head

	weight_init(OpponentBlock_head);                  // initial candidates
	weight_add(OpponentBlock_head);               // reliability를 고려한 가중치를 더해주는 함수
												  // int max[3] = guess_getMax(OpponentBlock_head);   // [position][guess_number][score]
	int* max;                              // [position][guess_number][score]
	max = weight_getMax(OpponentBlock_head);
	int guess1[2] = { max[0] ,max[1] };            // [position][guess_number]
	after_guess(OpponentBlock_head, guess1);      // guess를 했으니 그 블럭에서 그 경우의 수를 없애주는 함수

												  // 계속해서 guess 할지 결정
	int * result = (int*)malloc(sizeof(int) * 3);
	result[0] = max[0];
	result[1] = max[1];
	result[2] = 0;                            // [position][guess_number][repeat?]

	weight_init(OpponentBlock_head);
	weight_add(OpponentBlock_head);

	int* max2;                              // [position][guess_number][score]
	max2 = weight_getMax(OpponentBlock_head);

	LEAST_SCORE_TO_GUESS = max[2]+20;
	if (max2[2] >= LEAST_SCORE_TO_GUESS)         // 그 다음 큰 가중치값도 LEAST_SCORE_TO_GUESS 이상일 경우만
		result[2] = 1;  

	return result;
}

void init_score(Block* b, Block* OpponentBlock_head) {   // USER가 새로운 블록을 뽑았을 때 호출
													// input: 새로 뽑은 블럭
													// USER이 draw한 블럭의 점수는 기존 블럭들의 점수의 평균
	int score = 0;
	int count = 0;
	for (Block* current_block = OpponentBlock_head->rlink; current_block != OpponentBlock_head; current_block = current_block->rlink) {
		for (int i = 0; i < 26; i++) {
			if (current_block->score[i] != 0) {
				score += current_block->score[i];
				count++;
			}
		}
	}
	for (int i = 0; i < 26; i++)
		b->score[i] = score / count;               // int여서 소숫점 씹히겠지만 그정도는 괜찮겟지?
	b->get_turn = TURN_num;
}

void did_USER_lie(Block* revealed) {            // COM이 USER의 패를 맞춰서 앞면이 보일 때 호출해서 검사
												// USER이 guess했는데 틀려서 그 턴에 드로우한 블럭이 공개됬을 때도 호출????
												// input: 이번에 맞춰서 공개된 블럭
	int index = USER_guess.rear;
	do {
		if (USER_guess.queue[index].guess_number == revealed->number) {      // 만약 공개된 블럭의 number가 USER이 guess한 number중에 있다면
			if (revealed->get_turn <= USER_guess.queue[index].guess_turn)   // 만약 공개된 블럭을 드로우한 이후에 guess를 한거라면
				user_reliability--;                                 // 어느정도 더하고 뺄지는 조정.
			else
				user_reliability++;
		}
		index--;
	} while (USER_guess.queue[index].guess_turn != USER_guess.queue[USER_guess.rear].guess_turn);
	// 방금전 턴 guess 전부 검사
	// 만약 공개된 블럭의 number가 USER이 guess한 number중에 없다면, 아무것도 안함
}