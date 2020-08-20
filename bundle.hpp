#pragma once
#include <string>
#include "value.hpp"
/*
a bundle represents a compiled pit program/module.
the bundle can be written to a file or passed to the runtime.
*/

namespace pit {
	class Bundle {
	public:
		Bundle();
		Bundle(std::string file);
		void to_file(std::string filename);
	private:
		// constants
		// locals
		// code
		uint32_t code[];
	};
}