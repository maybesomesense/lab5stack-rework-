struct brack
{
	char inf;		// ������ ������
	int pos;		// ������� ������ � �������� ������
};

struct Stack
{
	brack bracket;	// ���������� � ������
	Stack* l;       // �������� ����(��������� �������)
};

struct errors {
	int type;
	int pos;
};

brack pop(Stack**);														// ������� ������ �������� � ������� �����
brack peek(Stack* );													// ������� ��������� �������� �� ������� �����
void markMistakes(Stack** , int* , int* );								// ������� ������������ ����� � ��������� ������ � ������
void push(Stack** , brack );											// ������� ���������� ������ �������� � ����
void showMistakes(char* , int* , int );									// ������� ����������� �� ����� ������� ������ � ����������� ������
int* analyzeStack(char* , int* );										// �������, ������� ���������� ������� ������ � ����������� ������ � ������
void openingBracket(Stack** , int* , brack );							// ������� ���������� ����������� ������ � ����
void closingBracket(Stack** , int*, int*, int*, int*, int*, brack);		// ������� ������� ����������� ������
char inverseBracket(char );												// ������� �������� ������
void show(Stack* );														// ������� ��������� �����
void freeStack(Stack** );												// ������� ������������ �����
void showResult(int*, int, char*, int);									// ������� ������ ������ �� �����, ���� �� ��� - ������� ��������������� ���������