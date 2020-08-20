#include "value.hpp"

namespace pit {
	Value Value::to_value(uint8_t value) {
		return { {(float)value}, {PrimitiveType::NUMBER} };
	}
}