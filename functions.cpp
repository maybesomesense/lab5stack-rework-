#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "Header.h"
#include "oldHeader.h"

mistake* analyzeStack(char* string, int* arrayLength)
{
	Stack* stack = nullptr;		   // ���� c ������������ ��������
	brack tmp;					   // ���������� ��� ����������� ������ � �� �������
	int k = 0;					   // ���������� ������� ������
	int l = 0;					   // ���������� ���������� ������
	int z = 0;					   // ���������� �������� ������
	int counter = 0;               // ������� ��� ��������� �������
	int len = strlen(string);	   // ����� ������
	mistake* mistakes = giveMemoryErrors(len);
	for (int i = 0; i < len; i++)
	{
		tmp = { *(string + i), i };
		if (*(string + i) == '(')	   openingBracket(&stack, &k, tmp);  // ������� ��� ��������� ����������� ������ � ����
		else if (*(string + i) == '[') openingBracket(&stack, &l, tmp);
		else if (*(string + i) == '{') openingBracket(&stack, &z, tmp);
		else if (*(string + i) == ')') closingBracket(&stack, &k, &l, &z, mistakes, &counter, tmp);  // ����������� ������
		else if (*(string + i) == ']') closingBracket(&stack, &l, &k, &z, mistakes, &counter, tmp);
		else if (*(string + i) == '}') closingBracket(&stack, &z, &l, &k, mistakes, &counter, tmp);
	}
	markMistakes(&stack, mistakes, &counter, 3);	// ������� � ������ ������ ���������� � ����� ������ � ����������� ���
	*arrayLength = counter;						// ���������� ������ ������� � ��������
	return mistakes;
}

void showResult(mistake* mistakes, int mistakesCount, char* string, int length) {
	if (mistakesCount)						     // ���� ���� ������� ������ - ������� �� �� �����
	{
		sort(mistakes, mistakesCount);		 // ���������� ������� � ��������� ������
		showMistakes(string, mistakes, length);		 // ��������� �� ����� ������ � ��������� ������
	}
	else printf("Parentheses are placed correctly\n");
}

void sort(mistake* mistakes, int n) {					// ������� ���������� ��� ������� ������
	int i, j, temp, half;
	for (half = n / 2; half > 0; half /= 2)
		for (i = half; i < n; i++)
			for (j = i - half; j >= 0 && (mistakes + j)->pos > (mistakes + half + j)->pos; j -= half) {
				temp = (mistakes + j)->pos;
				(mistakes + j)->pos = (mistakes + half + j)->pos;
				(mistakes + half + j)->pos = temp;
				temp = (mistakes + j)->type;
				(mistakes + j)->type = (mistakes + half + j)->type;
				(mistakes + half + j)->type = temp;
			}
}

int* giveMemoryInt(int amount) {					// ��������� ������ ��� ������� int
	int* array = (int*)malloc(sizeof(int) * amount);
	return array;
}

char* giveMemoryChar(int amount) {					// ��������� ������ ��� ������� char
	char* string = (char*)malloc(sizeof(char) * amount);
	return string;
}

void inputString(char* string) {					// ���� ������
	fgets(string, 50, stdin);
}

char inverseBracket(char bracket) // ������� �������� ������
{
	if (bracket == ')') return '(';
	if (bracket == '}') return '{';
	if (bracket == ']') return '[';
	if (bracket == '(') return ')';
	if (bracket == '{') return '}';
	if (bracket == '[') return ']';
}

void freeStack(Stack** stack)    // ������� ������������ ������ ��� �����
{
	while (*stack)
	{
		pop(stack);
	}
}

brack* newBracket(int count)  // ������� ��������� ������ ��� ������ ��������
{
	brack* brackets;
	if (!(brackets = (brack*)calloc(count, sizeof(brack)))) exit(1);
	return brackets;
}

brack peek(Stack* stack) { return stack->bracket; } // ������� ��������� �������� �� ������� �����

