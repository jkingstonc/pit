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
				case Instruction::HLT: return ExecutionResult::EXEC_OK;
				case Instruction::LD_I_IMM: {
					uint8_t immediate = next_instr();
					push(Value::num_val(immediate));
					break;
				}
				case Instruction::LD_B_IMM: {
					uint8_t immediate = next_instr();
					push(Value::bool_val(immediate ? true : false));
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
						return runtime_err(std::string("cannot negate non-numeric value"));
					}
					push(Value::num_val(-pop().as_num()));
					break;
				}

				case Instruction::NOT: {
					if (!peek(0).is_bool()) {
						return runtime_err(std::string("cannot not non-boolean value"));
					}
					push(Value::bool_val(!pop().as_bool()));
					break;
				}
				case Instruction::ADD:
				case Instruction::SUB:
				case Instruction::MUL:
				case Instruction::DIV:
				case Instruction::EQ: {
					if (!binary_op((Instruction)instr))
						return runtime_err(std::string("cannot apply operator non-numeric values"));
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


	inline bool VM::binary_op(Instruction op) {
		if (!(peek(0).is_num() && peek(1).is_num())) 
			return false;
		switch (op) {
		case Instruction::ADD: push(Value::num_val(pop().as_num() + pop().as_num())); break;
		case Instruction::SUB: push(Value::num_val(pop().as_num() - pop().as_num())); break;
		case Instruction::MUL: push(Value::num_val(pop().as_num() * pop().as_num())); break;
		case Instruction::DIV: push(Value::num_val(pop().as_num() / pop().as_num())); break;
		case Instruction::GT: push(Value::bool_val(pop().as_num() > pop().as_num())); break;
		case Instruction::LT: push(Value::bool_val(pop().as_num() < pop().as_num())); break;
		case Instruction::GE: push(Value::bool_val(pop().as_num() >= pop().as_num())); break;
		case Instruction::LE: push(Value::bool_val(pop().as_num() <= pop().as_num())); break;
		case Instruction::EQ: push(Value::bool_val(pop().as_num() == pop().as_num())); break;
		}
		return true;
	}

	ExecutionResult VM::runtime_err(std::string msg){
		int line_ptr = (int)((instr_ptr - 1) - bundle.code.data());
		uint32_t line = bundle.lines[line_ptr];
		std::cout << "Runtime Error [line " << line << "]\n" << msg << std::endl;
		return ExecutionResult::EXEC_RUNTIME_ERR;
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
