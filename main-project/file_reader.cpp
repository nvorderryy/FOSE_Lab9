#include "file_reader.h"
#include "constants.h"
#include <fstream>
#include <cstring>

time1 convert_to_time(char* str)
{
    time1 result = { 0, 0, 0 }; 
    char* context = NULL;
    char* str_number = strtok_s(str, ":", &context);
    if (str_number != NULL) result.hours = atoi(str_number);
    str_number = strtok_s(NULL, ":", &context);
    if (str_number != NULL) result.minutes = atoi(str_number);
    str_number = strtok_s(NULL, ":", &context);
    if (str_number != NULL) result.seconds = atoi(str_number);
    return result;
}

void read(const char* file_name, internet_protocol* array[], int& size)
{
    std::ifstream file(file_name);
    if (file.is_open())
    {
        size = 0;
        char tmp_buffer[MAX_STRING_SIZE];
        while (!file.eof() && size < MAX_FILE_ROWS_COUNT)
        {
            internet_protocol* item = new internet_protocol;
            file >> tmp_buffer;
            item->start = convert_to_time(tmp_buffer);
            file >> tmp_buffer;
            item->finish = convert_to_time(tmp_buffer);
            file >> item->receive.kbytes;
            file >> item->send.kbytes;
            file.ignore(); // Пропуск пробела перед чтением пути
            file.getline(item->path, MAX_STRING_SIZE);
            array[size++] = item;
        }
        file.close();
    }
    else
    {
        throw "Ошибка открытия файла";
    }
}
