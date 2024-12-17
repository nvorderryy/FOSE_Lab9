#include <iostream>

using namespace std;

#include "internet_protocol.h"
#include "file_reader.h"
#include "constants.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Лабораторная работа №8. GIT\n";
    cout << "Вариант №5. Протокол Интернет\n";
    cout << "Автор: Egor Kuznechik\n\n";

    internet_protocol* protocols[MAX_FILE_ROWS_COUNT];
    int size;

    try
    {
        read("data.txt", protocols, size);
        for (int i = 0; i < size; i++)
        {
            cout << protocols[i]->start.hours << ':';
            cout << protocols[i]->start.minutes << ':';
            cout << protocols[i]->start.seconds << '\n';
            cout << protocols[i]->finish.hours << ':';
            cout << protocols[i]->finish.minutes << ':';
            cout << protocols[i]->finish.seconds << '\n';
            cout << protocols[i]->receive.kbytes << '\n';
            cout << protocols[i]->send.kbytes << '\n';
            cout << protocols[i]->path << '\n';
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
