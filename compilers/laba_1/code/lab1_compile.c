#include <stdio.h>
#include <string.h>
#include <conio.h>

#define STATES_COUNT 4

enum CHARTYPE
{
	UNKNOWN = 0, // Если тип не определен
	QUOTE,       // Кавычка 
	SYMBOL,		 // Символ

	height		 // Кол-во элементов в enum
};

const int transitions[STATES_COUNT][height] =
{
	{0,0,0}, // Сотояние "Ошибка" 
	{0,2,0}, // Состояние "Ждем первую одинарную кавычку"
	{0,3,2}, // Состояние "Ждем символ или одинарную кавычку"
	{0,2,0}  // Состояние "Ждем одинарную кавычку или конец строки"
};

const int states[STATES_COUNT] = { 0,0,1,0 };

void trim(char* s);
short getCharType(char symbol);

int main() 
{

	char line[100] = { NULL };
	
	printf("Write a Pascal string in a correct form:\n");

	//Ввод исходной Pascal строки
	gets(line);
	trim(line);

	int state = 1;
	int result;

	for (unsigned i = 0; i < strlen(line); i++) 
		state = transitions[state][getCharType(line[i])];

	result = states[state - 1];

	//Проверяем на правильность введенной строки
	if (!result) 
	{
		printf("Incorrect line\n");
	}
	else 
	{
		printf("Line is correct\n");
	}

	return 0;
}

short getCharType(char symbol)
{
	if (symbol == 39) 
		return QUOTE;
	else if (symbol > 31 && symbol < 127) 
		return SYMBOL;
	else 
		return UNKNOWN;
}

void trim(char* s)
{
	// удаляем пробелы и табы с начала строки:
	int i = 0, j;
	while ((s[i] == ' ') || (s[i] == '\t'))
	{
		i++;
	}
	if (i > 0)
	{
		for (j = 0; j < strlen(s); j++)
		{
			s[j] = s[j + i];
		}
		s[j] = '\0';
	}

	// удаляем пробелы и табы с конца строки:
	i = strlen(s) - 1;
	while ((s[i] == ' ') || (s[i] == '\t'))
	{
		i--;
	}
	if (i < (strlen(s) - 1))
	{
		s[i + 1] = '\0';
	}
}