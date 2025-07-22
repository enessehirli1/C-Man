#pragma once
#include <string>
#include <vector>
#include <iostream>

class Session
{
private:
	std::string m_randomWord{};
	std::vector<char> m_guessedLetters{};
	int m_lives{ 10 };

public:
	Session(std::string_view randomWord)
		: m_randomWord{ randomWord } {}


	

	std::vector<char> getGuessedLetters() const { return m_guessedLetters; }	
	std::string_view getRandomWord() const { return m_randomWord; }
	int getLives() const { return m_lives; }

	void pushGuessedLetter(char letter);
	void draw();

	bool isLetterInWord(char c) const
	{
		for (auto ch : m_randomWord) // step through each letter of word
		{
			if (ch == c)
				return true;
		}

		return false;
	}

};