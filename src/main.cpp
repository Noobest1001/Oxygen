#include <filesystem>
#include <fstream>
#include <iostream>

// #include "../helpers/Generation.hpp"

int main(const int argc, char *argv[])
{
	static bool KeepOutFile;
	static std::string OutputFile;
	if (argc == 1)
	{
		std::cerr << "Incorrect usage of the Oxygen Compiler!\nProper usage is Oxygen <file.oxy>\n";
		exit(1);
	}
	if (argc > 2)
	{
		// Tokenizer::isDebugMode = false;
		// Parser::WarnsRErrors = false;
		KeepOutFile = false;

		for (auto i = 1; i < argc; i++)
		{
			if (argv[i] == std::string("--debug") || argv[i] == std::string("-d") || argv[i] == std::string("-D"))
			{
				// Tokenizer::isDebugMode = true;
				std::cout << "Debug mode activated\n";
			}
			if (argv[i] == std::string("--o-keep") || argv[i] == std::string("-o"))
			{
				KeepOutFile = true;
			}
			if (argv[i] == std::string("-o-name"))
			{
				std::cout << "Renaming output file\n";
				try
				{
					std::cout << "Attempted to index i to " << i + 1 << '\n';
					i++;
					std::cout << "Indexed i to " << i << '\n';
					if (argv[i] == nullptr)
					{
						throw std::exception();
					}
					std::cout << argv[i] << '\n';
					OutputFile = argv[i];
					if (OutputFile.find('.') != std::string::npos && OutputFile.find(".out") == std::string::npos)
					{
						std::filesystem::path temp = OutputFile;
						temp.replace_extension("out");
						OutputFile = temp.string();
						std::cout << OutputFile << std::endl;
					}
					else
					{
						std::cerr << "an Error has occurred\n";
						exit(3);
					}
					if (i == argc - 1)
					{
						break;
					}
				}
				catch (const std::exception &e)
				{
					std::cout << "i++ > argc\n";
					std::cout << "No output name specified. using default name (a.out)\n";
					OutputFile = "a.out";
					continue;
				}

				if (argv[i] == std::string("--WarnError") || argv[i] == std::string("-Werror"))
				{
					// Parser::WarnsRErrors = true;
				}
				if (argv[i] == std::string("-h") || argv[i] == std::string("--help"))
				{
					std::cout
							<< "-h or --help:\n\t"
							   "This\n-d, -D, or --debug:\n\tEnables debug text and writing of a log of all debug "
							   "text\n"
							   "-o, --o-keep, or --out-keep:\n\tKeeps the out (assembly) file for you fellow autists\n"
							   "-o-name:\n\tOverrides the out files name (default: a)\n";
					exit(0);
				}
			}
		}
		return 0;
	}
	if (argc == 2)
	{
		// Tokenizer::isDebugMode = false;
		// Parser::WarnsRErrors = false;
		KeepOutFile = false;

		if (!std::filesystem::is_regular_file(argv[1]))
		{
			std::cerr << "File not Found: " << argv[1] << "\n";
			std::cerr << "Exited with exit code: 5\n";
			exit(5);
		}
	}
}
