#include "token_base.h"

//Constructors and destructors
token_base::token_base(hash_func_t hash_function) : hash_function(hash_function) {} //Constructor by hash function


token_base::token_base(hash_func_t hash_function, token_cont_t& tokens) //Constructor by hash function and token container
	: hash_function(hash_function), tokens(tokens) {} 

token_base::token_base(hash_func_t hash_function, token_cont_t&& tokens) //Move constructor by hash function and token container
	: hash_function(hash_function), tokens(std::move(tokens)) {}

token_base::token_base(token_base& tb)  //Copy constructor
	: hash_function(tb.hash_function), tokens(tb.tokens) {}

 token_base::token_base(token_base&& tb) noexcept//Moving constructor 
	: hash_function(hash_function), tokens(std::move(tb.tokens))
{ 
	tb.~token_base();
}

token_base token_base::operator=(token_base& tb) { //operator=
	this->tokens = tb.tokens;
	this->hash_function = tb.hash_function;
	return *this;
}

token_base token_base::operator=(token_base&& tb) noexcept { //Moving operator=
	this->tokens = std::move(tb.tokens);
	this->hash_function = tb.hash_function;
	tb.~token_base();
	return *this;
}

token_base::~token_base() {} //Destructor


//Work with tokens
void token_base::add_token(std::string name, std::string password, std::string salt) { //Adding of token by name, password and "salt"
	tokens.insert(hash_function(name, password, salt));
}

void token_base::add_token(std::string token) { //Adding of token by prepared token
	tokens.insert(token);
}

bool token_base::it_has(std::string token) const { //Checking for existence of token by prepared token
	return tokens.find(token) != tokens.end();
}

bool token_base::it_has(std::string name, std::string password, std::string salt) const { //Checking for existence of token by name, password and "salt"
	return tokens.find(hash_function(name, password, salt)) != tokens.end();
}

auto token_base::find_token(std::string token) const { //Search of token by prepared token
	auto it = tokens.find(token);
	return it;
}

auto token_base::find_token(std::string name, std::string password, std::string salt) const { //Search of token by name, password and "salt"
	auto it = tokens.find(hash_function(name, password, salt));
	return it;
}

void token_base::delete_token(std::string name, std::string password, std::string salt) { //Deleting of token by name, password and "salt"
	auto it = tokens.find(hash_function(name, password, salt));
	if (it == tokens.end()) return;
	tokens.erase(it);
}

void token_base::delete_token(std::string token) { //Deleting of token by prepared token
	auto it = tokens.find(token);
	if (it == tokens.end()) return;
	tokens.erase(it);
}

//Access to container
token_base::tokenb_iter token_base::cbegin() const { //Constable begin of token container
	return tokens.cbegin();
}

token_base::tokenb_iter token_base::cend() const { //Constable end of token container
	return tokens.cend();
}


//File input/output of tokens

//P.S.: should add file input by name, password and "salt"

void token::file_input(std::string path_to_file, token_base& token_base) { //File input
	std::ifstream file_input;
	file_input.open(path_to_file);
	if (!file_input.is_open()) return; //File opens check

	std::string buffer;
	while (file_input >> buffer) { //Implicit type casting to bool type (if it reaches the end of the file, an error will occur and 0 will be returned)
		token_base.add_token(buffer);
	}

	file_input.close();
}

void token::file_output(std::string path_to_file, token_base& token_base) { //File output
	std::ofstream file_out;
	file_out.open(path_to_file);
	for (auto i = token_base.cbegin(); i != token_base.cend(); ++i) {
		file_out << *i << std::endl;
	}
	file_out.close();
}