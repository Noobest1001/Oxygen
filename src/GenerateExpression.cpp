#include "Generation.hpp"
#include "Parser.hpp"

void Generator::gen_term(const NodeTerm *term)
{
	struct TermVisitor
	{
			Generator &generator;

			void operator()(const NodeTermInt *term)
			{
				// TODO ask Soviet to do this part
			}

			void operator()(const NodeTermFloat *term) {}

			void operator()(const NodeTermBool *term) {}

			void operator()(const NodeTermString *term) {}
	};

  // TermVisitor visitor{.generator = *this};
  // std::visit(visitor, term->_expr);
}

void Generator::gen_bin_expr(const NodeBinExpr *bin_expr)
{
	struct ExprVisitor
	{
			Generator &generator;

			void operator()(const NodeBinOperSub *sub_expr)
			{
				generator.m_output << "    mov rax, " << generator.ExprToAsm(sub_expr->_left) << "\n";
				generator.m_output << "    sub rax, " << generator.ExprToAsm(sub_expr->_right) << "\n";
			}

			void operator()(const NodeBinOperAdd *bin_expr)
			{
				generator.m_output << "    mov rax, " << generator.ExprToAsm(bin_expr->_left) << "\n";
				generator.m_output << "    add rax, " << generator.ExprToAsm(bin_expr->_right) << "\n";
			}

			void operator()(const NodeBinOperDiv *bin_expr)
			{
				generator.m_output << "    mov rax, " << generator.ExprToAsm(bin_expr->_left) << "\n";
				generator.m_output << "    div rax, " << generator.ExprToAsm(bin_expr->_right) << "\n";
			}

			void operator()(const NodeBinOperMod *bin_expr)
			{
				generator.m_output << "    mov rax, " << generator.ExprToAsm(bin_expr->_left) << "\n";
				generator.m_output << "    mod rax, " << generator.ExprToAsm(bin_expr->_right) << "\n";
			}

			void operator()(const NodeBinOperMult *bin_expr)
			{
				generator.m_output << "    mov rax, " << generator.ExprToAsm(bin_expr->_left) << "\n";
				generator.m_output << "    mul rax, " << generator.ExprToAsm(bin_expr->_right) << "\n";
			}
	};

	ExprVisitor visitor{.generator = *this};
	std::visit(visitor, bin_expr->_op);
}

void Generator::gen_expr(const NodeExpr *expr)
{
	struct ExprVisitor
	{
		Generator &generator;

		void operator()(const NodeTerm *term)
		{
			generator.gen_term(term);
		}

		void operator()(const NodeBinExpr *bin_expr)
		{
			generator.gen_bin_expr(bin_expr);
		}
	};

	ExprVisitor visitor{.generator = *this};
	std::visit(visitor, expr->variant);
}

std::string Generator::ExprToAsm(const NodeExpr* expr)
{
	struct ExprToAsmVisitor
	{
		Generator& generator;

		std::string operator()(const NodeTerm* term)
		{
			struct TermToAsmVisitor
			{
				Generator& generator;

				std::string operator()(const NodeTermInt* term)
				{
					return term->_int.value.value_or("0");
				}

				std::string operator()(const NodeTermFloat* term)
				{
					return term->_float.value.value_or("0.0");
				}

				std::string operator()(const NodeTermDouble* term)
				{
					return term->_double.value.value_or("0.0");
				}

				std::string operator()(const NodeTermString* term)
				{
					return "\"" + term->_string.value.value_or("") + "\"";
				}

				std::string operator()(const NodeTermChar* term)
				{
					return "'" + term->_char.value.value_or("") + "'";
				}

				std::string operator()(const NodeTermBool* term)
				{
					return term->_bool.value.value_or("false") == "true" ? "1" : "0";
				}

				std::string operator()(const NodeExpr* expr)
				{
					return generator.ExprToAsm(expr);
				}

				std::string operator()(const NodeTermIdent* term)
				{
					// TODO: handle identifier (variable lookup)
					return term->_ident.value.value_or("");
				}

				std::string operator()(const NodeTermParen* term)
				{
					return generator.ExprToAsm(term->_expr);
				}
			};

			TermToAsmVisitor visitor{.generator = generator};
			return std::visit(visitor, term->_expr);
		}

		std::string operator()(const NodeBinExpr* bin_expr)
		{
			// For binary expressions, we can't just convert to string
			// This would require evaluation. For now, return an error or handle it differently
			// In practice, nested expressions should be evaluated, not converted to strings
			return "rax";  // Return register name as fallback
		}
	};

	ExprToAsmVisitor visitor{.generator = *this};
	return std::visit(visitor, expr->variant);
}
