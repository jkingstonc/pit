#include "bundle.hpp"

namespace pit {

	Bundle::Bundle(){
		constant_pool = std::vector<Value>();
		locals = std::vector<Value>();
		code = std::vector<uint8_t>();
	}

	Bundle::Bundle(std::string file) {
		constant_pool = std::vector<Value>();
		locals = std::vector<Value>();
		code = std::vector<uint8_t>();
	}
	
	void Bundle::write_instr(uint8_t instr, uint32_t line) {
		code.push_back(instr);
		lines.push_back(line);
	}

	void Bundle::write_constant(Value value) {
		constant_pool.push_back(value);
	}

	void Bundle::disassemble() {
		std::cout << "disassembling bundle" << std::endl;
		uint32_t offset = 0;
		while (offset < code.size()) {
			offset+=(1+disassemble_instruction(offset));
		}
	}

	uint32_t Bundle::disassemble_instruction(uint32_t offset) {
		int32_t instr = code.at(offset);
		switch (instr){
		case Instruction::LD_IMM:
			return one_arg("LD_IMM", offset);
		case Instruction::LD_CONST:
			return two_args("LD_CONST", offset);
		case Instruction::RET:
			return no_arg("RET", offset);
		default:
			std::cout << "unknown opcode" << std::endl;
			return 0;
		}
		return 0;
	}

	void Bundle::to_file(std::string filename){}

	inline int Bundle::no_arg(std::string instr, uint32_t offset) {
		std::cout << lines.at(offset) << ": " << instr << std::endl;
		return 0;
	}

	inline int Bundle::one_arg(std::string instr, uint32_t offset) {
		std::cout << lines.at(offset) << ": " << instr << " " << unsigned(code.at(offset + 1)) << std::endl;
		return 1;
	}

	inline int Bundle::two_args(std::string instr, uint32_t offset) {
		std::cout << lines.at(offset) << ": " << instr << " " << unsigned(code.at(offset + 1)) << ", " << unsigned(code.at(offset + 2)) << std::endl;
		return 2;
	}
}