#pragma once
#include "bundle.hpp"
#include "instruction.hpp"
#include "value.hpp"
#include "job.hpp"
#include <stack>

#define DEBUG_EXEC_INSTR
#define EXEC_STACK_SIZE 256

/*
this file actually runs the 'cyanide' virtual machine
*/

namespace pit {

	enum ExecutionResult {
		EXEC_OK,
		EXEC_RUNTIME_ERR,
	};

	class VM {
	public:
		VM();
		ExecutionResult run(Bundle bundle);
	private:

		JobPool job_pool;

		Bundle bundle;
		uint8_t*instr_ptr;

		Value exec_stack[EXEC_STACK_SIZE];
		uint8_t exec_stack_ptr;

		ExecutionResult runtime_err(std::string msg);

		void setup_internals();
		inline void debug_exec_stack();

		inline int instr_ptr_offset();
		inline int stack_ptr_offset();
		inline bool binary_op(Instruction op);
		inline uint8_t next_instr();
		inline void push(Value value);
		inline Value pop();
		inline Value peek(uint8_t offset);
	};
}