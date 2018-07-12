#ifndef calc_h__
#define calc_h__

#define STRING_LEN 128
enum 
{
	ADD = 1,
	SUB,
	MUT,
	DIV,
	SIN,
	COS,
	TAN,
	ATAN,
	ABS,
	INTE,
	SIGN,
	SQRT,
	EXP,
	NEG,
	POS,
};
typedef struct  _STACK
{
	double buff[STRING_LEN];
	int top;
}STACK;
typedef	struct _OP_STACK
{
	char buff[STRING_LEN];
	int top;
}OP_STACK;

int transfer(OP_STACK *op,STACK *e,char *buf);

int compute(OP_STACK *op,STACK *e);

#endif // calc_h__
