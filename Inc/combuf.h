#ifndef INC_COMBUF_H_
#define INC_COMBUF_H_

#define COMBUF_SIZE  (20+1)

typedef struct{
	char buffer[COMBUF_SIZE];
	int top;
}combuf_t;
#endif

void combuf_flush(combuf_t * combuf);
void combuf_init(combuf_t * combuf);
int combuf_is_full(combuf_t * combuf);
int combuf_put(combuf_t * combuf, char c);
char* combuf_read(combuf_t * combuf);
