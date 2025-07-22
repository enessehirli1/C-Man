#include "Session.h"
#include <iostream>


void Session::pushGuesses(char c)
{
	bool alreadyGuessed{false};
	for (const auto& e : m_guesses)
	{
		if (e == c)
		{
			std::cout << "You already guessed '" << c << "'\n";
			alreadyGuessed = true;
		}
	}

	if (!alreadyGuessed)
	{
		m_guesses.push_back(c);
	}
}