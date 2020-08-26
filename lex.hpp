#pragma once

#include <vector>
#include <iostream>
#include "token.hpp"


#define DEBUG_LEX_TOKENS

namespace pit {

	enum class LexResult {
		LEX_OK,
		LEX_ERR,
	};

	class Lexer{
	public:
		Lexer();
		LexResult lex(std::string src, std::shared_ptr<std::vector<Token>> tokens);
		std::string src;
	private:
		std::shared_ptr<std::vector<Token>> tokens;
		Position pos;
		uint32_t current;
		inline char next();
		inline char peek();
		inline bool is_whitespace(char c);
		inline void token(TokenType token);
		inline void token(TokenType token, std::string value);
	};
}