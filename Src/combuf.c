#include "combuf.h"

void combuf_flush(combuf_t * combuf){
	combuf->buffer[0] = '\0';
	combuf->top = 0;
}

void combuf_init(combuf_t * combuf){
	combuf_flush(combuf);
}

int combuf_is_full(combuf_t * combuf){
	return combuf->top+1 >= COMBUF_SIZE;
}

int combuf_put(combuf_t * combuf, char c){
	if(combuf_is_full(combuf)){
		return 0;
	}
	combuf->buffer[combuf->top] = c;
	combuf->top++;
	combuf->buffer[combuf->top] = '\0';
	return 1;
}

int combuf_pop(combuf_t * combuf){
	if(combuf->top>0){
		combuf->top++;
		return 1;
	}
	return 0;
}

char* combuf_read(combuf_t * combuf){
	return combuf->buffer;
}
