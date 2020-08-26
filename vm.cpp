#include "vm.hpp"

namespace pit {
	VM::VM(){
		job_pool = JobPool();
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
			switch (instr) {
				case Instruction::OP_HLT: return ExecutionResult::EXEC_OK;
				case Instruction::OP_LD_I_IMM: {
					uint8_t immediate = next_instr();
					push(Value::num_val(immediate));
					break;
				}
				case Instruction::OP_LD_B_IMM: {
					uint8_t immediate = next_instr();
					push(Value::bool_val(immediate ? true : false));
					break;
				}
				case Instruction::OP_LD_CONST: {
					uint8_t pool_index = next_instr();
					Value constant = bundle.constant_pool.at(pool_index);
					push(constant);
					break;
				}
				case Instruction::OP_NEW_BUNDLE:
				{
					// get the index into the constant pool
					uint8_t pool_index = next_instr();
					// get the constant bundle located in the constant pool (this is a BundleRef value)
					Value bundle_ref = bundle.constant_pool.at(pool_index);
					// push it to the stack
					push(bundle_ref);
					break;
				}
				case Instruction::OP_NEW_CONT:
				{
					// get the size of the container
					uint8_t length = next_instr();
					// get the initialisation values
					std::vector<Value> init_values = std::vector<Value>(length);
					for (int i = 0; i < length; i++)
						init_values.push_back(pop());
					//auto container_ref = Value::container_value(length, init_values);
					//push(container_ref);
					break;
				}
				case Instruction::OP_RET:{
					/*
					We need to check the jobpool to see if there are any jobs ready to be ran on the VM.
					*/
					return ExecutionResult::EXEC_OK;
				}
				case Instruction::OP_YIELD: break;
				case Instruction::OP_NEG: {
					if (!peek(0).is_num()) {
						return runtime_err(std::string("cannot negate non-numeric value"));
					}
					push(Value::num_val(-pop().as_num()));
					break;
				}

				case Instruction::OP_NOT: {
					if (!peek(0).is_bool()) {
						return runtime_err(std::string("cannot not non-boolean value"));
					}
					push(Value::bool_val(!pop().as_bool()));
					break;
				}
				case Instruction::OP_ADD:
				case Instruction::OP_SUB:
				case Instruction::OP_MUL:
				case Instruction::OP_DIV:
				case Instruction::OP_GT:
				case Instruction::OP_LT:
				case Instruction::OP_GE:
				case Instruction::OP_LE:
				case Instruction::OP_EQ: {
					if (!binary_op((Instruction)instr))
						return runtime_err(std::string("cannot apply operator non-numeric values"));
					break;
				}
			}
#ifdef DEBUG_EXEC_STACK
			debug_exec_stack();
#endif
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

		// check if the left is a container ref and has an overload
		if(peek(0).is_container()){
			// if the left is a container, then check its key-values
		}

		switch (op) {
			case Instruction::OP_ADD: push(Value::num_val(pop().as_num() + pop().as_num())); break;
			case Instruction::OP_SUB: push(Value::num_val(pop().as_num() - pop().as_num())); break;
			case Instruction::OP_MUL: push(Value::num_val(pop().as_num() * pop().as_num())); break;
			case Instruction::OP_DIV: push(Value::num_val(pop().as_num() / pop().as_num())); break;
			case Instruction::OP_GT: push(Value::bool_val(pop().as_num() > pop().as_num())); break;
			case Instruction::OP_LT: push(Value::bool_val(pop().as_num() < pop().as_num())); break;
			case Instruction::OP_GE: push(Value::bool_val(pop().as_num() >= pop().as_num())); break;
			case Instruction::OP_LE: push(Value::bool_val(pop().as_num() <= pop().as_num())); break;
			case Instruction::OP_EQ: push(Value::bool_val(pop().equals(pop()))); break;
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
