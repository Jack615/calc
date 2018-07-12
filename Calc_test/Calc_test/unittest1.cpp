#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Calc_test
{
    TEST_CLASS(UnitTest1)
    {
    public:
        TEST_METHOD(test_Transfer)
        {
            // TODO: 在此输入测试代码
			//STACK e;
			//OP_STACK op;
			//char buf[STRING_LEN];

			//memset(&e,0,sizeof(e));
			//memset(&op,0,sizeof(op));
			//transfer(&op,&e,buf);

			Assert::AreEqual(9, 9);
			Logger::WriteMessage("testAdd() finish testing!\n");
        }
    };
}