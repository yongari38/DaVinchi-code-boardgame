#ifndef __DAVINCI_CODE_H__
#define __DAVINCI_CODE_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define USER			1
#define COM				-1

#define TRUE			1
#define FALSE			0

#define BLACK			0      
#define WHITE			1
#define JOKER			12
#define BLOCK_LEN	    13
#define INIT_BLOCK		4			// 처음에 각 플레이어가 나눠가질 블록의 수

extern int MAX_QUEUE_SIZE;		// 난이도에 따라 크기 설정

extern int num_white;
extern int num_black;
extern int TURN;
extern int TURN_num;

typedef struct _block {            // 블럭 구조체 노드 정의(이중연결리스트)
	int color;                  // 블럭의 색 (0: BLACK, 1: WHITE)
	int number;                  // 블럭의 숫자 (0 ~ 11, 12(JOKER))
	int get_turn;               // 드로우된 턴
	int revealed;               // 블럭의 숫자 공개여부, 공개:1, 비공개:0
	struct _block * llink, *rlink;
	int score[26];               // 새 블럭 뽑았을때 해줘야.
								 // 처음 드로우 때는 score[24] = {50,}. 초기점수 50.(초기점수는 나중에 조정.)
								 // 각 칸에는 그 칸에 해당하는 블럭의 가중치값.
								 // USER이 draw한 블럭의 점수는 기존 블럭들의 점수의 평균                  
} Block;

typedef struct _deque {            // 블럭을 뽑아올 Deck을 위한 Deque 구조체
	Block * head, *tail;
} Deque;

extern Deque BlockDeck;   // 플레이어가 블럭을 뽑아올 블럭덱(Deck)
extern Block p_Block;   // USER가 소유하고 있는 블럭 head
extern Block c_Block;   // COM가 소유하고 있는 블럭 head

#endif

