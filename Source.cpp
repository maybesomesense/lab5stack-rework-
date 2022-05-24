#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "Header.h"
#include "oldHeader.h"


int main()
{
	char end;									 // ���������� ��� ������������ ���������
	do
	{
		system("cls");
		rewind(stdin);
		int mistakesCount;
		char* string = giveMemoryChar(50);						// ������� ��������� ������ ��� ������
		inputString(string);									// ������� ����� ������
		int length = strlen(string);							// ������� ����������� ����� ������
		int* mistakes = analyzeStack(string, &mistakesCount);	// �������, ������� ���������� ������� ������ � ����������� ������ � ������
		showResult(mistakes, mistakesCount, string, length);	// ������� ������� �� �����, ���� �� ��� - ������� ��������������� ���������
		free(string);											// ������������ ������
		string = nullptr;
		printf("Enter 1, to repeat. Or another symbol to leave\n");
		end = getchar();
	} while (end == '1');                  // ������������ ���������
	return 0;
}
