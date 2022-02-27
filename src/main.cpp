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
	printf(".   sin     正弦            .\n");
	printf(".   cos     余弦            .\n");
	printf(".   tan     正切            .\n");
	printf(".   atan    反正弦          .\n");
	printf(".   sqrt    开方            .\n");
	printf(".   abs     取绝对值        .\n");
	printf(".............................\n");
	while (buf[0]!='#')
	{
		memset(&e,0,sizeof(e));
		memset(&op,0,sizeof(op));
		gets(buf);
		if (0>transfer(&op,&e,buf))
		{
			printf("语法错误\n");
		}
		else
		{
			printf("%f\n",e.buff[--e.top]);
		}	
	}
	
	return 0;
}
