#ifndef TOKENBASE
#define TOKENBASE

#include <fstream>
#include <string>
#include <set>

class token_base {
//"Salt" - a string which doesn't allow dehashing the token only by name and password

public: //Redycing of types
	using hash_func_t = std::string(*)(std::string name, std::string password, std::string salt);
	using token_cont_t = std::set<std::string>;
	using tokenb_iter = token_cont_t::iterator;

public: //Constructors and destructors
	token_base(hash_func_t hash_function);
	token_base(hash_func_t hash_function, token_cont_t& tokens);
	token_base(hash_func_t hash_function, token_cont_t&& tokens);
	token_base(token_base& tb);
	token_base(token_base&& tb) noexcept;
	~token_base();

	token_base operator=(token_base& tb);
	token_base operator=(token_base&& tb) noexcept;

public: //Work with tokens
	//Token adding
	void add_token(std::string name, std::string password, std::string salt);
	void add_token(std::string token);

	//Token checking
	bool it_has(std::string token) const;
	bool it_has(std::string name, std::string password, std::string salt) const;

	//Token search
	auto find_token(std::string token) const;
	auto find_token(std::string name, std::string password, std::string salt) const;

	//Token deleting
	void delete_token(std::string name, std::string password, std::string salt);
	void delete_token(std::string token);

public://Access to container
	tokenb_iter cbegin() const;
	tokenb_iter cend() const;

private: //Поля
	hash_func_t hash_function;
	token_cont_t tokens;
};

namespace token { //Functions for work with token_base class
	void file_input(std::string path_to_file, token_base& token_base);
	void file_output(std::string path_to_file, token_base& token_base);
}

#endif