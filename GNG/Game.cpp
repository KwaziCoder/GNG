#include <iostream>
#include <cstdlib>
#include <ctime>


enum class Result
{
	TOO_HIGH,
	EXACT,
	TOO_LOW,
	WIN,
	FAIL,
};


int getRandomNumber()
{	
	int min{ 0 };
	int max{ 100 };

	srand(static_cast<unsigned int>(time(0)));
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	// Равномерно распределяем рандомное число в нашем диапазоне
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);	
}


int getTry() {
	int guess;

	while (true)
	{
		std::cin >> guess;

		if (std::cin.fail()) 
		{
			std::cin.clear(); 
			std::cin.ignore(32767, '\n'); 
			std::cout << "You must enter an integer!";
		}
		else
		{
			std::cin.ignore(32767, '\n');
			return guess;
		}
	}	

}


Result checkAnswer(int randNum, int guess)
{
	if (randNum == guess)
		return Result::EXACT;
	else if (randNum < guess)
		return Result::TOO_HIGH;
	else
		return Result::TOO_LOW;
}



bool checkRecord(int score, int record)
{
	return score > record;
}


void congratulateWithNewRecord(bool newRecord, int record)
{
	if (newRecord)
	{
		std::cout << "Congratulations! You set up a new record!" << std::endl;
	} 
	else
	{
		std::cout << "Your best result : " << record << std::endl;
	}
}


void printResult(Result result, int score, int record)
{
	if (result == Result::WIN)
		std::cout << "Correct! You win! Your score: " << score << std::endl;
	else
	{
		std::cout << "Sorry, you lose! Your score: " << score << std::endl;
		congratulateWithNewRecord(checkRecord(score, record), record);
	}

	std::cout << "Would you like to play again? (Y/N)  ";

}



bool StartNewOrExit(Result result, int score, int record)
{
	printResult(result, score, record);

	char answer;

	while (true) {

		std::cin >> answer;

		if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
		{
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
			std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
			continue;
		}
		else
		{
			std::cin.ignore(32767, '\n'); // удаляем лишние значения
		}


		if (answer == 'y' || answer == 'Y')
			return true;
		else if (answer == 'n' || answer == 'N')
			return false;
		else
			std:: cout << "Would you like to play again? (Y/N)  ";
		
	}
			
}	


int main()
{
	using namespace std;

	cout << "Let's play a game!" << endl;
	cout << "I'm thinking about a number... " << std::endl << 
		"You have 7 tries to tell me what this number is." << std::endl;

	int randNum = getRandomNumber();
	
	cout << "What is your first thought?" << endl << 
		"Enter a number: ";


	int tries{ 7 };
	int score = 0;
	int record = 0;

	bool newGame = false;
	bool endOfGame = false;


	while (true)
	{
		if (tries == 0)
		{
			endOfGame = true;
			newGame = StartNewOrExit(Result::FAIL, score, record);
			record = (checkRecord(score, record)) ? score : record;
			score = 0;
		}
		else
		{
			int guess = getTry();
			Result result = checkAnswer(randNum, guess);

			switch (result)
			{
			case Result::EXACT:
				++score;
				endOfGame = true;
				newGame = StartNewOrExit(Result::WIN, score, record);
				break;
			case Result::TOO_HIGH:
				cout << "Your guess is too high." << endl << "Try again" << endl;
				--tries;
				break;
			case Result::TOO_LOW:
				cout << "Your guess is too low." << endl << "Try again" << endl;
				--tries;
				break;

			}
		}

		if (endOfGame)
		{
			if (newGame)
			{
				endOfGame = false;
				tries = 7;
				cout << "I'm thinking about a number... " << std::endl
					<< "You have 7 tries to tell me what this number is." << std::endl;
				randNum = getRandomNumber();
				
			}
			else
			{
				cout << "Thanks for playing!" << endl;
				exit(0);
			}
		}
		
	}
	

	return 0;
}