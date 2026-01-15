#include "Generation.hpp"

[[nodiscard]] std::string Generator::gen_prog()
{
	m_output << "section .text\n";
	m_output << "    global _start\n";
	m_output << "_start:\n";
	for (const NodeStmt *stmt: m_prog.stmts)
	{
		gen_stmt(stmt);
	}
	return m_output.str();
}

void Generator::gen_stmt(const NodeStmt *stmt)
{
  struct StmtVisitor
  {
      Generator &generator;

      void operator()(const NodeStmtExit *stmt)
      {
        generator.m_output << "    mov rax, 60\n";
        generator.m_output << "    xor rdi, rdi\n";
        generator.m_output << "    syscall\n";
      }

      void operator()(const NodeScope *scope)
      {
        for (const NodeStmt *stmt: scope->_stmts)
        {
          generator.gen_stmt(stmt);
        }
      }

      void operator()(const NodeStmtIf *stmt)
      {
        // TODO add this
      }

      void operator()(const NodeStmtAssign *stmt)
      {
        // TODO add this
      }
  };

  StmtVisitor visitor{.generator = *this};
  std::visit(visitor, stmt->var);
}