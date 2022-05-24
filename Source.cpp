#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "Header.h"
#include "oldHeader.h"


int main()
{
	char end;									 // переменная для зацикливания программы
	do
	{
		system("cls");
		rewind(stdin);
		int mistakesCount;
		char* string = giveMemoryChar(50);						// функция выделения памяти под строку
		inputString(string);									// функция ввода строки
		int length = strlen(string);							// функция определения длины строки
		int* mistakes = analyzeStack(string, &mistakesCount);	// функция, которая определяет позиции ошибок в расстановке скобок в строке
		showResult(mistakes, mistakesCount, string, length);	// выводим ошибоки на экран, если их нет - выводим соответствующее сообщение
		free(string);											// освобождение памяти
		string = nullptr;
		printf("Enter 1, to repeat. Or another symbol to leave\n");
		end = getchar();
	} while (end == '1');                  // зацикливание программы
	return 0;
}
