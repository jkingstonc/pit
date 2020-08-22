#include "vm.hpp"

namespace pit {
	VM::VM(){
		
	}

	ExecutionResult VM::run(Bundle bundle){
		std::cout << "running VM" << std::endl;


		this->bundle = bundle;

		setup_internals();

		for (;;) {
#ifdef DEBUG_EXEC_INSTR
			this->bundle.disassemble_instruction((int)(instr_ptr - this->bundle.code.data()));
#endif
			uint8_t instr = next_instr();
			switch (instr){
				case Instruction::LD_IMM: {
					uint8_t immediate = next_instr();
					Value value = Value::num_val(immediate);
					std::cout << "immediate: " << value.data.num << std::endl;
					break;
				}
				case Instruction::LD_CONST: {
					uint8_t pool_index = next_instr();
					Value constant = bundle.constant_pool.at(pool_index);
					std::cout << "constant: " << (int)constant.as_num() << std::endl;
					push(constant);
					break;
				}
				case Instruction::RET:
					return ExecutionResult::EXEC_OK;
				case Instruction::NEG: {
					if (!peek(0).is_num()) {
						runtime_err(std::string("cannot negate non-numeric value"));
						return ExecutionResult::EXEC_RUNTIME_ERR;
					}
					push(Value::num_val(-pop().as_num()));
				}
				case Instruction::ADD: {}
				case Instruction::SUB: {}
				case Instruction::MUL: {}
				case Instruction::DIV: {}
			}
		}
	}


	void VM::runtime_err(std::string msg){
		std::cout << "runtime error [" << bundle.lines[(int)((instr_ptr-1) - bundle.code.data())] << "] " << msg << std::endl;
	}


	void VM::setup_internals(){
		instr_ptr = bundle.code.data();
		exec_stack_ptr = 0;
	}

	inline uint8_t VM::next_instr(){
		return (*instr_ptr++);
	}
	inline void VM::push(Value value){
		exec_stack[exec_stack_ptr++] = value;
	}
	inline Value VM::pop(){
		return exec_stack[--exec_stack_ptr];
	}
	inline Value VM::peek(uint8_t offset){

		return exec_stack[exec_stack_ptr - offset -1];
	}
}
