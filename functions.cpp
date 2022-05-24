#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "Header.h"
#include "oldHeader.h"

void showResult(int* mistakes, int mistakesCount, char* string, int length) {
	if (mistakesCount)						     // если были найдены ошибки - выводим их на экран
	{
		sort(mistakes, mistakesCount);		 // сортировка массива с позициями ошибок
		showMistakes(string, mistakes, length);		 // выведение на экран строки с позициями ошибок
	}
	else printf("Parentheses are placed correctly\n");
}

void sort(int* array, int n) {					// Функция сортировки для массива ошибок
	int i, j, temp, half;
	for (half = n / 2; half > 0; half /= 2)
		for (i = half; i < n; i++)
			for (j = i - half; j >= 0 && *(array + j) > *(array + half + j); j -= half) {
				temp = *(array + j);
				*(array + j) = *(array + j + half);
				*(array + j + half) = temp;
			}
}

int* giveMemoryInt(int amount) {					// выделение памяти для массива int
	int* array = (int*)malloc(sizeof(int) * amount);
	return array;
}

char* giveMemoryChar(int amount) {					// выделение памяти для массива char
	char* string = (char*)malloc(sizeof(char) * amount);
	return string;
}

void inputString(char* string) {					// ввод строки
	fgets(string, 50, stdin);
}

char inverseBracket(char bracket) // функция инверсии скобки
{
	if (bracket == ')') return '(';
	if (bracket == '}') return '{';
	if (bracket == ']') return '[';
	if (bracket == '(') return ')';
	if (bracket == '{') return '}';
	if (bracket == '[') return ']';
}

void freeStack(Stack** stack)    // функция освобождения памяти для стека
{
	while (*stack)
	{
		pop(stack);
	}
}

brack* newBracket(int count)  // функция выделения памяти под массив структур
{
	brack* brackets;
	if (!(brackets = (brack*)calloc(count, sizeof(brack)))) exit(1);
	return brackets;
}

brack peek(Stack* stack) { return stack->bracket; } // функция просмотра элемента на вершине стека

brack pop(Stack** s)							    //  функция снятия элемента стека с вершины
{
	Stack* tmp, head;
	tmp = *s;                // запоминаем указатель на вершину стека      
	head = **s;              // запоминаем содержимое вершины стека
	*s = (*s)->l;            // указатель передвигаем "вниз" по стеку
	free(tmp);               // удаляем элемент с вершины стека
	tmp = nullptr;
	return head.bracket;
}

void show(Stack* stack)  // функция вывода стека
{
	if (!stack) exit(-1);
	do
	{
		printf("%d %d\n", stack->bracket.inf, stack->bracket.pos);  // вывод информации текущего эл-та стека
		stack = stack->l;											// переход "вниз" к предыдущему эл-ту стека
	} while (stack);
}

void push(Stack** s, brack bracket)		  // функция cоздания/добавления элемента в стек
{
	Stack* tmp = *s;
	if (!(*s = (Stack*)calloc(1, sizeof(Stack))))  // указатель на новый элемент стека
	{
		puts("Нет свободной памяти\n");
		exit(-1);
	}
	(*s)->bracket.inf = bracket.inf;
	(*s)->bracket.pos = bracket.pos;
	(*s)->l = tmp;								  // новый элемент стека "ссылается" на элемент вершину стека
	tmp = *s;
}

void openingBracket(Stack** stack, int* bracketCount, brack bracket) // функция для занесения открывающих скобок в стек
{
	(*bracketCount)++;
	push(stack, bracket);
}

void closingBracket(Stack** stack, int* k, int* l, int* z, int* mistakes, int* counter, brack bracket) // функция для занесения закрывающих скобок в стек
{
	brack prevBracket = {};
	if (*stack) prevBracket = peek(*stack);   // запоминаем предыдущую скобку
	(*k)--;
	if (*k < 0)                  // закрывающая скобка первее открывающей
	{
		*(mistakes + *counter) = bracket.pos; // заносим позицию в строке в массив с ошибками
		(*counter)++;
		markMistakes(stack, mistakes, counter);
		*k = 0, * l = 0, * z = 0;
	}
	else if (prevBracket.inf == bracket.inf || prevBracket.inf == inverseBracket(bracket.inf)) pop(stack); // если предыдущая скобка такого же типа
	else                    // предыдущая скобка другого типа
	{
		*(mistakes + *counter) = bracket.pos;
		(*counter)++;
		markMistakes(stack, mistakes, counter);
		*k = 0, * l = 0, * z = 0;
	}
}

void markMistakes(Stack** s, int* array, int* counter) // функция освобождения стека и занесения ошибок в массив
{
	brack tmp;
	while (*s)
	{
		tmp = pop(s);
		*(array + *counter) = tmp.pos;
		(*counter)++;
	}
}

int* analyzeStack(char* string, int* arrayLength)
{
	Stack* stack = nullptr;		   // стек c открывающими скобками
	brack tmp;					   // переменная для запоминания скобки и ее позиции
	int k = 0;					   // количество круглых скобок
	int l = 0;					   // количество квадратных скобок
	int z = 0;					   // количество фигурных скобок
	int counter = 0;               // счетчик для выходного массива
	int len = strlen(string);	   // длина строки
	int* mistakes = giveMemoryInt(len);   // выделение памяти под массив с позициями ошибок
	for (int i = 0; i < len; i++)
	{
		tmp = { *(string + i), i };
		if (*(string + i) == '(')	   openingBracket(&stack, &k, tmp);  // функция для занесения открывающих скобок в стек
		else if (*(string + i) == '[') openingBracket(&stack, &l, tmp);
		else if (*(string + i) == '{') openingBracket(&stack, &z, tmp);
		else if (*(string + i) == ')') closingBracket(&stack, &k, &l, &z, mistakes, &counter, tmp);  // закрывающих скобок
		else if (*(string + i) == ']') closingBracket(&stack, &l, &k, &z, mistakes, &counter, tmp);
		else if (*(string + i) == '}') closingBracket(&stack, &z, &l, &k, mistakes, &counter, tmp);
	}
	markMistakes(&stack, mistakes, &counter);	// заносим в массив ошибок оставшиеся в стеке скобки и освобождаем его
	*arrayLength = counter;						// запоминаем размер массива с ошибками
	return mistakes;
}

void showMistakes(char* string, int* mistakes, int len) // функция выделения ошибок в расстановке скобок
{
	for (int i = 0, color = 0; i < len; i++)
	{
		if (i == *(mistakes + color)) // если встретили ошибку, то красим ее
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
			putchar(*(string + i));
			color++;
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_BACKGROUND | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			putchar(*(string + i));
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_BACKGROUND | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	printf("\n");
}