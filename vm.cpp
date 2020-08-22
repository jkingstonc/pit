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
					break;
				}
				case Instruction::ADD: {
					if (!peek(0).is_num()) {
						runtime_err(std::string("cannot add non-numeric values"));
						return ExecutionResult::EXEC_RUNTIME_ERR;
					}
					Value v1 = pop();
					Value v2 = pop();
					push(Value::num_val(BINARY(v1.as_num(), v2.as_num(), +)));
					break; 
				}
				case Instruction::SUB: {
					if (!peek(0).is_num()) {
						runtime_err(std::string("cannot add non-numeric values"));
						return ExecutionResult::EXEC_RUNTIME_ERR;
					}
					Value v1 = pop();
					Value v2 = pop();
					push(Value::num_val(BINARY(v1.as_num(), v2.as_num(), -)));
					break;
				}
				case Instruction::MUL: {
					if (!peek(0).is_num()) {
						runtime_err(std::string("cannot add non-numeric values"));
						return ExecutionResult::EXEC_RUNTIME_ERR;
					}
					Value v1 = pop();
					Value v2 = pop();
					push(Value::num_val(BINARY(v1.as_num(), v2.as_num(), *)));
					break;
				}
				case Instruction::DIV: {
					if (!peek(0).is_num()) {
						runtime_err(std::string("cannot add non-numeric values"));
						return ExecutionResult::EXEC_RUNTIME_ERR;
					}
					Value v1 = pop();
					Value v2 = pop();
					push(Value::num_val(BINARY(v1.as_num(), v2.as_num(), /)));
					break;
				}
			}

			debug_exec_stack();
		}
	}

	inline int VM::instr_ptr_offset() {
		return (int)((instr_ptr - 1) - bundle.code.data());
	}

	inline int VM::stack_ptr_offset() {
		return exec_stack_ptr;
	}


	void VM::runtime_err(std::string msg){
		int line_ptr = (int)((instr_ptr - 1) - bundle.code.data());
		uint32_t line = bundle.lines[line_ptr];
		std::cout << "Runtime Error [line " << line << "]\n" << msg << std::endl;
	}


	void VM::setup_internals(){
		instr_ptr = bundle.code.data();
		exec_stack_ptr = 0;
	}


	inline void VM::debug_exec_stack() {
		std::cout << "--stack--" << std::endl;
		for (int i = 0; i<exec_stack_ptr ; i++) {
			std::cout << i << " : " << peek(i).debug() << std::endl;
		}
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
