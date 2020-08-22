#include "instruction.hpp"

inline int no_arg(pit::Bundle bundle, std::string instr, uint32_t offset) {
	std::cout << bundle.lines.at(offset) << ": " << instr << std::endl;
	return 0;
}

inline int one_arg(Bundle bundle, std::string instr, uint32_t offset) {
	std::cout << bundle.lines.at(offset) << ": " << instr << " " << unsigned(bundle.code.at(offset + 1)) << std::endl;
	return 1;
}

inline int two_args(Bundle bundle, std::string instr, uint32_t offset) {
	std::cout << bundle.lines.at(offset) << ": " << instr << " " << unsigned(bundle.code.at(offset + 1)) << ", " << unsigned(bundle.code.at(offset + 2)) << std::endl;
	return 2;
}

uint32_t disassemble_instruction(Bundle bundle, uint32_t offset) {
	int32_t instr = bundle.code.at(offset);
	switch (instr) {
	case Instruction::LD_IMM:
		return one_arg(bundle, "LD_IMM", offset);
	case Instruction::LD_CONST:
		return two_args(bundle, "LD_CONST", offset);
	case Instruction::RET:
		return no_arg(bundle, "RET", offset);
	default:
		std::cout << "unknown opcode" << std::endl;
		return 0;
	}
	return 0;
}