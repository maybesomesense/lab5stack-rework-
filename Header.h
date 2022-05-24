struct brack
{
	char inf;		// символ скобки
	int pos;		// позиция скобки в исходной строке
};

struct Stack
{
	brack bracket;	// информация о скобке
	Stack* l;       // адресное поле(следующий элемент)
};

struct mistake {
	int type;
	int pos;
};

mistake* analyzeStack(char*, int*);										// функция, которая определяет позиции ошибок в расстановке скобок в строке
brack pop(Stack**);														// функция снятия элемента с вершины стека
brack peek(Stack* );													// функция просмотра элемента на вершине стека
void markMistakes(Stack** , mistake* , int*, int);								// функция освобождения стека и занесения ошибок в массив
void push(Stack** , brack );											// функция добавления нового элемента в стек
void showMistakes(char* , mistake* , int );									// функция отображения на экран позиций ошибок в расстановке скобок
void openingBracket(Stack** , int* , brack );							// функция добавления открывающей скобки в стек
void closingBracket(Stack** , int*, int*, int*, mistake*, int*, brack);		// функция анализа закрывающей скобки
char inverseBracket(char );												// функция инверсии скобки
void show(Stack* );														// функция просмотра стека
void freeStack(Stack** );												// функция освобождения стека
void showResult(mistake*, int, char*, int);									// функция вывода ошибок на экран, если их нет - выводит соответствующее сообщение