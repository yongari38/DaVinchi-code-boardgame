#include "DavinciCode.h"
/*
---------------
@덱(Deque) 함수
---------------
*/

void dq_init(Deque * pd) {   // 덱 초기화
	pd->head = NULL;
	pd->tail = NULL;
}
int dq_isEmpty(Deque * pd) {   // 덱이 비어있는지 여부
	return (pd->head == NULL);
}
int dq_isFrontEmpty(Deque * pd) {   // 덱의 앞쪽에는 검은 블럭을 넣음. 검은 블럭이 남아있는지 여부
	return (pd->head->color == WHITE);
}
int dq_isRearEmpty(Deque * pd) {   // 덱의 뒤쪽에는 흰 블럭을 넣음. 흰 블럭이 남아있는지 여부
	return (pd->tail->color == BLACK);
}
void dq_addFront(Deque * pd, Block * newBlock) {   // 덱의 앞쪽에 노드 추가
	if (dq_isEmpty(pd))
		pd->tail = newBlock;
	else {
		pd->head->llink = newBlock;
		newBlock->rlink = pd->head;
	}
	pd->head = newBlock;
}
void dq_addRear(Deque * pd, Block * newBlock) {   // 덱의 뒤쪽에 블럭노드 추가
	if (dq_isEmpty(pd))
		pd->head = newBlock;
	else {
		pd->tail->rlink = newBlock;
		newBlock->llink = pd->tail;
	}
	pd->tail = newBlock;
}
Block * dq_deleteFront(Deque * pd) { // 덱의 맨 앞 BlockNode를 메모리해제하지 "않고" 반환
	Block * removedNode = NULL;

	if (dq_isEmpty(pd)) {
		printf("블럭이 모두 소진되었습니다. 게임을 종료합니다.\n");
		exit(1);
	}

	if (dq_isFrontEmpty(pd)) {
		printf("더 이상 검정 블럭이 없습니다. 흰 블럭을 선택해주세요.\n");      // 검정 블럭 모두 소진
		return NULL;
	}

	else {
		removedNode = pd->head;
		pd->head = pd->head->rlink;

		if (pd->head == NULL)
			pd->tail = NULL;
		else
			pd->head->llink = NULL;
	}
	num_black--;
	return removedNode;
}
Block * dq_deleteRear(Deque * pd) {   // 덱의 맨 끝 BlockNode를 메모리해제하지 "않고" 반환
	Block * removedNode = NULL;

	if (dq_isEmpty(pd)) {
		printf("블럭이 모두 소진되었습니다. 게임을 종료합니다.\n");
		exit(1);
	}

	if (dq_isRearEmpty(pd)) {
		printf("더 이상 흰 블럭이 없습니다. 검정 블럭을 선택해주세요.\n");      // 흰 블럭 모두 소진
		return NULL;
	}

	else {
		removedNode = pd->tail;
		pd->tail = pd->tail->llink;

		if (pd->tail == NULL)
			pd->head = NULL;
		else
			pd->tail->rlink = NULL;
	}
	num_white--;
	return removedNode;
}
void dq_display(Deque * pd) { // 덱의 내용 출력
	Block * p;
	for (p = pd->head; p != NULL; p = p->rlink) {
		printf("(%d: %d), ", p->color, p->color);
	}
	printf("\n");
}