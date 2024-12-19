#include <iostream>
#include <iomanip>
#include "constants.h"
#include "internet_protocol.h"
#include "file_reader.h"
#include "filter.h"
#include "sort.h"

using namespace std;

void output(const internet_protocol* protocol)
{
    cout << "Время начала...: ";
    cout << setw(2) << setfill('0') << protocol->start.hours << ':';
    cout << setw(2) << setfill('0') << protocol->start.minutes << ':';
    cout << setw(2) << setfill('0') << protocol->start.seconds << '\n';

    cout << "Время окончания: ";
    cout << setw(2) << setfill('0') << protocol->finish.hours << ':';
    cout << setw(2) << setfill('0') << protocol->finish.minutes << ':';
    cout << setw(2) << setfill('0') << protocol->finish.seconds << '\n';

    cout << "Получено.......: " << protocol->receive.kbytes << " кбайт\n";
    cout << "Отправлено.....: " << protocol->send.kbytes << " кбайт\n";
    cout << "Путь...........: " << protocol->path << '\n';
    cout << '\n';
}

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
        read("data.txt", protocols, size);
        cout << "***** Протокол Интернет *****\n\n";
        for (int i = 0; i < size; i++)
        {
            output(protocols[i]);
        }

        bool (*check_function)(internet_protocol*) = NULL; 
        cout << "\nВыберите действие:\n";
        cout << "1) Фильтр по программе Skype\n";
        cout << "2) Фильтр по времени после 08:00:00\n";
        cout << "3) Сортировка данных\n";
        cout << "\nВаш выбор: ";
        int item;
        cin >> item;
        cout << '\n';

        switch (item)
        {
        case 1:
            check_function = check_protocol_by_program;
            cout << "***** Отфильтрованные данные по программе Skype *****\n\n";
            break;
        case 2:
            check_function = check_protocol_by_time;
            cout << "***** Отфильтрованные данные по времени после 08:00:00 *****\n\n";
            break;
        case 3:
        {
            cout << "Выберите метод сортировки:\n";
            cout << "1) Сортировка вставками\n";
            cout << "2) Быстрая сортировка\n";
            cout << "\nВаш выбор: ";
            int sort_choice;
            cin >> sort_choice;

            cout << "Выберите критерий сортировки:\n";
            cout << "1) По убыванию времени использования\n";
            cout << "2) По возрастанию названия программы и убыванию объема данных\n";
            cout << "\nВаш выбор: ";
            int criteria_choice;
            cin >> criteria_choice;

            if (sort_choice == 1)
            {
                if (criteria_choice == 1)
                {
                    insertion_sort(protocols, size, compare_by_usage_time);
                }
                else if (criteria_choice == 2)
                {
                    insertion_sort(protocols, size, compare_by_program_and_data);
                }
            }
            else if (sort_choice == 2)
            {
                if (criteria_choice == 1)
                {
                    quick_sort(protocols, 0, size - 1, compare_by_usage_time);
                }
                else if (criteria_choice == 2)
                {
                    quick_sort(protocols, 0, size - 1, compare_by_program_and_data);
                }
            }

            cout << "***** Отсортированные данные *****\n\n";
            for (int i = 0; i < size; i++)
            {
                output(protocols[i]);
            }
            break;
        }
        default:
            throw "Неверный выбор";
        }

        if (check_function)
        {
            int new_size;
            internet_protocol** filtered = filter(protocols, size, check_function, new_size);
            for (int i = 0; i < new_size; i++)
            {
                output(filtered[i]);
            }
            delete[] filtered;
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
