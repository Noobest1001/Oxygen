#pragma once

#include <algorithm>
#include <cassert>
#include <sstream>

#include "Parser.hpp"

class Generator
{
	public:
		explicit Generator(NodeProg prog) : m_prog(std::move(prog))
		{

		}

		void gen_term(const NodeTerm* term)
		{
			struct TermVisitor
			{
				Generator& generator;

				void operator()(const NodeTermInt* term)
				{

				}
			};
		}

		void gen_bin_expr(const NodeBinExpr* bin_expr)
		{
			struct ExprVisitor
			{
				Generator& generator;

				void operator()(const NodeBinOperSub sub_expr)
				{
					//TODO add this
				}

				void operator()(const NodeBinExpr* bin_expr)
				{
					//TODO add this
				}
			};

			ExprVisitor visitor {.generator = *this};
			std::visit(visitor, bin_expr -> var);
		}

		void gen_method(const std::string&, const NodeLabelStmt* label_expr)
		{
			struct ExprVisitor
			{
				Generator& generator;

				void operator()(const NodeLabelStmt* label_expr)
				{
					generator.m_output << ""
				}
			};
		}

	private:
		void push(const std::string& reg)
		{
			m_output << "    push " << reg << "\n";
			m_stack_size++;
		}

		void pop(const std::string& reg)
		{
			m_output << "    pop " << reg << "\n";
			m_stack_size--;
		}

		void begin_scope()
		{
			m_scopes.push_back(m_vars.size());
		}

		void end_scope()
		{
			const size_t pop_count = m_vars.size() - m_scopes.back();
			if (pop_count != 0) {
				m_output << "    add rsp, " << pop_count * 8 << "\n";
			}
			m_stack_size -= pop_count;
			for (size_t i = 0; i < pop_count; i++) {
				m_vars.pop_back();
			}
			m_scopes.pop_back();
		}

		std::string ArgtoAsm(const int argType = 0, const std::optional<std::string> &label = std::nullopt)
		{
			if (argType == 0)
			{
				if (!label.has_value())
				{
					std::cerr << "[Argument error] message has no value";
					exit(EXIT_FAILURE);
				}
				m_output << "    mov rax, 1\n";
				m_output << "    mov rdi, 1\n";
				m_output << "    mov rsi, " << label.value() << "\n";
				m_output << "    mov rdx, " << label->length() << "\n";
			}
			if (argType == 1)
			{

			}
		}

		std::string create_label()
		{
			std::stringstream ss;
			ss << "label" << m_label_count++;
			return ss.str();
		}

		struct Var {
			std::string name;
			size_t stack_loc;
		};

		const NodeProg m_prog;
		std::stringstream m_output;
		size_t m_stack_size = 0;
		std::vector<Var> m_vars {};
		std::vector<size_t> m_scopes {};
		int m_label_count = 0;
};
