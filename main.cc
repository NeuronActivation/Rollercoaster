#include "Rollercoaster.hh"

int main(int argc, char** argv)
{
	Rollercoaster rc(argc < 2 ? "" : argv[1]);
	rc.parse(Rollercoaster::Syntax::Brainfuck);

	printf("%s\n", rc.getOutput().c_str());
}
