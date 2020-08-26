#include "compiler.hpp"

namespace pit{
	CompileResult Compiler::compile() {

		Lexer lexer;
		Parser parser;

		std::shared_ptr<std::vector<Token>> tokens = std::make_shared<std::vector<Token>>();
		LexResult lex_result = lexer.lex(std::string("{}"), tokens);

		std::shared_ptr<AST> ast = std::make_shared<AST>();
		ParseResult parse_result = parser.parse(tokens, ast);

		return CompileResult::COMP_OK;
	}
}