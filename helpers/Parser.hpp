#pragma once

#include <cassert>
#include <iostream>
#include <variant>

#include "Arena.hpp"
#include "Tokenizer.hpp"

struct NodeTermInt
{
	Token _int;
};

struct NodeTermFloat
{
	Token _float;
};

struct NodeTermString
{
	Token _string;
};

struct NodeTermChar
{
	Token _char;
};

struct NodeTermBool
{
	Token _bool;
};

struct NodeTermIdent
{
	Token _ident;
};

struct NodeExpr;

struct NodeTermParen
{
	NodeExpr* _expr;
};

struct NodeBinOperAdd
{
	NodeExpr* _left;
	NodeExpr* _right;
};

struct NodeBinOperSub
{
	NodeExpr* _left;
	NodeExpr* _right;
};

struct NodeBinOperMult
{
	NodeExpr* _left;
	NodeExpr* _right;
};

struct NodeBinOperDiv
{
	NodeExpr* _left;
	NodeExpr* _right;
};

struct NodeBinOperMod
{
	NodeExpr* _left;
	NodeExpr* _right;
};

struct NodeBinExpr
{
	std::variant<NodeBinOperAdd*, NodeBinOperSub*, NodeBinOperMult*, NodeBinOperDiv*, NodeBinOperMod*> _op;
};

struct NodeTerm
{
	std::variant<NodeTermInt*, NodeTermFloat*, NodeTermString*, NodeTermChar*, NodeExpr*, NodeTermIdent*, NodeTermParen*> _expr;
};

struct NodeExpr
{
	std::variant<NodeTerm*, NodeBinExpr*> variant;
};

struct NodeStmtExit
{
	NodeExpr* _expr;
};

struct NodeStmt;

struct NodeScope
{
	std::vector<NodeStmt*> _stmts;
};

struct NodeIfPred;

struct NodeIfPredIfElse
{
	NodeExpr* expr {};
	NodeScope* scope {};
	std::optional<NodeIfPred*> pred {};
};

struct NodeIfPredElse
{
	NodeScope* scope;
};

struct NodeIfPred {
	std::variant<NodeIfPredIfElse*, NodeIfPredElse*> var;
};

struct NodeStmtIf {
	NodeExpr* expr {};
	NodeScope* scope {};
	std::optional<NodeIfPred*> pred;
};

struct NodeStmtAssign {
	Token ident;
	NodeExpr* expr {};
};

struct NodeStmt {
	std::variant<NodeStmtExit*, NodeScope*, NodeStmtIf*, NodeStmtAssign*> var;
};

struct NodeProg {
	std::vector<NodeStmt*> stmts;
};

struct NodeWrite
{
	NodeExpr* expr;
};

struct  NodeLabelStmt
{
	Token ident;
	NodeTerm terms;
};

class Parser
{
	public:
		static bool WarnsRErrors;
		explicit Parser(std::vector<Token> tokens) : m_tokens(std::move(tokens)), m_allocator(1024 * 1024 * 4) {}

		void error_expected(const std::string& message) const
		{
			std::cerr << "[Parse Error] Expected" << message << "on line" << read_next(-1).value().line << "\n";
			exit(EXIT_FAILURE);
		}

		std::optional<NodeTerm*> parse_term() //NOLINT(*-no-recursion)
		{

			if (auto ident = try_consume(TokenType::misc_ident))
			{
				auto expr = m_allocator.emplace<NodeTermIdent>(ident.value());
				auto term = m_allocator.emplace<NodeTerm>(expr);
				return term;
			}
			if (auto string_init = try_consume(TokenType::symbol_word))
			{
				auto expr = m_allocator.emplace<NodeTermString>(string_init.value());
				auto term = m_allocator.emplace<NodeTerm>(expr);
				return term;
			}
			if (auto _char = try_consume(TokenType::symbol_char))
			{
				auto expr = m_allocator.emplace<NodeTermChar>(_char.value());
				auto term = m_allocator.emplace<NodeTerm>(expr);
				return term;
			}
			if (auto _int = try_consume(TokenType::type_int))
			{
				auto expr = m_allocator.emplace<NodeTermInt>(_int.value());
				auto term = m_allocator.emplace<NodeTerm>(expr);
				return term;
			}
			if (auto _float = try_consume(TokenType::type_float))
			{
				auto expr = m_allocator.emplace<NodeTermFloat>(_float.value());
				auto term = m_allocator.emplace<NodeTerm>(expr);
				return term;
			}
			if (auto _string = try_consume(TokenType::type_string))
			{
				auto expr = m_allocator.emplace<NodeTermString>(_string.value());
				auto term = m_allocator.emplace<NodeTerm>(expr);
				return term;
			}
			if (const auto _open_paren = try_consume(TokenType::symbol_open_paren))
			{
				auto expr = parse_expr();
				if (!expr.has_value()) { error_expected("expression"); }
				try_consume_err(TokenType::symbol_close_paren);
				auto term_paren = m_allocator.emplace<NodeTermParen>(expr.value());
				auto term = m_allocator.emplace<NodeTerm>(term_paren);
				return term;
			}
			return {};
		}

