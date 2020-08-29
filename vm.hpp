#pragma once
#include "bundle.hpp"
#include "instruction.hpp"
#include "value.hpp"
#include "job.hpp"
#include "frame.hpp"
#include <stack>

#define DEBUG_EXEC_INSTR
#define DEBUG_EXEC_STACK
#define EXEC_STACK_SIZE 256

/*
this file actually runs the 'cyanide' virtual machine
*/

namespace pit {

	enum ExecutionResult {
		EXEC_OK,			// when an instruction successfully completes operation
		EXEC_RUNTIME_ERR,   // when there is a VM runtime error
		EXEC_COMPLETE,      // when the vm successfully completes operation
	};

	class VM {
	public:
		VM();
		ExecutionResult run();
		ExecutionResult step();

		JobPool job_pool;
		uint8_t call_stack_ptr;

		CallFrame* current_frame;

		CallFrame call_stack[CALL_FRAME_SIZE];
		Value exec_stack[EXEC_STACK_SIZE];

		ExecutionResult runtime_err(std::string msg);

		void setup_internals(std::shared_ptr<Bundle> bundle);
		inline void debug_exec_stack();
		inline void debug_traceback();

		inline int instr_ptr_offset();
		inline int stack_ptr_offset();
		inline bool binary_op(Instruction op);
		inline uint8_t next_instr();
		inline uint8_t get_ubyte();
		inline int8_t get_sbyte();
		inline void push(Value value);
		inline Value pop();
		inline Value peek(uint8_t offset);
		inline void push_frame(CallFrame frame);
		inline void pop_frame();
		inline CallFrame* peek_frame(uint8_t offset);
		inline std::shared_ptr<Bundle> current_bundle();
	};
}