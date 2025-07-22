#pragma once
#include <string>
#include <vector>
#include <iostream>

class Session
{
private:
	std::string m_word{};
	std::vector<char> m_guesses{};
	std::vector<char> m_wrongGuesses{};
	int m_lives{ 9 };

public:
	Session(std::string_view word)
		    : m_word{ word } {}

	std::string_view getWord() const { return m_word; }
	std::vector<char> getGuesses() const { return m_guesses; }
	std::vector<char> getWrongGuesses() const { return m_wrongGuesses; };
	int getLives() const { return m_lives; }

	void pushGuesses(char c);

	void pushWrongGuesses(char c) {m_wrongGuesses.push_back(c);}
	void decrementLives() {m_lives -= 1;}
};