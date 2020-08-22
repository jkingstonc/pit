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


		inline bool as_bool() { return data.boolean; }
		inline float as_num() { return data.num; }

		inline bool is_num() {
			return type == ValueType::NUMBER;
		}

		inline std::string debug() {
			switch (type){
			case BOOL: {
				std::ostringstream stringStream;
				stringStream << "bool: " << data.boolean;
				return stringStream.str();
			}
			case NUMBER:
				std::ostringstream stringStream;
				stringStream << "num: " << data.num;
				return stringStream.str();
			}
		}

		ValueType type;
		union ValueData{
			bool boolean;
			float num;
		} data;
	}Value;
}