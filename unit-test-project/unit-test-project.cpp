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
            protocols[0] = build_protocol(10, 0, 0, 12, 0, 0, "Skype"); // 7200 ������ (2 ����)
            protocols[1] = build_protocol(14, 0, 0, 16, 0, 0, "Zoom"); // �� �����������
            protocols[2] = build_protocol(9, 0, 0, 10, 30, 0, "Skype"); // 5400 ������ (1.5 ����)
            Assert::AreEqual(12600, process(protocols, 3, "Skype")); // ����� ����� 12600 ������ (3.5 ����)
        }

        TEST_METHOD(TestProcess_ZeroTimeForTeams)
        {
            internet_protocol protocols[3];
            protocols[0] = build_protocol(1, 0, 0, 1, 0, 0, "Teams"); // 0 ������
            protocols[1] = build_protocol(2, 0, 0, 2, 0, 0, "Teams"); // 0 ������
            protocols[2] = build_protocol(3, 0, 0, 3, 0, 0, "Teams"); // 0 ������
            Assert::AreEqual(0, process(protocols, 3, "Teams")); // ����� ����� 0 ������
        }

        TEST_METHOD(TestProcess_VariousTimesForProgram1)
        {
            internet_protocol protocols[3];
            protocols[0] = build_protocol(1, 0, 0, 1, 0, 30, "Program1"); // 30 ������
            protocols[1] = build_protocol(2, 0, 0, 2, 1, 0, "Program1"); // 60 ������ (1 ������)
            protocols[2] = build_protocol(3, 0, 0, 3, 2, 0, "Program1"); // 120 ������ (2 ������)
            Assert::AreEqual(210, process(protocols, 3, "Program1")); // ����� ����� 210 ������
        }

        
    };
}
