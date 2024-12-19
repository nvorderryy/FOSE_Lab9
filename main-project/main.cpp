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
    cout << "����� ������...: ";
    cout << setw(2) << setfill('0') << protocol->start.hours << ':';
    cout << setw(2) << setfill('0') << protocol->start.minutes << ':';
    cout << setw(2) << setfill('0') << protocol->start.seconds << '\n';

    cout << "����� ���������: ";
    cout << setw(2) << setfill('0') << protocol->finish.hours << ':';
    cout << setw(2) << setfill('0') << protocol->finish.minutes << ':';
    cout << setw(2) << setfill('0') << protocol->finish.seconds << '\n';

    cout << "��������.......: " << protocol->receive.kbytes << " �����\n";
    cout << "����������.....: " << protocol->send.kbytes << " �����\n";
    cout << "����...........: " << protocol->path << '\n';
    cout << '\n';
}

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
        read("data.txt", protocols, size);
        cout << "***** �������� �������� *****\n\n";
        for (int i = 0; i < size; i++)
        {
            output(protocols[i]);
        }

        bool (*check_function)(internet_protocol*) = NULL; 
        cout << "\n�������� ��������:\n";
        cout << "1) ������ �� ��������� Skype\n";
        cout << "2) ������ �� ������� ����� 08:00:00\n";
        cout << "3) ���������� ������\n";
        cout << "\n��� �����: ";
        int item;
        cin >> item;
        cout << '\n';

        switch (item)
        {
        case 1:
            check_function = check_protocol_by_program;
            cout << "***** ��������������� ������ �� ��������� Skype *****\n\n";
            break;
        case 2:
            check_function = check_protocol_by_time;
            cout << "***** ��������������� ������ �� ������� ����� 08:00:00 *****\n\n";
            break;
        case 3:
        {
            cout << "�������� ����� ����������:\n";
            cout << "1) ���������� ���������\n";
            cout << "2) ������� ����������\n";
            cout << "\n��� �����: ";
            int sort_choice;
            cin >> sort_choice;

            cout << "�������� �������� ����������:\n";
            cout << "1) �� �������� ������� �������������\n";
            cout << "2) �� ����������� �������� ��������� � �������� ������ ������\n";
            cout << "\n��� �����: ";
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

            cout << "***** ��������������� ������ *****\n\n";
            for (int i = 0; i < size; i++)
            {
                output(protocols[i]);
            }
            break;
        }
        default:
            throw "�������� �����";
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
