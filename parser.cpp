#include "parse.hpp"
#include <iostream>

namespace pit {
	ParseResult Parser::parse(std::shared_ptr<std::vector<Token>> tokens, std::shared_ptr<AST> ast){
		this->tokens = tokens;
		this->ast = ast;

		*ast = ASTRoot();
		std::cout << "debug: " << ast->debug() << std::endl;

		return ParseResult::PARSE_OK;
	}
}