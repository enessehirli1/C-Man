#include <iostream>
#include <vector>
#include <cassert>
#include <utility>
#include "Random.h"
#include "Session.h"

namespace WordList
{
	std::vector<std::string_view> words{ "mystery", "broccoli", "account", "almost", "spaghetti",
										"opinion", "beautiful", "luggage"};

	std::string_view getRandomWord()
	{
		return words[static_cast<std::size_t>(Random::get(0, static_cast<int>(std::ssize(words) - 1)))];
	}
}

char getChar()
{
    while (true)
    {
        std::cout << "Enter your next letter: ";

        char c{};
        std::cin >> c;

        if (!std::cin)
        {
            // Fix it
            std::cin.clear();
            std::cout << "That wasn't a valid input.  Try again.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Clear out any extraneous input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // If the user entered an invalid char, try again
		if (c >= 'A' && c <= 'Z')
		{
			return static_cast<char>(c + 32); // Convert to lowercase
		}
        if (c < 'a' || c > 'z')
        {
            std::cout << "That wasn't a valid input.  Try again.\n";
            continue;
        }

        return c;
    }
}


bool checkWin(std::string_view word, const std::vector<char>& ch)
{
	// Önce tahmin edilen harflerin sayısını kontrol edelim
	if (ch.empty())
		return 0;

	bool wordFound{ true };

	// Her harf için kontrol yapalım
	for (const auto& letter : word)
	{
		bool letterFound{ false };
		// Tahmin edilen harfler arasında var mı diye bakalım
		for (const auto& guess : ch)
		{
			if (letter == guess)
			{
				letterFound = true;
				break;
			}
		}

		if (!letterFound)
		{
			wordFound = false;
			break;
		}
	}

	if (wordFound)
	{
		std::cout << "You win! The word was: " << word << '\n';
		return true;
	}

	return false;
}



int main()
{
	bool control{ false };
	std::cout << "Welcome to C++man (a variant of Hangman)\n";
	std::cout << "To win: guess the word.  To lose: run out of pluses.\n";
	Session session{WordList::getRandomWord()};
	session.draw();
	while (session.getLives() > 0)
	{
		char letter{ getChar() };
		session.pushGuessedLetter(letter);
		session.draw();
		if (checkWin(session.getRandomWord(), session.getGuessedLetters()))
		{
			control = true;
			break;
		}

	}

	if (!control)
	{
		std::cout << "You lose! The word was: " << session.getRandomWord() << '\n';
	}


	return 0;
}





















/*
namespace Game
{
	enum Items
	{
		healthPotions,
		torchs,
		arrows,

		MAX_ITEMS
	};

	std::vector<int> numItems{ 1, 5, 10 };
}

int printTotal(const std::vector<int>& arr)
{
	int total{ 0 };
	for (const auto& i : arr)
		total += i;

	return total;
}

std::string_view getItemName(Game::Items item)
{
	switch (item)
	{
	case (Game::healthPotions): return "Health Potions";
	case (Game::torchs):	    return "Torchs";
	case (Game::arrows):		return "Arrows";
	default:					return "Unknown Item";
	}
}

void printInventory(const std::vector<int> arr, bool total = false)
{
	for (size_t i{ 0 }; i < arr.size(); i++)
	{
		std::cout << "You have " << arr[i] << " " << getItemName(static_cast<Game::Items>(i)) << '\n';
	}

	if (total)
	{
		std::cout << "You have total " << printTotal(arr) << " items\n";
	}
}


int main()
{
	assert(Game::MAX_ITEMS == std::ssize(Game::numItems) && "The length of num items and max items must be same");

	printInventory(Game::numItems, true);
}

template<typename T>
std::pair<std::size_t, std::size_t> findMinMaxPair(const std::vector<T>& arr)
{
	std::size_t size{ arr.size() };

	std::size_t minIndex{ 0 };
	std::size_t maxIndex{ 0 };

	for (std::size_t index {1}; index < size; index++)
	{
		if (arr[index] < arr[minIndex])
			minIndex = index;
		if (arr[index] > arr[maxIndex])
			maxIndex = index;
	}

	return { minIndex, maxIndex };
}


template <typename T>
void printArray(const std::vector<T>& vec)
{
	bool comma{ false };

	std::cout << "With Array ( ";
	for (const auto& i : vec)
	{
		if (comma)
			std::cout << ", ";

		std::cout << i;
		comma = true;
	}

	std::cout << " ):\n";
}

template <typename T>
std::vector<T> getVector()
{
	std::vector<T> vec{};


	std::cout << "Enter numbers to add (use -1 to stop): ";
	do
	{
		T input{};
		std::cin >> input;

		if (input == -1)
			break;

		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		vec.push_back(input);
	} while (true);

	return vec;
}


int main()
{
	std::vector v1{ getVector<int>()};
	printArray(v1);

	auto m1{ findMinMaxPair(v1) };
	std::cout << "The min element has index " << m1.first << " and value " << v1[m1.first] << '\n';
	std::cout << "The max element has index " << m1.second << " and value " << v1[m1.second] << '\n';

	std::cout << '\n';

	std::vector v2{getVector<double>()};
	printArray(v2);

	auto m2{ findMinMaxPair(v2) };
	std::cout << "The min element has index " << m2.first << " and value " << v2[m2.first] << '\n';
	std::cout << "The max element has index " << m2.second << " and value " << v2[m2.second] << '\n';


	return 0;
}

*/
