#include <stdio.h>


#include <string.h>
#include <ctype.h>
#include <math.h>

#include "calc.h"

int compute(OP_STACK *op,STACK *e)
{
	int i;
	for (i=0;i<op->top;i++)
	{
		switch(op->buff[i])
		{
		case '+':
			if (e->top-2>=0) // 有足够操作数
			{
				e->top--;
				e->buff[e->top-1] = e->buff[e->top] + e->buff[e->top-1];
			}
			else
			{
				return -1;
			}
			break;
		case '-':
			if (e->top-2>=0) // 有足够操作数
			{
				e->top--;
				e->buff[e->top-1] = e->buff[e->top-1] - e->buff[e->top];
			}
			else
			{
				return -1;
			}
			break;
		case '*':
			if (e->top-2>=0) // 有足够操作数
			{
				e->top--;
				e->buff[e->top-1] = e->buff[e->top-1] * e->buff[e->top];
			}
			else
			{
				return -1;
			}
			break;
		case '/':
			if (e->top-2>=0&&e->buff[e->top-1]!=0) // 有足够操作数
			{
				e->top--;
				e->buff[e->top-1] = e->buff[e->top-1] / e->buff[e->top];
			}
			else
			{
				return -1;
			}
			break;
		case SIN:
			if (e->top -1 >=0)
			{
				e->buff[e->top-1] = sin(e->buff[e->top-1]);
			}
			else
			{
				return -1;
			}
			break;
		case COS:
			if (e->top -1 >=0)
			{
				e->buff[e->top-1] = cos(e->buff[e->top-1]);
			}
			else
			{
				return -1;
			}
			break;	
		case TAN:
			if (e->top - 1 >= 0 && 0 != cos(e->buff[e->top-1]))
			{
				e->buff[e->top-1] = sin(e->buff[e->top-1]) / cos(e->buff[e->top-1]);
			}
			else
			{
				return -1;
			}
			break;
		case ATAN:
			if (e->top -1 >=0)
			{
				e->buff[e->top-1] = atan(e->buff[e->top-1]);
			}
			else
			{
				return -1;
			}
			break;
		case ABS:
			if (e->top -1 >=0)
			{
				e->buff[e->top-1] = fabs(e->buff[e->top-1]);
			}
			else
			{
				return -1;
			}
			break;
		case INTE:
		case SIGN:
		case SQRT:
			if (e->top -1 >=0 && e->buff[e->top-1] >= 0)
			{
				e->buff[e->top-1] = sqrt(e->buff[e->top-1]);
			}
			else
			{
				return -1;
			}
			break;
		case EXP:
		case NEG: // 负号
			e->buff[e->top-1] = -1 * e->buff[e->top-1];
			break;
		case POS: // 正号
			break;	
		default:
			return 1;
		}
	}
	memset(op,0,sizeof(OP_STACK));
	return 0;
}
int transfer(OP_STACK *op,STACK *e,char *buf)
{
	int len = strlen(buf);
	char ch;
	int i,j;
	double tem = 0;
	OP_STACK s;
	memset(&s,0,sizeof(OP_STACK));
	for (i= 0;i<len;i++)
	{
		ch = buf[i];
		switch(ch)
		{
		case '+':
		case '-':
			if (i == 0
				||	(!isdigit(buf[i-1]) && buf[i-1] != ')'))
			{
				if (buf[i] == '-')
				{
					s.buff[s.top++] = NEG;
				}
				else
				{
					s.buff[s.top++] = POS;
				}	
				break;
			}
			while (s.buff[s.top-1] != '+'
				&& s.buff[s.top-1] != '-'
				&& s.buff[s.top-1] != '('
				&& s.top-1 >= 0)
			{
				op->buff[op->top++] = s.buff[--s.top];
			}
			if (s.buff[s.top-1] == '+' || s.buff[s.top-1] == '-')
			{
				op->buff[op->top++] = s.buff[--s.top];
			}
			s.buff[s.top++] = ch;
			if (0 > compute(op,e))
			{
				return -1;
			}
			break;
		case '*':
		case '/':
			while (s.buff[s.top-1] != '+'
				&& s.buff[s.top-1] != '-'
				&& s.buff[s.top-1] != '('
				//				&& s.buff[s.top-1] != '*'
				//				&& s.buff[s.top-1] != '/'
				&& s.top-1 >= 0
				)
			{
				op->buff[op->top++] = s.buff[--s.top];
			}
			if (0 > compute(op,e))
			{
				return -1;
			}
			s.buff[s.top++] = ch;
			break;
		case '(':
			s.buff[s.top] = ch;
			s.top++;
			break;
		case ')':
			while (s.buff[s.top - 1] != '(')
			{
				op->buff[op->top++] = s.buff[--s.top];
			}
			s.top--;
			if (0 > compute(op,e))
			{
				return -1;
			}
			break;
		case 's':
		case 'S':
			if ( i + 2 < len
				&& (buf[i+1] == 'i'||buf[i+1] == 'I')
				&& (buf[i+2] == 'n'||buf[i+2] == 'N'))
			{
				s.buff[s.top++] = SIN;
				i+=2;
			}
			else if ( i +3 < len
				&& (buf[i+1] == 'i'||buf[i+1] == 'I')
				&& (buf[i+2] == 'g'||buf[i+2] == 'G')
				&& (buf[i+3] == 'n'||buf[i+3] == 'N'))
			{
				return -1;
			}
			else if ( i +3 < len
				&& (buf[i+1] == 'q'||buf[i+1] == 'Q')
				&& (buf[i+2] == 'r'||buf[i+2] == 'R')
				&& (buf[i+3] == 't'||buf[i+3] == 'T'))
			{
				s.buff[s.top++] = SQRT;
				i+=3;
			}
			else
			{
				return -1; // 表达式非法
			}
			break;
		case 'c':
		case 'C':
			if ( i + 2 < len
				&& (buf[i+1] == 'o'||buf[i+1] == 'O')
				&& (buf[i+2] == 's'||buf[i+2] == 'S'))
			{
				s.buff[s.top++] = COS;
				i+=2;	
			}
			else
			{
				return -1;
			}
			break;
		case 'a':
		case 'A':
			if ( i + 2 < len
				&& (buf[i+1] == 'b'||buf[i+1] == 'B')
				&& (buf[i+2] == 's'||buf[i+2] == 'S'))
			{
				s.buff[s.top++] = ABS;
				i+=2;
			}
			else if ( i +3 < len
				&& (buf[i+1] == 't'||buf[i+1] == 'T')
				&& (buf[i+2] == 'a'||buf[i+2] == 'A')
				&& (buf[i+3] == 'n'||buf[i+3] == 'N'))
			{
				s.buff[s.top++] = ATAN;
				i+=3;
			}
			else
			{
				return -1; // 表达式非法
			}
			break;
		case 't':
		case 'T':
			if ( i + 2 < len
				&& (buf[i+1] == 'a'||buf[i+1] == 'A')
				&& (buf[i+2] == 'n'||buf[i+2] == 'N'))
			{
				s.buff[s.top++] = TAN;
				i+=2;	
			}
			else
			{
				return -1;
			}
			break;	
		default:
			if (!isdigit(buf[i]))
			{
				return -1;
			}
			for (tem = 0;isdigit(buf[i]);i++) 
			{
				tem=tem*10 +(buf[i]-'0');
			}
			if (buf[i]=='.') // 小数部分转换
			{
				double deci;
				i++;
				for (;isdigit(buf[i]);i++)
				{
					;
				}
				for (deci =0,j=i-1;buf[j]!='.';j--)
				{
					deci=deci/10+buf[j]-'0';
				}
				deci/=10;
				tem += deci;
			}
			i--;
			e->buff[e->top++] = tem;
			break;
		}
	}
	if (i == len) // 最后计算
	{
		while (s.top-1 >= 0)
		{
			op->buff[op->top++] = s.buff[--s.top];
		}
	}
	if (0 > compute(op,e) || e->top !=1 ) // 没有计算完
	{
		return -1;
	}
	return 0;
}
