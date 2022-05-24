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

struct mistake {
	int type;
	int pos;
};

mistake* analyzeStack(char*, int*);										// �������, ������� ���������� ������� ������ � ����������� ������ � ������
brack pop(Stack**);														// ������� ������ �������� � ������� �����
brack peek(Stack* );													// ������� ��������� �������� �� ������� �����
void markMistakes(Stack** , mistake* , int*, int);								// ������� ������������ ����� � ��������� ������ � ������
void push(Stack** , brack );											// ������� ���������� ������ �������� � ����
void showMistakes(char* , mistake* , int );									// ������� ����������� �� ����� ������� ������ � ����������� ������
void openingBracket(Stack** , int* , brack );							// ������� ���������� ����������� ������ � ����
void closingBracket(Stack** , int*, int*, int*, mistake*, int*, brack);		// ������� ������� ����������� ������
char inverseBracket(char );												// ������� �������� ������
void show(Stack* );														// ������� ��������� �����
void freeStack(Stack** );												// ������� ������������ �����
void showResult(mistake*, int, char*, int);									// ������� ������ ������ �� �����, ���� �� ��� - ������� ��������������� ���������