#include "siffers_algorithms.h"

size_t _find_index_only_alphabet(std::string const& alphabet, char const& element){
	for (size_t i = 0; i != alphabet.size(); ++i) {
		if (alphabet[i] == element) return i;
	}
	return -1;
}

std::string SifferOfCessar(std::string const& input_string, std::string const& alphabet,signed long long const& offset = 1) {
	#define CessarAlgorithm alphabet[(alphabet.size() + alphaPos + offset % (alphabet.size() + 1)) % alphabet.size()]

	std::string ret = input_string;
	for (size_t i = 0; i != input_string.size(); ++i) {
		size_t alphaPos = _find_index_only_alphabet(alphabet, input_string[i]);
		ret[i] = CessarAlgorithm;
	}

	#undef CessarAlgorithm
	return ret;
}