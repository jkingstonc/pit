#include "vm.hpp"

namespace pit {

	VM::VM() {
		call_stack_ptr = 0;
	}


	ExecutionResult VM::run(){
		ExecutionResult result;
		do {
			result = step();
		} while (result == ExecutionResult::EXEC_OK);
		return result;
	}

	ExecutionResult VM::step(){
#ifdef DEBUG_EXEC_INSTR
		call_stack[call_stack_ptr-1].running_ref_fn->bundle->disassemble_instruction((int)(call_stack[call_stack_ptr-1].instr_ptr - current_bundle()->code.data()));
#endif
		uint8_t instr = next_instr();
		switch (instr) {
		case Instruction::OP_DBG: {
			debug_exec_stack(); 
			break; 
		}
		case Instruction::OP_HLT: return ExecutionResult::EXEC_COMPLETE;
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
			Value constant = current_bundle()->constant_pool.at(pool_index);
			push(constant);
			break;
		}
		case Instruction::OP_LD_LOCAL: {
			auto internal_index = next_instr(); // the index inside the frame 
			auto frame_index = next_instr(); // the frame index
			auto frame = peek_frame(frame_index);
			// now we have the frame, we can use the base_sp to access the stack address
			auto local = exec_stack[frame->sp_base + internal_index];
			push(local);
			break;
		}
		case Instruction::OP_ST_LOCAL: {
			auto internal_index = next_instr(); // the index inside the frame 
			auto frame_index = next_instr(); // the frame index
			auto frame = peek_frame(frame_index);
			// now we have the frame, we can use the base_sp to access the stack address
			exec_stack[frame->sp_base + internal_index] = pop();
			break;
		}
		case Instruction::OP_JMP: {
			auto jmp_offset = get_sbyte();
			auto condition = pop();
			std::cout << "jumping to offset " << (int)jmp_offset << " value " << condition.debug() << std::endl;
			if (condition.as_bool()) {
				current_frame->instr_ptr += jmp_offset;
			}
			break;
		}
		case Instruction::OP_NEW_FN:
		{
			// get the index into the constant pool
			uint8_t pool_index = next_instr();
			// get the constant fn located in the constant pool (this is a RefFN value)
			Value fn_ref = current_bundle()->constant_pool.at(pool_index);
			// push it to the stack
			push(fn_ref);
			break;
		}
		case Instruction::OP_NEW_CONT:
		{
			// get the size of the container
			uint8_t length = next_instr();
			// get the initialisation values
			std::vector<Value> init_values;
			init_values.reserve(length);
			for (int i = 0; i < length; i++)
				init_values.push_back(pop());
			auto container_ref = Value::container_value(length, init_values);
			push(container_ref);
			break;
		}
		case Instruction::OP_CALL: {
			/*
			Calling works by poping a function off the stack,
			creating a CallFrame and pushing that to the call stack.
			*/
			auto arg_count = next_instr();
			auto fn = pop();
			if(fn.is_fn()){
				// the new frame is being given an incorrect stack pointer!
				// we mark the base stack index as what the current frame has reached
				CallFrame new_frame(fn.as_fn(), current_frame->sp);
				push_frame(new_frame);
				break;
			}
			return runtime_err("callee must be a fn reference");
		}
		case Instruction::OP_RET: {
			/*
			Returning works by poping the top CallFrame from the call stack.
			NOTE: We need to check the jobpool to see if there are any jobs ready to be ran on the VM.
			NOTE: Implement return values.
			*/
			int return_amount = next_instr();
			std::vector<Value> ret_values;
			ret_values.reserve(return_amount);
			for (int i = 0; i < return_amount; i++) {
				ret_values.push_back(pop());
			}
			pop_frame();
			// the current frame sp here is wrong! it is 1 not 0
			for (auto value : ret_values)
				push(value);
			break;
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
		return ExecutionResult::EXEC_OK;
	}

	inline int VM::instr_ptr_offset() {
		return (int)((call_stack[call_stack_ptr-1].instr_ptr - 1) - current_bundle()->code.data());
	}

	inline int VM::stack_ptr_offset() {
		return current_frame->sp;
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
		int line_ptr = (int)((call_stack[call_stack_ptr-1].instr_ptr - 1) - current_bundle()->code.data());
		uint32_t line = current_bundle()->lines[line_ptr];
		std::cout << "Runtime Error [line " << line << "]\n" << msg << std::endl;
		debug_traceback();
		return ExecutionResult::EXEC_RUNTIME_ERR;
	}


	void VM::setup_internals(std::shared_ptr<Bundle> bundle){
		call_stack_ptr = 0;
		job_pool = JobPool();
		// we have to create a call frame for the main bundle
		auto main_fn = Value::fn_value("main_module", bundle, 0, 0).as_fn();
		CallFrame main_frame(main_fn, 0);
		push_frame(main_frame);
	}


	inline void VM::debug_exec_stack() {
		std::cout << "--stack--" << std::endl;
		for (int i = 0; i<current_frame->sp ; i++) {
			std::cout << i << " : " << peek(i).debug() << std::endl;
		}
		std::cout << "---------" << std::endl;
	}

	inline void VM::debug_traceback() {
		std::cout << "--traceback most recent call--" << std::endl;
		for (int i = 0; i < call_stack_ptr; i++)
			std::cout << "-> " << peek_frame(i)->running_ref_fn->name << std::endl;
	}

	inline uint8_t VM::next_instr(){
		return (*call_stack[call_stack_ptr - 1].instr_ptr++);
	}
	inline uint8_t VM::get_ubyte() {
		return next_instr();
	}
	
	inline int8_t VM::get_sbyte(){
		return get_ubyte()-127;
	}

	inline void VM::push(Value value){
		exec_stack[current_frame->sp++] = value;
	}
	inline Value VM::pop(){
		return exec_stack[--current_frame->sp];
	}
	inline Value VM::peek(uint8_t offset){

		return exec_stack[current_frame->sp - offset -1];
	}
	inline void VM::push_frame(CallFrame frame) {
		call_stack[call_stack_ptr++] = frame;
		current_frame = &call_stack[call_stack_ptr-1];
	}
	inline CallFrame* VM::peek_frame(uint8_t offset) {
		return &call_stack[call_stack_ptr - offset - 1];
	}
	inline void VM::pop_frame() {
		current_frame = &call_stack[call_stack_ptr--];
	}
	inline std::shared_ptr<Bundle> VM::current_bundle() {
		return call_stack[call_stack_ptr - 1].running_ref_fn->bundle;
	}
}
