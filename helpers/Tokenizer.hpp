#pragma once

#include <cassert>
#include <functional>
#include <optional>
#include <string>
#include <vector>

// For debugging
#include <fstream>


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
	std::optional<std::string> value {};
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

		explicit Tokenizer(std::string input) : m_src(std::move(input)) {}

		static std::string to_string(const TokenType type)
		{
			switch (type)
			{
				// type identifiers -> int <variable name> = 69;
				case TokenType::type_int: return "int";
				case TokenType::type_char: return "char";
				case TokenType::type_bool: return "bool";
				case TokenType::type_float: return "float";
				case TokenType::type_double: return "double";
				case TokenType::type_string: return "string";
					// Keywords
				case TokenType::keyword_exit: return "exit";
				case TokenType::keyword_if: return "if";
				case TokenType::keyword_elif: return "else if";
				case TokenType::keyword_else: return "else";
				case TokenType::keyword_write: return "write";
					// symbols... I don't know how to describe this.
				case TokenType::symbol_open_paren: return "(";
				case TokenType::symbol_close_paren: return ")";
					//TODO add functions
					// case TokenType::symbol_open_brace: return "{";
					// case TokenType::symbol_closed_brace: return "}"; For Functions later on
				case TokenType::symbol_equals: return "=";
				case TokenType::symbol_plus: return "+";
				case TokenType::symbol_minus: return "-";
				case TokenType::symbol_mult: return "*";
				case TokenType::symbol_div: return "/";
				case TokenType::symbol_mod: return "%";
					//TODO add string functionality
				case TokenType::symbol_char: return "\'";
				case TokenType::symbol_word: return "\"";
					//miscellaneous stuff
				case TokenType::misc_ident: return "identifier";
				default: exit(EXIT_FAILURE);
			}
			assert(false);
		}

		std::vector<Token> tokenize()
		{
			std::vector<Token> tokens;
			std::string buffer;
			int line_counter = 1;

			while (peek().has_value())
			{
				if (std::isalpha(peek().value()))
				{
					buffer.push_back(consume());
					while (peek().has_value() && std::isalnum(peek().value()))
					{
						buffer.push_back(consume());
					}
					std::cout << "Buffer has value" << buffer << "on line" << line_counter << "\n";
					if (buffer == "exit")
					{
						tokens.push_back({TokenType::keyword_exit, line_counter});
						buffer.clear();
					}
					else if (buffer == "if")
					{
						tokens.push_back({TokenType::keyword_if, line_counter});
						buffer.clear();
					}
					else if (buffer == "else")
					{
						tokens.push_back({TokenType::keyword_else, line_counter});
						buffer.clear();
					}
					else if (buffer == "int")
					{
						tokens.push_back({TokenType::type_int, line_counter});
						buffer.clear();
					}
					else if (buffer == "char")
					{
						tokens.push_back({TokenType::type_char, line_counter});
						buffer.clear();
					}
					else if (buffer == "bool")
					{
						tokens.push_back({TokenType::type_bool, line_counter});
						buffer.clear();
					}
					else if (buffer == "float")
					{
						tokens.push_back({TokenType::type_float, line_counter});
						buffer.clear();
					}
					else if (buffer == "double")
					{
						tokens.push_back({TokenType::type_double, line_counter});
					}
					else if (buffer == "string")
					{
						tokens.push_back({TokenType::type_string, line_counter});
						buffer.clear();
					}

				}
				else if (std::isdigit(peek().value()) || peek().value() == '.')
				{
					buffer.push_back(consume());
					while (peek().has_value() && (std::isdigit(peek().value()) || peek().value() == '.'))
					{
						buffer.push_back(consume());
					}
					if (buffer.contains("."))
					{
						tokens.push_back({TokenType::type_float, line_counter});
						buffer.clear();
					}
					else if (peek().value() == 'd' || peek().value() == 'D')
					{
						tokens.push_back({TokenType::type_double, line_counter});
						buffer.clear();
					}
					else
					{
						tokens.push_back({TokenType::type_int, line_counter});
						buffer.clear();
					}
				}
			}
		}

	private:
		const std::string m_src;

		// ReSharper disable once CppDFAConstantParameter
		[[nodiscard]] std::optional<char> peek(const size_t offset = 0) const
		{
			if (m_index + offset >= m_src.length())
			{
				return {};
			}
			return m_src[m_index + offset];
		}

		char consume()
		{
			return m_src[m_index++];
		}


};