#pragma once
#include <cstdint>
#include <string>
#include <sstream>

namespace pit {
	enum TokenType {
		// grammar
		TOK_LEFT_BRACKET,
		TOK_RIGHT_BRACKET,
		TOK_LEFT_PAREN,
		TOK_RIGHT_PAREN,
		TOK_LEFT_CURLY,
		TOK_RIGHT_CURLY,
		TOK_DOT,
		TOK_COLON,
		TOK_SEMI_COLON,
		TOK_QUESTION,
		TOK_PLUS,
		TOK_MINUS,
		TOK_STAR,
		TOK_SLASH,

		TOK_ASSIGN,
		TOK_QUICK_ASSIGN,

		// variables
		TOK_IDENTIFIER,
		TOK_VAR,


		// bitwise
		TOK_BAND,
		TOK_BOR,

		// logical
		TOK_BANG,
		TOK_LAND,
		TOK_LOR,
		TOK_EQ,
		TOK_LT,
		TOK_GT,
		TOK_LE,
		TOK_GE,
		TOK_NE,
		
		// control flow
		IF,
		ELSE,
		LOOP,
		MATCH,
		RET,
		IN,

		TOK_EOF
	};



	struct Position {
		Position(){}
		Position(uint32_t indent, uint32_t line) : indent(indent), line(line){}
		uint32_t indent;
		uint32_t line;
	};

	struct Token {

		Token(TokenType tok, Position pos) : tok(tok), pos(pos){}
		Token(TokenType tok, std::string value, Position pos) : tok(tok), value(value), pos(pos) {}

		TokenType tok;
		Position pos;
		std::string value;

		std::string lexme() {
			std::ostringstream ss;
			ss << "tok: " << lexmes[tok];
			return ss.str();
		}

		static const char* lexmes[];
	};
}