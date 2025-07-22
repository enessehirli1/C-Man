#include "Session.h"
#include <iostream>

void Session::draw()
{
	std::cout << "\nThe word: ";
	int length{ static_cast<int>(m_randomWord.length()) };

	for (size_t t{ 0 }; t < length; t++)
	{
		bool found{ false };
		for (const auto& i : m_guessedLetters)
		{
			if (m_randomWord[t] == i)
			{
				std::cout << m_randomWord[t];
				found = true;
			}
		}
		if (!found)
		{
			std::cout << '_';
		}
		else
		{
			std::cout << "";
		}
	}

	std::cout << " | Lives: " << m_lives << '\n';
}

void Session::pushGuessedLetter(char letter)
{
	bool found{ false };

	for (const auto& i : m_guessedLetters)
	{
		if (i == letter)
		{
			std::cout << "You already guessed that letter: " << letter << '\n';
			found = true;
		}
	}

	if (!found)
	{
		m_lives -= 1;
		m_guessedLetters.push_back(letter);
	}
}


