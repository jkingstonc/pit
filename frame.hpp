#pragma once

#include "value.hpp"
#include "bundle.hpp"

#define CALL_FRAME_SIZE 256

namespace pit {
	typedef struct CallFrame {
	public:
		CallFrame();
		CallFrame(std::shared_ptr<RefFN> running_ref_fn, uint8_t sp_base);
		/* The currently running function reference */
		std::shared_ptr<RefFN> running_ref_fn;
		/* The currently executing instruction ptr */
		uint8_t* instr_ptr;
		/* Exec stack pointer */
		uint8_t sp;
		/* Point to the start of the allocated stack space for this fn */
		uint8_t sp_base;
	}CallFrame;
}