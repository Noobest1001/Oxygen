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
					generator.m_output << "";
				}
			};
		}

		[[nodiscard]] std::string gen_prog()
		{
			m_output << "section .bss\n";
			m_output << "    input_buffer: resb 128";

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

		std::stringstream ArgtoAsm(const int argType = 0, const std::variant<std::string, std::optional<std::string>, int> &label = std::nullopt)
		{

			// Write
			if (argType == 0)
			{
				std::string temp;

				if (std::holds_alternative<std::string>(label))
				{
					if (temp = std::get<std::string>(label); temp.empty())
					{
						std::cerr << "[Argument error] message has no value";
						exit(EXIT_FAILURE);
					}
				}
				if (std::holds_alternative<int>(label))
				{
					std::cerr << "[Input error]message can not be and integer!";
					exit(EXIT_FAILURE);
				}
				m_output << "   mov rax, 1\n";
				m_output << "   mov rdi, 1\n";
				m_output << "   mov rsi, " << temp << "\n";
				m_output << "   mov rdx, " << temp.length() << "\n";

				return std::move(m_output);
			}
			// Read
			if (argType == 1)
			{
				m_output << "   mov rax, 0\n";
				m_output << "   mov rdi, 1\n";
				m_output << "   mov rsi, [rel input_buffer]\n";
				m_output << "   mov rdx, 128\n";
				return std::move(m_output);
			}
			// exit/ return
			if (argType == 2)
			{
				int number = -1;
				if (std::holds_alternative<int>(label))
				{
					number = std::get<int>(label);
				}
				if (number == -1)
				{
					std::cerr << "Exit code not provided!";
					exit(EXIT_FAILURE);
				}
				m_output << "   mov rax, 60\n";
				m_output << "	mov rdx, " << number << "\n";
				m_output << "   syscall\n";
				return std::move(m_output);
			}
			std::cerr << "[Argument error] Invalid argument type!";
			exit(EXIT_FAILURE);
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
		size_t m_string_counter = 0;
		std::vector<Var> m_vars {};
		std::vector<size_t> m_scopes {};
		int m_label_count = 0;
};
