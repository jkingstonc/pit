#pragma once
#include "bundle.hpp"
#include "instruction.hpp"

/*
this file actually runs the 'cyanide' virtual machine
*/

namespace pit {
	namespace runtime {
		class VM {
		public:
			VM(Bundle bundle);
			void run();
		private:
			Bundle bundle;
		};
	}
}