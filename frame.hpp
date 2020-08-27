#pragma once

#include "value.hpp"
#include "bundle.hpp"

#define CALL_FRAME_SIZE 256

namespace pit {
	typedef struct CallFrame {
	public:
		CallFrame();
		CallFrame(std::shared_ptr<RefFN> running_ref_fn, uint8_t locals_stack_index);
		/* The currently running function reference */
		std::shared_ptr<RefFN> running_ref_fn;
		/* The currently executing instruction ptr */
		uint8_t* instr_ptr;
		/* A pointer into the VM exec stack pointing to the first local variable for the current fn */
		uint8_t locals_stack_index;
	}CallFrame;
}