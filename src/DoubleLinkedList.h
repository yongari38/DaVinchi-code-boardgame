void dll_init(Block * phead);
Block * dll_find_index(Block * head, Block * newBlock);
void dll_insert(Block * before, Block * newBlock);
void dll_display(Block * phead, int n);
int dll_count(Block * phead);
Block * dll_getNodeAt(Block * blocks, int pos);