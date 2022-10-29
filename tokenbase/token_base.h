#ifndef TOKENBASE
#define TOKENBASE

#include <fstream>
#include <string>
#include <set>

class token_base {
//��� "�����" �������� ������, ������� �� ��������� ������������ ����� ������ �� ����� � ������

public: //���������� ��� �����
	using hash_func_t = std::string(*)(std::string name, std::string password, std::string salt);
	using token_cont_t = std::set<std::string>;
	using tokenb_iter = token_cont_t::iterator;

public: //������������ � �����������, �������� =
	token_base(hash_func_t hash_function);
	token_base(hash_func_t hash_function, token_cont_t& tokens);
	token_base(hash_func_t hash_function, token_cont_t&& tokens);
	token_base(token_base& tb);
	token_base(token_base&& tb) noexcept;
	~token_base();

	token_base operator=(token_base& tb);
	token_base operator=(token_base&& tb) noexcept;

public: //������ � ��������
	//���������� ������
	void add_token(std::string name, std::string password, std::string salt);
	void add_token(std::string token);

	//�������� �� ������� ������
	bool it_has(std::string token) const;
	bool it_has(std::string name, std::string password, std::string salt) const;

	//����� ������
	auto find_token(std::string token) const;
	auto find_token(std::string name, std::string password, std::string salt) const;

	//�������� ������
	void delete_token(std::string name, std::string password, std::string salt);
	void delete_token(std::string token);

public://������ � ����������
	tokenb_iter cbegin() const; //����������� ������ ���������� � �������� 
	tokenb_iter cend() const; //����������� ����� ���������� � �������� 

private: //����
	hash_func_t hash_function;
	token_cont_t tokens;
};

namespace token { //������� ��� ������� ������ � token_base
	void file_input(std::string path_to_file, token_base& token_base);
	void file_output(std::string path_to_file, token_base& token_base);
}

#endif