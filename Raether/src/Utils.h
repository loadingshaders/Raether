#pragma once

#include <string>

namespace Utils {

	#ifdef DEBUG
	inline void PrintError(std::string Error) {
		std::cout << Error << std::endl;
	}
	
	#else
	inline void PrintError(std::string Error) {
		// Do Nothing!
	}
	#endif
};