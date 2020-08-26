#pragma once

#include "value.hpp"

namespace pit {
	/* 
	currently this implementation doesn't use a GC and instead uses reference counting.
	We need a way of avoiding reference loops though...
	*/
	static std::shared_ptr<RefBundle> allocate_bundle(std::string name, std::shared_ptr<Bundle> bundle);
	static std::shared_ptr<RefContainer> allocate_container(int length);
}