#pragma once

#include <cstdint>
#include <string>
#include <sstream>

namespace pit {
		
	enum ValueType {
		BOOL,
		NUMBER,
		STRING,     // reference
		BUNDLE,     // reference (fn is a bundle)
		CONTAINER,	// reference
		TYPE,
		SIGNATURE, 
		ATOM,
	};

	// a value represents a runtime value of a pit value
	typedef struct Value {
	public:
		inline static Value bool_val(bool value) { 
			Value v;
			v.type = BOOL;
			v.data.boolean = value;
			return v;
		}

		inline static Value num_val(float value) {
			Value v;
			v.type = NUMBER;
			v.data.num = value;
			return v;
		}

		inline bool equals(Value other) {
			if (type != other.type) return false;
			switch (type) {
			case BOOL: return data.boolean == other.as_bool();
			case NUMBER: return data.num == other.as_num();
			}
		}

		inline bool as_bool() { return data.boolean; }
		inline float as_num() { return data.num; }

		inline bool is_bool() {
			return type == ValueType::BOOL;
		}
		inline bool is_num() {
			return type == ValueType::NUMBER;
		}

		inline std::string debug() {
			std::ostringstream stringStream;
			switch (type) {
			case BOOL:
				stringStream << "bool: " << data.boolean;
				break;
			case NUMBER:
				stringStream << "num: " << data.num;
				break;
			}
			return stringStream.str();
		}

		ValueType type;
		union ValueData{
			bool boolean;
			float num;
		} data;
	}Value;
}