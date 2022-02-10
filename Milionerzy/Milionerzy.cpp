#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int question(string question[]) {
	char playerAnswer;
	cout <<question[0] << endl << endl;
	cout << "A: " << question[1] << endl;
	cout << "B: " << question[2] << endl;
	cout << "C: " << question[3] << endl;
	cout << "D: "<< question[4] << endl;
	cout << "OdpowiedŸ: ";
	cin >> playerAnswer;

	if (toupper(playerAnswer) == 'R')
	{
		return -1 ; // Resignation
	}

	if (toupper(playerAnswer) == toupper(question[5][0]))
	{
		return  1 ; // true
	} 
	return 0; // flase

}
void printTutorial() {
	cout << "------Instrukcja------ " << endl;
	cout << "Aby odpowiedzieæ na pytanie wpisz 'a', 'b', 'c' lub 'd' i kliknij enter" << endl;
	cout << "Jeœli chcesz zrezygnowaæ z odpowiedzi na pytanie i wygraæ wartoœæ pieniê¿n¹ równ¹ poprzedniemu pytaniu wpisz r i kliknij enter \n" << endl;
	
	cout << "\n\n\n Witaj w grze milionerzy, z tej strony Ce'plus-plus Urbañski, zaraz zaczynamy nasz teleturniej!\n\n" << endl;

}
int main()
{
	setlocale(LC_ALL, "polish");
	printTutorial();
	bool isRunning = true;
	bool resigned = false;
	int questionNumber = 0;
	const int questionAmount = 12;

	string questionBase[questionAmount][6];

	string line;
	ifstream questionBank("questions.txt");
	if (questionBank.is_open())
	{
		int questionsLoaded = 0;
		while (getline(questionBank, line))
		{
			int index = 0;
			string delim = ";";
			int start = 0;
			int end = line.find(delim);
			while (end != string::npos)
			{
				questionBase[questionsLoaded][index] = line.substr(start, end - start); //przypisanie do [0] pytania, do [1] - odp a, itd...
				start = end + delim.length();
				end = line.find(delim, start);
				index++; 
			}
			questionBase[questionsLoaded][index] = line.substr(start, end); // przypisanie do ostatnej komórki w tablicy prawid³owej odp
			questionsLoaded++;
		}
		questionBank.close();
	}

	else cout << "Nie uda³o siê otworzyæ pliku :(";


	int prices[questionAmount] = { 500, 1000, 2000, 5000, 10000, 20000, 40000, 75000, 125000, 250000, 500000, 1000000 };
	bool win = false;


	while (isRunning && !resigned) {
		cout << "Pytanie " << questionNumber + 1 << "/" << questionAmount << " za " << prices[questionNumber] << " z³. \n" << endl;
		int controlNumber = question(questionBase[questionNumber]);
		switch (controlNumber) {
		case 1:
			cout << "\n-----------Poprawna Odpowiedz-----------\n" << endl;
			questionNumber++;
			if (questionNumber == questionAmount) {
				isRunning = false;
			}
			break;
		case 0:
			isRunning = false;
			cout << "\n-----------B³êdna odpowiedŸ----------- \n" << endl;
			break;
		case -1:
			if (questionNumber > 0) {
				resigned = true;
				cout << "\n-----------Zrezygnowano z pytania----------- \n"  << endl;
			}
			else {
				cout << "\n Nie mo¿na zrezygnowaæ z tego pytania \n" << endl;
			}
			break;
		}

	}
	int wonPrice;
		if (resigned) {
			wonPrice = prices[questionNumber - 1];
		} else if (questionNumber == questionAmount) {
			wonPrice = prices[questionNumber - 1];
		} else if (questionNumber > 6) {
			wonPrice = prices[6];
		} else if (questionNumber > 1) {
			wonPrice = prices[1];
		} else {
			wonPrice = 0;
		}
		cout << "\nOdpowiedziano na " << questionNumber << " pytañ z " << questionAmount << endl;
		cout << "\nWygra³eœ " << wonPrice<< " z³"<< endl;
		cout << "\n-------------------------------------------- \n" << endl;
		return 0;
	}



