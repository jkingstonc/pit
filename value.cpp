#include "value.hpp"

namespace pit {

	RefFN::RefFN(std::string name, std::shared_ptr<Bundle> bundle) {
		ref_type = FN;
		this->name = name;
		this->bundle = bundle;
	}

	std::string RefFN::debug() {
		std::ostringstream ss;
		ss << "<ref-fn " << name << ">";
		return ss.str(); 
	}

	RefContainer::RefContainer(uint32_t length, std::vector<Value> init_values) { 
		ref_type = CONTAINER;
		this->size = length;
		this->data = init_values;
	}

	std::string RefContainer::debug() {
		std::ostringstream ss;
		ss << "<ref-container>";
		for (auto v : data)
			ss << v.debug() << ", ";
		return ss.str();
	}
}