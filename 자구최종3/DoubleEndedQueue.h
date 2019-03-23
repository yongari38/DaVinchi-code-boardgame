void dq_init(Deque * pd);
int dq_isEmpty(Deque * pd);
int dq_isFrontEmpty(Deque * pd);
int dq_isRearEmpty(Deque * pd);
void dq_addFront(Deque * pd, Block * newBlock);
void dq_addRear(Deque * pd, Block * newBlock);
Block * dq_deleteFront(Deque * pd);
Block * dq_deleteRear(Deque * pd);
void dq_display(Deque * pd);