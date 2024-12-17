#include <iostream>
#include <iomanip>

using namespace std;

#include "internet_protocol.h"
#include "file_reader.h"
#include "constants.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "������������ ������ �8. GIT\n";
    cout << "������� �5. �������� ��������\n";
    cout << "�����: ���� ��������\n";
    cout << "������: 24����1�\n\n";

    internet_protocol* protocols[MAX_FILE_ROWS_COUNT];
    int size;

    try
    {
        read ("data.txt", protocols, size);
        cout << "***** �������� �������� *****\n\n";
        for (int i = 0; i < size; i++)
        {
            /********** ����� ������� ������ **********/
            cout << "����� ������...: ";
            cout << setw(2) << setfill('0') << protocols[i]->start.hours << ':';
            cout << setw(2) << setfill('0') << protocols[i]->start.minutes << ':';
            cout << setw(2) << setfill('0') << protocols[i]->start.seconds << '\n';

            /********** ����� ������� ��������� **********/
            cout << "����� ���������: ";
            cout << setw(2) << setfill('0') << protocols[i]->finish.hours << ':';
            cout << setw(2) << setfill('0') << protocols[i]->finish.minutes << ':';
            cout << setw(2) << setfill('0') << protocols[i]->finish.seconds << '\n';

            /********** ����� ���������� ������ **********/
            cout << "��������.......: " << protocols[i]->receive.kbytes << " �����\n";

            /********** ����� ������������ ������ **********/
            cout << "����������.....: " << protocols[i]->send.kbytes << " �����\n";

            /********** ����� ���� **********/
            cout << "����...........: " << protocols[i]->path << '\n';
            cout << '\n';
        }
        for (int i = 0; i < size; i++)
        {
            delete protocols[i];
        }
    }
    catch (const char* error)
    {
        cout << error << '\n';
    }

    return 0;
}
