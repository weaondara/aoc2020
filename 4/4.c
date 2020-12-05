#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void task1()
{
    char line[256];
    int current_line = 0;
    int alloced_lines = 16;
    char** lines = malloc(sizeof(char*) * alloced_lines);

    FILE* fp = fopen("input", "r");

    int byr = 0, iyr = 0, eyr = 0, hgt = 0, hcl = 0, ecl = 0, pid = 0;
    int valid = 0;

    while (fgets(line, sizeof(line), fp))
    {
        //printf("line: %s", line);
        if (strlen(line) < 4)
        {
            //printf("empty\n");
            if (byr && iyr && eyr && hgt && hcl && ecl && pid)
            {
                //printf("valid\n");
                valid++;
            }
            else
            {
                //printf("not valid\n");
            }
            byr = 0; iyr = 0; eyr = 0; hgt = 0; hcl = 0; ecl = 0; pid = 0;
            continue;
        }

        size_t pos = 0;
        size_t len = strlen(line);
        while(pos + 2 < len)
        {
            char code[] = {line[pos], line[pos + 1], line[pos + 2]};
            if (strncmp(code, "byr", (size_t)3) == 0) byr = 1;
            else if (strncmp(code, "iyr", (size_t)3) == 0) iyr = 1;
            else if (strncmp(code, "eyr", (size_t)3) == 0) eyr = 1;
            else if (strncmp(code, "hgt", (size_t)3) == 0) hgt = 1;
            else if (strncmp(code, "hcl", (size_t)3) == 0) hcl = 1;
            else if (strncmp(code, "ecl", (size_t)3) == 0) ecl = 1;
            else if (strncmp(code, "pid", (size_t)3) == 0) pid = 1;

            while(pos < len && line[pos] != ' ')
                pos++;
            pos++;
        }
    }

    //last line
    if (strlen(line) > 3)
    {
        if (byr && iyr && eyr && hgt && hcl && ecl && pid)
        {
            //printf("valid\n");
            valid++;
        }
        else
        {
            //printf("not valid\n");
        }
    }

    fclose(fp);

    printf("Task 1: Valid passports: %d\n", valid);
}

int isDigits(char* value, size_t len)
{
    if (strlen(value) != len)
        return 0;
    for (size_t i = 0; i < len; i++)
        if (value[i] < '0' || '9' < value[i])
            return 0;
    return 1;
}

int isHexCode(char* value)
{
    if (strlen(value) != 7 || value[0] != '#')
        return 0;
     for (size_t i = 1; i < 7; i++)
        if ((value[i] < '0' || '9' < value[i]) && (value[i] < 'a' || 'f' < value[i]))
            return 0;
    return 1;
}

void task2()
{
    char line[256];
    int current_line = 0;
    int alloced_lines = 16;
    char** lines = malloc(sizeof(char*) * alloced_lines);

    FILE* fp = fopen("input", "r");

    int byr = 0, iyr = 0, eyr = 0, hgt = 0, hcl = 0, ecl = 0, pid = 0;
    int valid = 0;

    while (fgets(line, sizeof(line), fp))
    {
        //printf("line: %s", line);
        if (strlen(line) < 4)
        {
            //printf("empty\n");
            if (byr && iyr && eyr && hgt && hcl && ecl && pid)
            {
                //printf("valid\n");
                valid++;
            }
            else
            {
                //printf("not valid\n");
            }
            byr = 0; iyr = 0; eyr = 0; hgt = 0; hcl = 0; ecl = 0; pid = 0;
            continue;
        }

        size_t pos = 0;
        size_t len = strlen(line);
        while(pos + 2 < len)
        {
            char code[] = {line[pos], line[pos + 1], line[pos + 2]};
            char value[20] = {0};

            size_t valuestart = pos + 4;
            while(pos < len && line[pos] != ' ' && line[pos] != '\n')
                pos++;
            size_t valueend = pos;
            memcpy(value, line + valuestart * sizeof(char), (valueend - valuestart) * sizeof(char));

            if (strncmp(code, "byr", (size_t)3) == 0 && isDigits(value, 4) && 1920 <= atoi(value) && atoi(value) <= 2002) byr = 1;
            else if (strncmp(code, "iyr", (size_t)3) == 0 && isDigits(value, 4) && 2010 <= atoi(value) && atoi(value) <= 2020) iyr = 1;
            else if (strncmp(code, "eyr", (size_t)3) == 0 && isDigits(value, 4) && 2020 <= atoi(value) && atoi(value) <= 2030) eyr = 1;
            else if (strncmp(code, "hgt", (size_t)3) == 0 && strlen(value) > 3)
            {
                char* unit = value + strlen(value) - 2 * sizeof(char);
                char unitvalue[20] = {0};
                memcpy(unitvalue, value, strlen(value) - 2 * sizeof(char));
                if (strncmp(unit, "cm", (size_t)2) == 0 && 150 <= atoi(unitvalue) && atoi(unitvalue) <= 193)
                    hgt = 1;
                else if (strncmp(unit, "in", (size_t)2) == 0 && 59 <= atoi(unitvalue) && atoi(unitvalue) <= 76)
                    hgt = 1;
            }
            else if (strncmp(code, "hcl", (size_t)3) == 0 && isHexCode(value)) hcl = 1;
            else if (strncmp(code, "ecl", (size_t)3) == 0 && (
                    strncmp(value, "amb", (size_t)3) == 0 ||
                    strncmp(value, "blu", (size_t)3) == 0 ||
                    strncmp(value, "brn", (size_t)3) == 0 ||
                    strncmp(value, "gry", (size_t)3) == 0 ||
                    strncmp(value, "grn", (size_t)3) == 0 ||
                    strncmp(value, "hzl", (size_t)3) == 0 ||
                    strncmp(value, "oth", (size_t)3) == 0
                )) ecl = 1;
            else if (strncmp(code, "pid", (size_t)3) == 0 && isDigits(value, 9)) pid = 1;

            pos++;
        }
    }

    //last line
    if (strlen(line) > 3)
    {
        if (byr && iyr && eyr && hgt && hcl && ecl && pid)
        {
            //printf("valid\n");
            valid++;
        }
        else
        {
            //printf("not valid\n");
        }
    }

    fclose(fp);

    printf("Task 2: Valid passports: %d\n", valid);
}

int main() {
    task1();
    task2();
    return 0;
}