#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

using namespace std;





typedef char*(*CodeLetter)(char);
typedef char*(*CodeWord)(char*, int, CodeLetter);


const int N = 256;

char* task(char*, int, CodeWord, CodeLetter);
char* encodeWords(char*, int, CodeLetter);
char* encodeLetter(char);

int main()
{
	char string[N] = "Jessica Runy, Percicle ABLE Project teacher says: Russians usually write long sentences with lots of commas.";
	cout << string << endl;

	int length;
	cout << "Length of word to code ";
	cin >> length;

	cout << task(string, length, encodeWords, encodeLetter) << endl;

	system("pause");
	return 0;
}

char* task(char* source, int lengthWords, CodeWord codeWord, CodeLetter codeLetter)
{
	const char* symbols = "ABCDEFGHIJKLMNOPQRSTUWVXYZabcdefghijklnmopqrstuwvxyz";
	char* pword = strpbrk(source, symbols);
	char* result = new char[N] {0};

	while (pword)
	{
		int length = strspn(pword, symbols);

		if (lengthWords == length)
		{
			char* code = codeWord(pword, length, codeLetter);
			strcat(result, code);
			pword += length;
			pword = strpbrk(pword, symbols);
		}
		else
		{
			strncat(result, pword, length + 1);
			pword += length;
			pword = strpbrk(pword, symbols);
		}
	}

	delete[] pword;

	return result;
}

char* encodeWords(char* word, int length, CodeLetter codeLetter)
{
	char* result = new char[N] {0};

	for (int i = 0; i < length; i++)
	{
		strcat(result, codeLetter(word[i]));
	}

	strcat(result, " ");

	return result;
}

char* encodeLetter(char letter)
{
	const char* symbolsUp = "ZYXWVUTSRQPONMLKJIHGFEDCBA";
	const char* symbolsDown = "zyxwvutsrqponmlkjihgfedcba";
	const char* brace = "()";

	char* code = new char[5]{ 0 };

	for (int i = 0; i < strlen(symbolsUp); i++)
	{
		if (letter == symbolsUp[i] || letter == symbolsDown[i])
		{
			code[0] = brace[0];

			if (i < 10)
			{
				code[1] = i + '0';
				code[2] = brace[1];
			}
			else
			{
				code[1] = i / 10 + '0';
				code[2] = i % 10 + '0';
				code[3] = brace[1];
			}

			break;
		}
	}

	return code;
}