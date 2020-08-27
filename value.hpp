#pragma once

#include <cstdint>
#include <string>
#include <sstream>
#include <variant>
#include <vector>

namespace pit {
		
	class Bundle;
	struct Value;

	enum ReferenceType {
		FN,
		CONTAINER,
	};

	enum ValueType {
		BOOL,
		NUMBER,
		REFERENCE,
		SIGNATURE, 
		ATOM,
	};

	typedef struct Reference {
	public:
		ReferenceType ref_type;
		virtual std::string debug() = 0;
	} Reference;

	/*
	A RefFN is assentially a heap allocated bundle
	*/
	typedef struct RefFN : public Reference {
	public:
		RefFN(std::string name, std::shared_ptr<Bundle> bundle);
		std::string debug();
		std::shared_ptr<Bundle> bundle;
		std::string name;
	}RefFN;

	// a container essentially extends reference
	typedef struct RefContainer : public Reference {
	public:
		RefContainer(uint32_t size, std::vector<Value> init_values);
		std::string debug();
		uint32_t size;
		std::vector<Value> data;
	} RefContainer;

	// a value represents a runtime value of a pit value
	typedef struct Value {
	public:
		inline static Value bool_val(bool value) { 
			Value v;
			v.type = BOOL;
			v.data = value;
			return v;
		}

		inline static Value num_val(float value) {
			Value v;
			v.type = NUMBER;
			v.data = value;
			return v;
		}

		inline static Value fn_value(std::string name, std::shared_ptr<Bundle> bundle){
			Value v;
			v.type = REFERENCE;
			v.data = std::make_shared<RefFN>(name, bundle);
			return v;
		}

		inline static Value container_value(uint32_t size, std::vector<Value> init_values) {
			Value v;
			v.type = REFERENCE;
			v.data = std::make_shared<RefContainer>(size, init_values);
			return v;
		}

		inline bool equals(Value other) {
			if (type != other.type) return false;
			switch (type) {
			case BOOL: return std::get<bool>(data) == other.as_bool();
			case NUMBER: return std::get<float>(data) == other.as_num();
			}
		}

		inline bool as_bool() { 
			return std::get<bool>(data); 
		}
		inline float as_num() {
			return std::get<float>(data); 
		}
		inline std::shared_ptr<RefFN> as_fn() {
			return std::dynamic_pointer_cast<RefFN>(std::get<std::shared_ptr<Reference>>(data));
		}
		inline std::shared_ptr<RefContainer> as_container() {
			return std::dynamic_pointer_cast<RefContainer>(std::get<std::shared_ptr<Reference>>(data)); 
		}

		inline bool is_bool() {
			return type == ValueType::BOOL;
		}
		inline bool is_num() {
			return type == ValueType::NUMBER;
		}
		inline bool is_fn() {
			return type == ValueType::REFERENCE && std::get<std::shared_ptr<Reference>>(data)->ref_type == FN;
		}
		inline bool is_container() {
			return type == ValueType::REFERENCE && std::get<std::shared_ptr<Reference>>(data)->ref_type == CONTAINER;
		}

		inline std::string debug() {
			std::ostringstream stringStream;
			switch (type) {
			case BOOL:
				stringStream << "bool: " << std::get<bool>(data);
				break;
			case NUMBER:
				stringStream << "num: " << std::get<float>(data);
				break;
			case REFERENCE:
				stringStream << std::get<std::shared_ptr<Reference>>(data)->debug();
				break;
			}
			return stringStream.str();
		}

		ValueType type;
		std::variant<bool, float, std::shared_ptr<Reference>> data;
	}Value;
}