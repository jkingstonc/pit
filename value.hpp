#pragma once

#include <cstdint>
#include <string>

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
			Value pvalue{pvalue.type = BOOL, pvalue.data.boolean=value};
			return pvalue;
		}

		inline static Value num_val(float value) {
			Value pvalue{ pvalue.type = NUMBER, pvalue.data.num = value };
			return pvalue;
		}


		inline bool as_bool() { return data.boolean; }
		inline float as_num() { return data.num; }

		inline bool is_num() {
			return type == ValueType::NUMBER;
		}

		ValueType type;
		union ValueData{
			bool boolean;
			float num;
		} data;
	}Value;
}