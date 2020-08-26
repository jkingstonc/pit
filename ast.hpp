#pragma once

namespace pit {

	/*
	The type of the node inside the ast (e.g. literal value, function call etc)
	*/
	enum class NodeType {
		AST_LITERAL,
		AST_EXPR_STATEMENT, // e.g. 1+2 * variable
		AST_UNARY,
		AST_BIN,

		AST_ROOT,
		AST_ASSIGN,
		AST_QUICK_ASSIGN,
		AST_IF,
		AST_LOOP
	};

	class AST {
	public:
		NodeType type;
		virtual std::string debug() {
			return std::string("I am a base AST node!");
		}
	private:
	};

	/*
	An expression resolves to a value
	*/
	class Expression : public AST{};


	/*
	A statement does not resolve to a value
	*/
	class Statement : public AST {};


	class ASTRoot : public Statement{
	public:
		std::string debug() {
			return std::string("I am the root AST!");
		}
	private:
	};
}