#include "frame.hpp"

namespace pit {
	CallFrame::CallFrame(){}

	CallFrame::CallFrame(std::shared_ptr<RefFN> running_ref_fn, uint8_t* return_instr_ptr, uint8_t locals_stack_index) {
		this->running_ref_fn = running_ref_fn;
		this->return_instr_ptr = return_instr_ptr;
		this->locals_stack_index = locals_stack_index;
	}
}