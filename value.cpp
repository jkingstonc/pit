#include "value.hpp"

namespace pit {

	RefBundle::RefBundle(std::shared_ptr<Bundle> bundle) { 
		ref_type = BUNDLE; this->bundle = bundle; 
	}

	std::string RefBundle::debug() { 
		return "<ref-bundle>"; 
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