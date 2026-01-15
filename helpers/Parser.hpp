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

struct NodeTermDouble
{
	Token _double;
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
	std::variant<NodeTermInt*, NodeTermFloat*, NodeTermString*, NodeTermChar*,NodeTermBool* ,NodeTermDouble*, NodeExpr*, NodeTermIdent*, NodeTermParen*> _expr;
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
		explicit Parser(std::vector<Token> tokens);

		void error_expected(const std::string& message) const;

		std::optional<NodeTerm*> parse_term(); //NOLINT(*-no-recursion)

		std::optional<NodeExpr*> parse_expr(const int min_precedence = 0);

	private:
		// ReSharper disable once CppDFAConstantParameter
		[[nodiscard]] std::optional<Token> read_next(const int offset = 0) const;

		Token consume();

		Token try_consume_err(const TokenType type);

		std::optional<Token> try_consume(const TokenType type);

		const std::vector<Token> m_tokens;
		size_t m_index = 0;
		ArenaAllocator m_allocator;
};
