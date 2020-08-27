#include "frame.hpp"

namespace pit {
	CallFrame::CallFrame(){}

	CallFrame::CallFrame(std::shared_ptr<RefFN> running_ref_fn, uint8_t sp_base) {
		this->running_ref_fn = running_ref_fn;
		this->instr_ptr = running_ref_fn->bundle->code.data();
		this->sp_base = sp_base;
		this->sp = sp_base + running_ref_fn->arity + running_ref_fn->locals;
	}
}