#include "vm.hpp"

namespace pit {
	VM::VM(){
		call_stack = std::stack<Bundle>();
	}

	ExecutionResult VM::run(Bundle bundle){
		std::cout << "running VM" << std::endl;
		this->bundle = bundle;
		// push the bundle to the call stack
		call_stack.push(bundle);
		// get a pointer from the bundle code vector iterator
		instr_ptr = bundle.code.data();

		for (;;) {
			uint8_t instr = next_instr();
#ifdef DEBUG_EXEC_INSTR
			// debug the instruction here
#endif
			switch (instr){
			case Instruction::LD_IMM: {
				uint8_t immediate = next_instr();
				Value value = Value::to_value(immediate);
				std::cout << "immediate: " << value.data.num << std::endl;
				break;
			}
			case Instruction::LD_CONST: {
				uint8_t up_level = next_instr();
				uint8_t this_level = next_instr();
				Value constant = bundle.constant_pool.at(this_level);
				std::cout << "constant: " << constant.data.num << std::endl;
				break;
			}
			case Instruction::RET:
				return ExecutionResult::EXEC_OK;
			}
		}
	}

	inline uint8_t VM::next_instr(){
		return (*instr_ptr++);
	}
}