		std::optional<NodeExpr*> parse_expr(const int min_precedence = 0)
		{
			std::optional<NodeTerm*> term_lhs = parse_term();
			if (!term_lhs.has_value()){return {}; }

			auto expr_lhs = m_allocator.emplace<NodeExpr>(term_lhs.value());

			while (true)
			{
				std::optional<Token> current_token = read_next();
				std::optional<int> token_precedence;
				if (current_token.has_value())
				{
					token_precedence = order_of_op(current_token->type);
					if (!token_precedence.has_value() || token_precedence.value() < min_precedence)
					{
						break;
					}
				}
				else
				{
					break;
				}
				const auto [type, line, value] = consume();
				const int next_min_precedence = token_precedence.value() + 1;
				auto expr_rhs = parse_expr(next_min_precedence);
				if (!expr_rhs.has_value()) { error_expected("expression"); }
				auto expr = m_allocator.emplace<NodeBinExpr>();
				auto expr_lhs2 = m_allocator.emplace<NodeExpr>();

				if (type == TokenType::symbol_plus)
				{
					expr_lhs2->variant = expr_lhs->variant;
					auto add = m_allocator.emplace<NodeBinOperAdd>(expr_lhs2, expr_rhs.value());
					expr->_op = add;
				}
				else if (type == TokenType::symbol_minus)
				{
					expr_lhs2->variant = expr_lhs->variant;
					auto sub = m_allocator.emplace<NodeBinOperSub>(expr_lhs2,  expr_rhs.value());
					expr->_op = sub;
				}
				else if (type == TokenType::symbol_mult)
				{
					expr_lhs2->variant = expr_lhs->variant;
					auto multi = m_allocator.emplace<NodeBinOperMult>(expr_lhs2,  expr_rhs.value());
					expr->_op = multi;
				}
				else if (type == TokenType::symbol_div)
				{
					expr_lhs2->variant = expr_lhs->variant;
					auto div = m_allocator.emplace<NodeBinOperDiv>(expr_lhs2,  expr_rhs.value());
					expr->_op = div;
				}
				else if (type == TokenType::symbol_mod)
				{
					expr_lhs2->variant = expr_lhs->variant;
					auto mod = m_allocator.emplace<NodeBinOperMod>(expr_lhs2,  expr_rhs.value());
					expr->_op = mod;
				}
				else
				{
					assert(false);
				}
				expr_lhs->variant = expr;
			}
			return expr_lhs;
		}

	private:
		// ReSharper disable once CppDFAConstantParameter
		[[nodiscard]] std::optional<Token> read_next(const int offset = 0) const
		{
			if (m_index + offset >= m_tokens.size()) {
				return {};
			}
			return m_tokens.at(m_index + offset);
		}

		Token consume()
		{
			return m_tokens.at(m_index++);
		}

		Token try_consume_err(const TokenType type)
		{
			if (read_next().has_value() && read_next().value().type == type) {
				return consume();
			}
			error_expected(Tokenizer::to_string(type));
			return {};
		}

		std::optional<Token> try_consume(const TokenType type)
		{
			if (read_next().has_value() && read_next().value().type == type) {
				return consume();
			}
			return {};
		}

		const std::vector<Token> m_tokens;
		size_t m_index = 0;
		ArenaAllocator m_allocator;
};
