#pragma once

namespace pit {
	namespace runtime {
		
		enum PrimitiveType {
			BOOL,
			NUMBER,
			STRING,
			FN,
			CONTAINER,
			TYPE,
			SIGNATURE,
			ATOM,
		};

		class Type {
		public:
		private:
			PrimitiveType primitive_type;
		};

		// a value represents a runtime value of a pit value
		class Value{
		public:
		private:
			Type type;
		};
	}
}