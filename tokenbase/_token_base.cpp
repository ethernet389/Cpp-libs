#include "token_base.h"

//Конструкторы и деструкторы
token_base::token_base(hash_func_t hash_function) : hash_function(hash_function) {} //Конструктор по хэш-функции


token_base::token_base(hash_func_t hash_function, token_cont_t& tokens) //Конструктор по хэш-функции и контейнеру с токенами
	: hash_function(hash_function), tokens(tokens) {} 

token_base::token_base(hash_func_t hash_function, token_cont_t&& tokens) //Перемещающий конструктор по хэш-функции и контейнеру с токенами
	: hash_function(hash_function), tokens(std::move(tokens)) {}

token_base::token_base(token_base& tb)  //Конструктор копирования
	: hash_function(tb.hash_function), tokens(tb.tokens) {}

token_base::token_base(token_base&& tb) noexcept//Конструктор перемещения
	: hash_function(hash_function), tokens(std::move(tb.tokens))
{ 
	tb.~token_base();
}

token_base token_base::operator=(token_base& tb) { //Приравнивание
	this->tokens = tb.tokens;
	this->hash_function = tb.hash_function;
	return *this;
}

token_base token_base::operator=(token_base&& tb) noexcept { //Перемещающее приравнивание
	this->tokens = std::move(tb.tokens);
	this->hash_function = tb.hash_function;
	tb.~token_base();
	return *this;
}

token_base::~token_base() {} //Деструктор


//Работа с токенами
void token_base::add_token(std::string name, std::string password, std::string salt) { //Добавление токена по имени, паролю и "соли"
	tokens.insert(hash_function(name, password, salt));
}

void token_base::add_token(std::string token) { //Добавление готового токена
	tokens.insert(token);
}

bool token_base::it_has(std::string token) const { //Проверка на наличие токена по готовому токену
	return tokens.find(token) != tokens.end();
}

bool token_base::it_has(std::string name, std::string password, std::string salt) const { //Проверка на наличие токена по имени, паролю и "соли"
	return tokens.find(hash_function(name, password, salt)) != tokens.end();
}

auto token_base::find_token(std::string token) const { //Поиск токена по готовому токену
	auto it = tokens.find(token);
	return it;
}

auto token_base::find_token(std::string name, std::string password, std::string salt) const { //Поиск токена по имени, паролю и "соли"
	auto it = tokens.find(hash_function(name, password, salt));
	return it;
}

void token_base::delete_token(std::string name, std::string password, std::string salt) { //Удаление токена по имени, паролю и "соли"
	auto it = tokens.find(hash_function(name, password, salt));
	if (it == tokens.end()) return;
	tokens.erase(it);
}

void token_base::delete_token(std::string token) { //Удаление по готовому токену
	auto it = tokens.find(token);
	if (it == tokens.end()) return;
	tokens.erase(it);
}

//Доступ к контейнеру
token_base::tokenb_iter token_base::cbegin() const { //Константное начало контейнера с токенами 
	return tokens.cbegin();
}

token_base::tokenb_iter token_base::cend() const { //Константный конец контейнера с токенами 
	return tokens.cend();
}


//Файловый ввод/вывод токенов

//Примечание: следует добавить файловый ввод по имени, паролю и "соли"

void token::file_input(std::string path_to_file, token_base& token_base) { //Файловый ввод
	std::ifstream file_input;
	file_input.open(path_to_file);
	if (!file_input.is_open()) return; //Проверка на удачное открытие файла

	std::string buffer;
	while (file_input >> buffer) { //Неявное приведение типа к типу bool (если дойдёт до конца файла, то произойдёт ошибка и вернётся 0)
		token_base.add_token(buffer);
	}

	file_input.close();
}

void token::file_output(std::string path_to_file, token_base& token_base) { //Файловый вывод
	std::ofstream file_out;
	file_out.open(path_to_file);
	for (auto i = token_base.cbegin(); i != token_base.cend(); ++i) {
		file_out << *i << std::endl;
	}
	file_out.close();
}