#pragma once

#include "parse.hpp"
#include "lex.hpp"

namespace pit {

	enum class CompileResult {
		COMP_OK,
		COMP_ERR
	};

	class Compiler{
	public:
		CompileResult compile();
	private:
	};
}