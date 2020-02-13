#include "Functions.h"

void flush()
{
	cin.clear();
	while (cin.get() != '\n');
}

int menu()
{
	int key = 0;
	int code;

	do {
		system("cls");

		key = (key + 3) % 3;

		if (key == 0) cout << "-> Add the word" << endl;
		else  cout << "   Add the word" << endl;
		if (key == 1) cout << "-> Find the word" << endl;
		else  cout << "   Find the word" << endl;
		if (key == 2) cout << "-> Exit" << endl;
		else cout << "   Exit" << endl;

		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}

	} while (code != 13);
	system("cls");
	return key;
}





char* newword(const char* text, char* word)
{
	while (true)
	{
		cout << "Enter the " << text << " (Up to 15 leters) to add it in the base" << endl;

		cin.getline(word, 15);
		if (cin.fail())
		{
			flush();
			system("cls");
			cout << "Incorrect input" << endl;
			continue;
		}

		bool ret = false;

		for (int i = 1; i < 16; i++)
		{
			if (word[i] != ' ' && word[i - 1] == ' ')
			{
				ret = true;
				break;
			}
		}
		for (int i = 0; i < 16; i++)
		{
			if (!isalpha(word[i]) && word[i] != '\0' && (word[i] < 'À' || word[i] > 'ÿ') && word[i] != '¿' && word[i] != 'º' && word[i] != '³' && word[i] != '¯' && word[i] != 'ª' && word[i] != '²')
			{
				ret = true;
				break;
			}
		}
		if (word[0] == '\0')
		{
			system("cls");
			continue;
		}
		if (ret == true)
		{
			system("cls");
			cout << "Incorrect input" << endl;
			continue;
		}

		break;
	}

	bool engl = true;

	for (int j = 0; j < 16; j++)
	{
		if (((word[j] >= 65 && word[j] <= 90) || (word[j] >= 97 && word[j] <= 122)) || word[j] == '\0')
		{
			continue;
		}
		else
		{
			engl = false;
		}
	}

	if (engl == true)
	{
		for (int i = 1; i < 17; i++)
		{
			if (word[i] == '\0')
			{
				word[i] = '.';
				word[i + 1] = 'T';
				word[i + 2] = 'X';
				word[i + 3] = 'T';
				break;
			}
		}
	}

	return word;
}





void Add()
{
	Word word = {};

	FILE* file = fopen(newword("english word", word.eng), "w");

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	fwrite(newword("ukrainian translate", word.ukr), 16, 1, file);

	fclose(file);

	cout << "Successfully added" << endl;
}




void Find()
{
	while (true)
	{
		cout << "Enter the word to find" << endl;

		Word word;

		cin.getline(word.eng, 15);
		if (cin.fail())
		{
			flush();
			system("cls");
			continue;
		}

		if (word.eng[0] == '\0')
		{
			system("cls");
			continue;
		}

		bool ret = false;

		for (int i = 1; i < 16; i++)
		{
			if (word.eng[i] != ' ' && word.eng[i - 1] == ' ')
			{
				ret = true;
				break;
			}
		}

		if (ret == true)
		{
			cout << "There is no such a word" << endl;
			break;
		}

		char english[20] = {};
		strcpy(english, word.eng);

		for (int i = 1; i < 17; i++)
		{
			if (word.eng[i] == '\0')
			{
				word.eng[i] = '.';
				word.eng[i + 1] = 'T';
				word.eng[i + 2] = 'X';
				word.eng[i + 3] = 'T';
				break;
			}
		}

		try
		{
			FILE* file;

			if ((file = fopen(word.eng, "r")) != NULL)
			{
				fread(word.ukr, 20, 1, file);
				
				cout << english << " - " << word.ukr << endl;

				fclose(file);
			}
			else
			{
				cout << "There is no such a word" << endl;
			}
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
			cout << "There is no such a word" << endl;
		}

		break;
	}
}