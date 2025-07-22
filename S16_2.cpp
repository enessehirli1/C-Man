#include <iostream>
#include <vector>
#include <cassert>
#include <utility>
#include "Random.h"
#include "Session.h"

namespace WordList
{
	std::vector<std::string_view> words{ "school", "car", "zeplin", "fault", "breakfast", "pizza" };

	std::string_view getRandomWord()
	{
		assert(!words.empty());
		return words[static_cast<size_t>(Random::get(0, static_cast<int>(std::ssize(words) -1)))];
	}
}

char getValidChar()
{
	char c{};
	while (true)
	{
		std::cout << "Enter your next guess: ";
		std::cin >> c;

		if (!std::cin)
		{
			std::cin.clear();
			// clear the error state
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
			continue;
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (std::isalpha(c))
		{
			return static_cast<char>(std::tolower(c));
		}
		else
		{
			std::cout << "Please enter a valid letter.\n";
		}
	}
}

void printLefted(Session& game)
{
	const static int lives{ game.getLives() };
	for (int index{0}; index < lives - std::ssize(game.getWrongGuesses()); index++)
	{
		std::cout << "+";
	}

	for (const auto& e : game.getWrongGuesses())
	{
		std::cout << e;
	}
}

void draw(Session& game)
{
	std::cout << "The word is: ";
	for (const auto& c : game.getWord())
	{
		bool found{ false };
		for (size_t index{0}; index < game.getGuesses().size(); index++)
		{
			if (c == game.getGuesses()[index])
			{
				found = true;
				std::cout << c;
			}
		}
		if (!found)
		{
			std::cout << '_';
		}
			
	}

	std::cout << "   | Lives left: " ; //game.getLives()
	printLefted(game);
	std::cout << '\n';
}

void checkWin(const Session& game)
{
	bool won{ true };
	for (const auto& e: game.getWord())
	{
		bool found{ false };
		for (const auto& c : game.getGuesses())
		{
			if (e == c)
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			won = false;
			break;
		}
	}

	if (won)
	{
		std::cout << "Congratulations! You guessed the word: " << game.getWord() << "\n";
		exit(0);
	}
	else if (game.getLives() <= 0)
	{
		std::cout << "Game over! The word was: " << game.getWord() << "\n";
		exit(0);
	}
}

void playGame(Session& game)
{
	std::cout << "Welcome to Hangman in C++\n";

	while (game.getLives())
	{
		draw(game);
		char input{ getValidChar() };
		bool notFound{ false };
		for (const auto e : game.getWord())
		{
			if (input == e)
			{
				notFound = true;
				break;
			}
		}
		if (!notFound)
		{
			game.decrementLives();
			game.pushWrongGuesses(input);
		}
		game.pushGuesses(input);
		checkWin(game);
	}
}


int main()
{
	Session game{ WordList::getRandomWord() };
	playGame(game);

	
	return 0;
}