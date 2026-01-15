#pragma once

#include <cassert>
#include <sstream>

#include "Parser.hpp"

class Generator
{
	public:
		explicit Generator(NodeProg prog);

		void gen_term(const NodeTerm* term);

		void gen_bin_expr(const NodeBinExpr* bin_expr);

		void gen_method(const std::string&, const NodeLabelStmt* label_expr)
		{
			struct ExprVisitor
			{
				Generator& generator;

				void operator()(const NodeLabelStmt* label_expr)
				{
					generator.m_output << "";
				}
			};
		}

		[[nodiscard]] std::string gen_prog();

	private:
    void gen_stmt(const NodeStmt *stmt);

		// I don't know how to do assembly so could one of you help me with this part?
		void push(const std::string& reg);

		void pop(const std::string& reg);

		void begin_scope();

		void end_scope();

		std::stringstream ArgtoAsm(const int argType = 0, const std::variant<std::string, std::optional<std::string>, int> &label = std::nullopt);

		std::string create_label();

		struct Var {
			std::string name;
			size_t stack_loc;
		};

		const NodeProg m_prog;
		std::stringstream m_output;
		size_t m_stack_size = 0;
		size_t m_string_counter = 0;
		std::vector<Var> m_vars {};
		std::vector<size_t> m_scopes {};
		int m_label_count = 0;
};
