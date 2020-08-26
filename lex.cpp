#include "lex.hpp"

namespace pit {

	const char* Token::lexmes[] = {"[","]","(",")","{","}",
	".", ":", ";", "?", "+", "-", "*", "/", "=", ":=", "identifier", "var",
	"&", "|", "!", "and", "or", "==", "<", ">", "<=", ">=", "!=",
	"if", "else", "loop", "match", "ret", "in"};

	Lexer::Lexer() {
		current = 0;
		pos = Position(1,1);
	}

	LexResult Lexer::lex(std::string src, std::shared_ptr<std::vector<Token>> tokens) {
		this->src = src;
		this->tokens = tokens;
		for (int i = 0; i < src.length(); i++) {
			auto c = next();
			while (is_whitespace(c))
				c = next();
			switch (c) {
			case '\n': pos.line++; pos.indent = 1; break;
			case '[': token(TOK_LEFT_BRACKET); break;
			case ']': token(TOK_RIGHT_BRACKET); break;
			case '(': token(TOK_LEFT_PAREN); break;
			case ')': token(TOK_RIGHT_PAREN); break;
			case '{': token(TOK_LEFT_CURLY); break;
			case '}': token(TOK_RIGHT_CURLY); break;
			default: break;
			}
		}
#ifdef DEBUG_LEX_TOKENS
		for (auto t : *tokens)
			std::cout << t.lexme() << std::endl;
#endif
		return LexResult::LEX_OK;
	}

	inline char Lexer::next(){
		pos.indent++;
		return src.at(current++);
	}
	inline char Lexer::peek(){
		return src.at(current);
	}

	inline bool Lexer::is_whitespace(char c) {
		return c == ' ' || c == '\t' || c == '\f' || c == '\v';
	}

	inline void Lexer::token(TokenType token) {
		tokens->push_back(Token(token, pos));
	}

	inline void Lexer::token(TokenType token, std::string value) {
		tokens->push_back(Token(token, value, pos));
	}
}