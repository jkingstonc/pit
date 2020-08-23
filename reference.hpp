#pragma once

#include "value.hpp"

namespace pit {
	static RefBundle* allocate_bundle(int length);
	static RefContainer* allocate_container(int length);
}