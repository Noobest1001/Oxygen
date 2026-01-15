#pragma once

#include <cassert>
#include <optional>
#include <string>
#include <vector>

enum class TokenType
{
	keyword_exit,
	type_int,
	type_char,
	type_bool,
	type_float,
	type_double,
	type_string,
	keyword_if,
	keyword_elif,
	keyword_else,
	keyword_write,
	keyword_dynamic,
	keyword_property,
	keyword_function,
	symbol_open_paren,
	symbol_close_paren,
	symbol_open_brace,
	symbol_closed_brace,
	symbol_word, // "
	symbol_char, // '
	symbol_equals,
	symbol_plus,
	symbol_minus,
	symbol_mult,
	symbol_div,
	symbol_mod,
	misc_ident,
};

struct Token
{
		TokenType type;
		int line;
		std::optional<std::string> value{};
};

inline std::optional<int> order_of_op(const TokenType type)
{
	switch (type)
	{
		case TokenType::symbol_minus:
		case TokenType::symbol_plus:
			return 0;
		case TokenType::symbol_div:
		case TokenType::symbol_mult:
			return 1;

		default:
			return {};
	}
}

class Tokenizer
{
	public:
		size_t m_index = 0;
		static bool isDebugMode;

		explicit Tokenizer(std::string input);

		static std::string to_string(const TokenType type);

		std::vector<Token> tokenize();

	private:
		const std::string m_src;

		// ReSharper disable once CppDFAConstantParameter
		[[nodiscard]] std::optional<char> peek(const size_t offset = 0) const;

		char consume();
};
