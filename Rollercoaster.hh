#ifndef ROLLERCOASTER_HH
#define ROLLERCOASTER_HH

#include <string>
#include <vector>

class Rollercoaster
{
public:
	enum class Syntax
	{
		Brainfuck
	};

	Rollercoaster(const std::string& sourcePath);
	bool parse(Syntax syntax);

	const std::string& getOutput() { return output; }

private:
	const static std::string& getCharacters(Syntax syntax);
	std::vector <std::string> lines;

	std::string output;
};

#endif
