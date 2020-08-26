/*
Perhaps instead of a decent recursive LR parser, we instead try to write a Shift-Reduce parser
*/

#pragma once

#include <vector>

#include "token.hpp"
#include "ast.hpp"

namespace pit {

	enum class ParseResult {
		PARSE_OK,
		PARSE_ERR
	};

	class Parser {
	public:
		ParseResult parse(std::shared_ptr<std::vector<Token>> tokens, std::shared_ptr<AST> ast);
	private:
		std::shared_ptr<std::vector<Token>> tokens;
		std::shared_ptr<AST> ast;
	};
}