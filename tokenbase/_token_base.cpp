#include "token_base.h"

//������������ � �����������
token_base::token_base(hash_func_t hash_function) : hash_function(hash_function) {} //����������� �� ���-�������


token_base::token_base(hash_func_t hash_function, token_cont_t& tokens) //����������� �� ���-������� � ���������� � ��������
	: hash_function(hash_function), tokens(tokens) {} 

token_base::token_base(hash_func_t hash_function, token_cont_t&& tokens) //������������ ����������� �� ���-������� � ���������� � ��������
	: hash_function(hash_function), tokens(std::move(tokens)) {}

token_base::token_base(token_base& tb)  //����������� �����������
	: hash_function(tb.hash_function), tokens(tb.tokens) {}

token_base::token_base(token_base&& tb) noexcept//����������� �����������
	: hash_function(hash_function), tokens(std::move(tb.tokens))
{ 
	tb.~token_base();
}

token_base token_base::operator=(token_base& tb) { //�������������
	this->tokens = tb.tokens;
	this->hash_function = tb.hash_function;
	return *this;
}

token_base token_base::operator=(token_base&& tb) noexcept { //������������ �������������
	this->tokens = std::move(tb.tokens);
	this->hash_function = tb.hash_function;
	tb.~token_base();
	return *this;
}

token_base::~token_base() {} //����������


//������ � ��������
void token_base::add_token(std::string name, std::string password, std::string salt) { //���������� ������ �� �����, ������ � "����"
	tokens.insert(hash_function(name, password, salt));
}

void token_base::add_token(std::string token) { //���������� �������� ������
	tokens.insert(token);
}

bool token_base::it_has(std::string token) const { //�������� �� ������� ������ �� �������� ������
	return tokens.find(token) != tokens.end();
}

bool token_base::it_has(std::string name, std::string password, std::string salt) const { //�������� �� ������� ������ �� �����, ������ � "����"
	return tokens.find(hash_function(name, password, salt)) != tokens.end();
}

auto token_base::find_token(std::string token) const { //����� ������ �� �������� ������
	auto it = tokens.find(token);
	return it;
}

auto token_base::find_token(std::string name, std::string password, std::string salt) const { //����� ������ �� �����, ������ � "����"
	auto it = tokens.find(hash_function(name, password, salt));
	return it;
}

void token_base::delete_token(std::string name, std::string password, std::string salt) { //�������� ������ �� �����, ������ � "����"
	auto it = tokens.find(hash_function(name, password, salt));
	if (it == tokens.end()) return;
	tokens.erase(it);
}

void token_base::delete_token(std::string token) { //�������� �� �������� ������
	auto it = tokens.find(token);
	if (it == tokens.end()) return;
	tokens.erase(it);
}

//������ � ����������
token_base::tokenb_iter token_base::cbegin() const { //����������� ������ ���������� � �������� 
	return tokens.cbegin();
}

token_base::tokenb_iter token_base::cend() const { //����������� ����� ���������� � �������� 
	return tokens.cend();
}


//�������� ����/����� �������

//����������: ������� �������� �������� ���� �� �����, ������ � "����"

void token::file_input(std::string path_to_file, token_base& token_base) { //�������� ����
	std::ifstream file_input;
	file_input.open(path_to_file);
	if (!file_input.is_open()) return; //�������� �� ������� �������� �����

	std::string buffer;
	while (file_input >> buffer) { //������� ���������� ���� � ���� bool (���� ����� �� ����� �����, �� ��������� ������ � ������� 0)
		token_base.add_token(buffer);
	}

	file_input.close();
}

void token::file_output(std::string path_to_file, token_base& token_base) { //�������� �����
	std::ofstream file_out;
	file_out.open(path_to_file);
	for (auto i = token_base.cbegin(); i != token_base.cend(); ++i) {
		file_out << *i << std::endl;
	}
	file_out.close();
}