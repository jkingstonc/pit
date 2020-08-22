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
		case Instruction::HLT:
			return no_arg("HLT", offset);
		case Instruction::LD_I_IMM:
			return one_arg("LD_I_IMM", offset);
		case Instruction::LD_B_IMM:
			return one_arg("LD_B_IMM", offset);
		case Instruction::LD_CONST:
			return one_arg("LD_CONST", offset);
		case Instruction::RET:
			return no_arg("RET", offset);
		case Instruction::NEG:
			return no_arg("NEG", offset);
		case Instruction::ADD:
			return no_arg("ADD", offset);
		case Instruction::SUB:
			return no_arg("SUB", offset);
		case Instruction::MUL:
			return no_arg("MUL", offset);
		case Instruction::DIV:
			return no_arg("DIV", offset);
		case Instruction::NOT:
			return no_arg("NOT", offset);
		case Instruction::EQ:
			return no_arg("EQ", offset);
		case Instruction::GT:
			return no_arg("GT", offset);
		case Instruction::LT:
			return no_arg("LT", offset);
		case Instruction::GE:
			return no_arg("GE", offset);
		case Instruction::LE:
			return no_arg("LE", offset);
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