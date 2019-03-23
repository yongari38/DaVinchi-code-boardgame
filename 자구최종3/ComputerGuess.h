extern int user_reliability;
// 게임 새로시작할 때 user_reliability는 초기화하지 않고 그대로 갖고간다

extern int LEAST_SCORE_TO_GUESS;                  // guess 한번 더 하기위한 최소 가중치
extern int known_block[26];                  // 알려지지 않은 블럭
													 // 0: 알려짐, 1: 알려지지 않다.
													 // ㄴ 각 칸은 {0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,J,J}에 해당한다.

													 //int USER_guess[13][13] = { { -1,-1 }, };         // USER이 한 guess 기록, 신뢰도때문에 저장해놓는거임
													 // [guess_turn][그 턴에 guess한 수들]
													 // 이렇게 하지 말고 원형 큐로 선언하자.
													 //   -> 유저가 과거에 한 guess를 저장해야 하므로 FIFO가 적합

typedef struct {
	int guess_turn;
	int guess_number;         // 한턴에 3개를 guess했다면 각각 노드 생성
} element;

typedef struct {
	element * queue;
	int front, rear;
} QueueType;

extern QueueType USER_guess;

void init(QueueType *q);
void enqueue(QueueType *q, element item);

//=====================원형 큐 끝==============================//

void add_to_known(Block* b);
void insert_USER_guess(int guess_num);
void weight_init(Block * OpponentBlock_head);
void weight_add(Block* OpponentBlock_head);
int * weight_getMax(Block* OpponentBlock_head);
void after_guess(Block* OpponentBlock_head, int guess[2]);
int* guess(Block* OpponentBlock_head);
void init_score(Block* b, Block* OpponentBlock_head);
void did_USER_lie(Block* revealed);