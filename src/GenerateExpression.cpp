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
				// TODO add this
			}

			void operator()(const NodeBinOperAdd *bin_expr)
			{
				// TODO add this
			}

			void operator()(const NodeBinOperDiv *bin_expr)
			{
				// TODO add this
			}

			void operator()(const NodeBinOperMod *bin_expr)
			{
				// TODO add this
			}

			void operator()(const NodeBinOperMult *bin_expr)
			{
				// TODO add this
			}
	};

	ExprVisitor visitor{.generator = *this};
	std::visit(visitor, bin_expr->_op);
}
