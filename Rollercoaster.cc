#include "Rollercoaster.hh"

#include <fstream>
#include <cstdio>

Rollercoaster::Rollercoaster(const std::string& sourcePath)
{
	std::ifstream file(sourcePath);
	std::string line;
	
	if(!file.is_open())
	{
		printf("\u001b[31;1mUnable to open source file '%s'\n", sourcePath.c_str());
		return;
	}

	while(std::getline(file, line))
		lines.emplace_back(std::move(line));
}

const std::string& Rollercoaster::getCharacters(Syntax syntax)
{
	static std::string sets[]
	{
		"+-<>[].,"	//	Brainfuck
	};

	return sets[static_cast <size_t> (syntax)];
}

bool Rollercoaster::parse(Syntax syntax)
{
	if(lines.empty())
		return true;

	size_t length = lines[0].size();
	for(size_t i = 1; i < lines.size(); i++)
	{
		if(lines[i].size() != length)
		{
			printf("\u001b[31;1mLine %lu length mismatches (Is %lu, should be %lu)\n", i, lines[i].size(), length);
			return false;
		}
	}

	const std::string& charset = getCharacters(syntax);

	bool isOriginValid = lines[0][0] == '_' || lines[0][0] == '/' || lines[0][0] == '\\';

	size_t x = isOriginValid ? 0 : 1;
	size_t y = 0;

	for(size_t i = x; i < length; i++)
	{
		char ch = lines[y][x];

		if(ch == '_')
		{
			if(y >= charset.size())
			{
				printf("\u001b[31;1mNo characters available this deep on line %lu column %lu\n", y, x);
				return false;
			}

			x++;
			output += charset[y];
		}

		else if(ch == '/')
		{
			if(--y >= lines.size())
				y = lines.size() - 1;

			x++;
		}

		else if(ch == '\\' && y == 0)
		{
			x++;
		}

		else
		{
			size_t below = y + 1;
			if(below >= lines.size())
				below = 0;

			if(lines[below][x] == '\\')
			{
				y = below;
				x++;
			}

			else
			{
				printf("\u001b[31;1mInvalid character '%c' on line %lu column %lu\n", ch, y + 1, x + 1);
				return false;
			}
		}
	}

	return true;
}