brack pop(Stack** s)							    //  ������� ������ �������� ����� � �������
{
	Stack* tmp, head;
	tmp = *s;                // ���������� ��������� �� ������� �����      
	head = **s;              // ���������� ���������� ������� �����
	*s = (*s)->l;            // ��������� ����������� "����" �� �����
	free(tmp);               // ������� ������� � ������� �����
	tmp = nullptr;
	return head.bracket;
}

void show(Stack* stack)  // ������� ������ �����
{
	if (!stack) exit(-1);
	do
	{
		printf("%d %d\n", stack->bracket.inf, stack->bracket.pos);  // ����� ���������� �������� ��-�� �����
		stack = stack->l;											// ������� "����" � ����������� ��-�� �����
	} while (stack);
}

void push(Stack** s, brack bracket)		  // ������� c�������/���������� �������� � ����
{
	Stack* tmp = *s;
	if (!(*s = (Stack*)calloc(1, sizeof(Stack))))  // ��������� �� ����� ������� �����
	{
		puts("��� ��������� ������\n");
		exit(-1);
	}
	(*s)->bracket.inf = bracket.inf;
	(*s)->bracket.pos = bracket.pos;
	(*s)->l = tmp;								  // ����� ������� ����� "���������" �� ������� ������� �����
	tmp = *s;
}

void openingBracket(Stack** stack, int* bracketCount, brack bracket) // ������� ��� ��������� ����������� ������ � ����
{
	(*bracketCount)++;
	push(stack, bracket);
}

void closingBracket(Stack** stack, int* k, int* l, int* z, mistake* mistakes, int* counter, brack bracket) // ������� ��� ��������� ����������� ������ � ����
{
	brack prevBracket = {};
	if (*stack) prevBracket = peek(*stack);   // ���������� ���������� ������
	(*k)--;
	if (*k < 0)								  // ����������� ������ ������ �����������
	{
		(mistakes + *counter)->pos = bracket.pos;		// ������� ������� � ������ � ������ � ��������
		(mistakes + *counter)->type = 1;
		(*counter)++;
		markMistakes(stack, mistakes, counter, 1);
		*k = 0, * l = 0, * z = 0;
	}
	else if (prevBracket.inf == bracket.inf || prevBracket.inf == inverseBracket(bracket.inf)) pop(stack); // ���� ���������� ������ ������ �� ����
	else                    // ���������� ������ ������� ����
	{
		(mistakes + *counter)->pos = bracket.pos;
		(mistakes + *counter)->type = 2;
		(*counter)++;
		markMistakes(stack, mistakes, counter, 2);
		*k = 0, * l = 0, * z = 0;
	}
}

void markMistakes(Stack** s, mistake* mistakes, int* counter, int error) // ������� ������������ ����� � ��������� ������ � ������
{
	brack tmp;
	while (*s)
	{
		tmp = pop(s);
		(mistakes + *counter)->pos = tmp.pos;
		(mistakes + *counter)->type = error;
		(*counter)++;
	}
}

mistake*	giveMemoryErrors(int n) {
	mistake* mistakes = (mistake*) malloc(sizeof(mistake) * n);
	return mistakes;
}



void showMistakes(char* string, mistake* mistakes, int len) // ������� ��������� ������ � ����������� ������
{
	for (int i = 0, color = 0; i < len; i++)
	{
		if (i == (mistakes + color)->pos) // ���� ��������� ������, �� ������ ��
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

	for (int i = 0, shift = 0; i < len; i++) {
		if ((mistakes + shift)->type == 1) // 
		{
			printf("There is no opening bracket on the closing bracket for position %d \n", (mistakes + shift)->pos);
			shift++;
		}
		else if ((mistakes + shift)->type == 2) {
			printf("Wrong balance on position %d\n", (mistakes + shift)->pos);
			shift++;
		}
		else if ((mistakes + shift)->type == 3) {
			printf("The remaining opening brackets, incorrectly positioned at position %d\n", (mistakes + shift)->pos);
			shift++;
		}
	}

	for (int i = 0; i < len; i++) {
		printf("%d ", (mistakes + i)->pos);
	}
	printf("\n");
	for (int i = 0; i < len; i++) {
		printf("%d ", (mistakes + i)->type);
	}
}