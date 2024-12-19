#include "pch.h"
#include "CppUnitTest.h"
#include "../main-project/internet_protocol.h"
#include "../main-project/processing.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittestproject
{

    internet_protocol build_protocol(int start_h, int start_m, int start_s, int finish_h, int finish_m, int finish_s, const char* path)
    {
        internet_protocol protocol;
        protocol.start.hours = start_h;
        protocol.start.minutes = start_m;
        protocol.start.seconds = start_s;
        protocol.finish.hours = finish_h;
        protocol.finish.minutes = finish_m;
        protocol.finish.seconds = finish_s;
        strcpy_s(protocol.path, path);
        return protocol;
    }

    TEST_CLASS(unittestproject)
    {
    public:
        TEST_METHOD(TestProcess_SumTimeForSkype)
        {
            internet_protocol protocols[3];
            protocols[0] = build_protocol(10, 0, 0, 12, 0, 0, "Skype"); // 7200 секунд (2 часа)
            protocols[1] = build_protocol(14, 0, 0, 16, 0, 0, "Zoom"); // не учитывается
            protocols[2] = build_protocol(9, 0, 0, 10, 30, 0, "Skype"); // 5400 секунд (1.5 часа)
            Assert::AreEqual(12600, process(protocols, 3, "Skype")); // Общее время 12600 секунд (3.5 часа)
        }

        TEST_METHOD(TestProcess_ZeroTimeForTeams)
        {
            internet_protocol protocols[3];
            protocols[0] = build_protocol(1, 0, 0, 1, 0, 0, "Teams"); // 0 секунд
            protocols[1] = build_protocol(2, 0, 0, 2, 0, 0, "Teams"); // 0 секунд
            protocols[2] = build_protocol(3, 0, 0, 3, 0, 0, "Teams"); // 0 секунд
            Assert::AreEqual(0, process(protocols, 3, "Teams")); // Общее время 0 секунд
        }

        TEST_METHOD(TestProcess_VariousTimesForProgram1)
        {
            internet_protocol protocols[3];
            protocols[0] = build_protocol(1, 0, 0, 1, 0, 30, "Program1"); // 30 секунд
            protocols[1] = build_protocol(2, 0, 0, 2, 1, 0, "Program1"); // 60 секунд (1 минута)
            protocols[2] = build_protocol(3, 0, 0, 3, 2, 0, "Program1"); // 120 секунд (2 минуты)
            Assert::AreEqual(210, process(protocols, 3, "Program1")); // Общее время 210 секунд
        }

        
    };
}
