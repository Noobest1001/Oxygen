#include <filesystem>
#include <fstream>
#include <iostream>

#include "../helpers/Generation.hpp"

int main(const int argc, char* argv[])
{
	static bool KeepOutFile;
	if (argc == 1)
	{
		std::cerr << "Incorrect usage of the Oxygen Compiler!\nProper usage is Oxygen <file.oxy>";
		exit(1);
	}
	if (argc > 2)
	{
		for (auto i = 1; i < argc; i++)
		{
			if (argv[i] == std::string("--debug") || argv[i] == std::string("-d") || argv[i] == std::string("-D"))
			{
				Tokenizer::isDebugMode = true;
			}
			if (argv[i] == std::string("-o"))
			{
				KeepOutFile = true;
			}
			if (argv[i] == std::string("--WarnError") || argv[i] == std::string("-Werror"))
			{
				Parser::WarnsRErrors = true;
			}
		}
	}
	else if (argc == 2)
	{
		Tokenizer::isDebugMode = false;
		Parser::WarnsRErrors = false;
		KeepOutFile = false;

		if (!std::filesystem::is_regular_file(argv[2]))
		{
			std::cerr << "File not Found: " << argv[2] << std::endl;
			std::cerr << "Exited with exit code: 5";
			exit(5);
		}
	}
}