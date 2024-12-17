#include <iostream>
#include <iomanip>

using namespace std;

#include "internet_protocol.h"
#include "file_reader.h"
#include "constants.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Лабораторная работа №8. GIT\n";
    cout << "Вариант №5. Протокол Интернет\n";
    cout << "Автор: Егор Кузнечик\n";
    cout << "Группа: 24ПИнж1д\n\n";

    internet_protocol* protocols[MAX_FILE_ROWS_COUNT];
    int size;

    try
    {
        read ("data.txt", protocols, size);
        cout << "***** Протокол Интернет *****\n\n";
        for (int i = 0; i < size; i++)
        {
            /********** вывод времени начала **********/
            cout << "Время начала...: ";
            cout << setw(2) << setfill('0') << protocols[i]->start.hours << ':';
            cout << setw(2) << setfill('0') << protocols[i]->start.minutes << ':';
            cout << setw(2) << setfill('0') << protocols[i]->start.seconds << '\n';

            /********** вывод времени окончания **********/
            cout << "Время окончания: ";
            cout << setw(2) << setfill('0') << protocols[i]->finish.hours << ':';
            cout << setw(2) << setfill('0') << protocols[i]->finish.minutes << ':';
            cout << setw(2) << setfill('0') << protocols[i]->finish.seconds << '\n';

            /********** вывод полученных данных **********/
            cout << "Получено.......: " << protocols[i]->receive.kbytes << " кбайт\n";

            /********** вывод отправленных данных **********/
            cout << "Отправлено.....: " << protocols[i]->send.kbytes << " кбайт\n";

            /********** вывод пути **********/
            cout << "Путь...........: " << protocols[i]->path << '\n';
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
