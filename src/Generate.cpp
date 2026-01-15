#include "Generation.hpp"

Generator::Generator(NodeProg prog) : m_prog(std::move(prog)) {}

void Generator::push(const std::string &reg)
{
	m_output << "    push " << reg << "\n";
	m_stack_size++;
}

void Generator::pop(const std::string &reg)
{
	m_output << "    pop " << reg << "\n";
	m_stack_size--;
}

void Generator::begin_scope() { m_scopes.push_back(m_vars.size()); }

void Generator::end_scope()
{
	const size_t pop_count = m_vars.size() - m_scopes.back();
	if (pop_count != 0)
	{
		m_output << "    add rsp, " << pop_count * 8 << "\n";
	}
	m_stack_size -= pop_count;
	for (size_t i = 0; i < pop_count; i++)
	{
		m_vars.pop_back();
	}
	m_scopes.pop_back();
}

std::stringstream Generator::ArgtoAsm(const int argType,
									  const std::variant<std::string, std::optional<std::string>, int> &label)
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
			std::cerr << "[Input error] message can not be an integer!";
			exit(EXIT_FAILURE);
		}
		m_output << "   mov rax, 1\n";
		m_output << "   mov rdi, 1\n";
		m_output << "   mov rsi, " << temp << "\n";
		m_output << "   mov rdx, " << temp.length() << "\n";
		m_output << "   syscall\n";

		return std::move(m_output);
	}
	// Read
	if (argType == 1)
	{
		m_output << "   mov rax, 0\n";
		m_output << "   mov rdi, 1\n";
		m_output << "   mov rsi, [rel input_buffer]\n";
		m_output << "   mov rdx, 128\n";
		m_output << "   syscall\n";
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
	// Clear read buffer
	if (argType == 3)
	{
		m_output << "   mov edi, input_buffer\n";
		m_output << "	xor al, al";
		m_output << "	mov ecx, 128\n";
		m_output << "	rep stosb\n";
		return std::move(m_output);
	}
	std::cerr << "[Argument error] Invalid argument type!";
	exit(EXIT_FAILURE);
}

std::string Generator::create_label()
{
	std::stringstream ss;
	ss << "label" << m_label_count++;
	return ss.str();
}
