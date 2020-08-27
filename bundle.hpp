#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include "value.hpp"
#include "instruction.hpp"
/*
a bundle represents a compiled pit program/module.
the bundle can be written to a file or passed to the runtime.
*/

namespace pit {
	class Bundle {
	public:
		Bundle();
		Bundle(std::string file);
		void write_instr(uint8_t instr, uint32_t line);
		void write_constant(Value value);
		void to_file(std::string filename);
		void disassemble();
		uint32_t disassemble_instruction(uint32_t offset);
		// constants
		std::vector<Value> constant_pool;
		// locals
		std::vector<Value> locals;
		// code
		std::vector<uint8_t> code;
		// lines corresponding to bytecode
		std::vector<uint32_t> lines;
	private:
		inline int no_arg(std::string instr, uint32_t offset);
		inline int one_arg(std::string instr, uint32_t offset);
		inline int two_args(std::string instr, uint32_t offset);
	};
}