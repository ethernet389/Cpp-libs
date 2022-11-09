#ifndef TOKENBASE
#define TOKENBASE

#include <fstream>
#include <string>
#include <set>

class token_base {
	//"Salt" - a string which doesn't allow dehashing the token only by name and password

public: //Redycing of types
	using hash_func_t = std::string(*)(std::string const& name, std::string const& password, std::string const& salt);
	using token_cont_t = std::set<std::string>;
	using tokenb_iter = token_cont_t::iterator;

public: //Constructors and destructors
	explicit token_base(hash_func_t hash_function);
	explicit token_base(hash_func_t hash_function, token_cont_t const& tokens);
	explicit token_base(hash_func_t hash_function, token_cont_t&& tokens);
	token_base(token_base const& tb);
	token_base(token_base&& tb) noexcept;
	~token_base();

	token_base operator=(token_base const& tb);
	token_base operator=(token_base&& tb) noexcept;

public: //Work with tokens
	//Token adding
	void add_token(std::string const& name, std::string const& password, std::string const& salt);
	void add_token(std::string const& token);

	//Token checking
	bool it_has(std::string const& token) const;
	bool it_has(std::string const& name, std::string const& password, std::string const& salt) const;

	//Token search
	auto find_token(std::string const& token) const;
	auto find_token(std::string const& name, std::string const& password, std::string const& salt) const;

	//Token deleting
	void delete_token(std::string const& name, std::string const& password, std::string const& salt);
	void delete_token(std::string const& token);

public://Access to container
	tokenb_iter cbegin() const;
	tokenb_iter cend() const;

private:
	hash_func_t hash_function;
	token_cont_t tokens;
};

namespace tb { //Functions for work with token_base class
	std::string hash_function(const std::string& name, const std::string& password, const std::string& salt); //Must implements
	void file_input(std::string const& path_to_file, token_base& token_base);
	void file_output(std::string const& path_to_file, token_base const& token_base);
}

#endif
