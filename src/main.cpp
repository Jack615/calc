#include <stdio.h>

#include <string.h>
#include <ctype.h>
#include <math.h>

#include "calc.h"


int main()
{
	STACK e;
	OP_STACK op;
	char buf[STRING_LEN];
	printf(".............................\n");
	printf(".   sin     ����            .\n");
	printf(".   cos     ����            .\n");
	printf(".   tan     ����            .\n");
	printf(".   atan    ������          .\n");
	printf(".   sqrt    ����            .\n");
	printf(".   abs     ȡ����ֵ        .\n");
	printf(".............................\n");
	while (buf[0]!='#')
	{
		memset(&e,0,sizeof(e));
		memset(&op,0,sizeof(op));
		gets(buf);
		if (0>transfer(&op,&e,buf))
		{
			printf("�﷨����\n");
		}
		else
		{
			printf("%f\n",e.buff[--e.top]);
		}	
	}
	
	return 0;
}
