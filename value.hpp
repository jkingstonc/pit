#pragma once

#include <cstdint>

namespace pit {
		
	enum PrimitiveType {
		BOOL,
		NUMBER,
		STRING,
		BUNDLE,     // technically a fn is a bundle
		CONTAINER,
		TYPE,
		SIGNATURE,
		ATOM,
	};

	struct Type {
	public:
		PrimitiveType primitive_type;
	};

	// a value represents a runtime value of a pit value
	struct Value{
	public:
		static Value to_value(uint8_t value);
		union{
			float num;
		} data;
		Type type;
	};
}