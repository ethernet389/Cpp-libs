#ifndef TOKENBASE
#define TOKENBASE

#include <fstream>
#include <string>
#include <set>

class token_base {
//Под "солью" понимаем строку, которая не позволяет дехэшировать токен только по имени и паролю

public: //Сокращения для типов
	using hash_func_t = std::string(*)(std::string name, std::string password, std::string salt);
	using token_cont_t = std::set<std::string>;
	using tokenb_iter = token_cont_t::iterator;

public: //Конструкторы и деструкторы, оператор =
	token_base(hash_func_t hash_function);
	token_base(hash_func_t hash_function, token_cont_t& tokens);
	token_base(hash_func_t hash_function, token_cont_t&& tokens);
	token_base(token_base& tb);
	token_base(token_base&& tb) noexcept;
	~token_base();

	token_base operator=(token_base& tb);
	token_base operator=(token_base&& tb) noexcept;

public: //Работа с токенами
	//Добавление токена
	void add_token(std::string name, std::string password, std::string salt);
	void add_token(std::string token);

	//Проверка на наличие токена
	bool it_has(std::string token) const;
	bool it_has(std::string name, std::string password, std::string salt) const;

	//Поиск токена
	auto find_token(std::string token) const;
	auto find_token(std::string name, std::string password, std::string salt) const;

	//Удаление токена
	void delete_token(std::string name, std::string password, std::string salt);
	void delete_token(std::string token);

public://Доступ к контейнеру
	tokenb_iter cbegin() const; //Константное начало контейнера с токенами 
	tokenb_iter cend() const; //Константный конец контейнера с токенами 

private: //Поля
	hash_func_t hash_function;
	token_cont_t tokens;
};

namespace token { //Функции для внешней работы с token_base
	void file_input(std::string path_to_file, token_base& token_base);
	void file_output(std::string path_to_file, token_base& token_base);
}

#endif