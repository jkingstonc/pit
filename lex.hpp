#pragma once

#include <vector>
#include <iostream>
#include "token.hpp"

#define DEBUG_LEX_TOKENS

namespace pit {
	class Lexer{
	public:
		Lexer(std::string source);
		std::vector<Token> lex();
		std::string src;
		std::vector<Token> tokens;
	private:
		Position pos;
		uint32_t current;
		inline char next();
		inline char peek();
		inline bool is_whitespace(char c);
		inline void token(TokenType token);
		inline void token(TokenType token, std::string value);
	};
}