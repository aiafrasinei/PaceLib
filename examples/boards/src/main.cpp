#define SDL_MAIN_HANDLED
#include "core/Init.hpp"

using namespace PaceLib;


Init *starter = nullptr;

bool init()
{
	Root *root = starter->GetRoot();

	Tabber::BeginBlock("Bag");
		Tabber::BeginTabBlock("Chess");
		Tabber::EndTabBlock();

		Tabber::BeginTabBlock("Shogi");
		Tabber::EndTabBlock();

		Tabber::BeginTabBlock("Go");
		Tabber::EndTabBlock();
	Tabber::EndBlock();


	return true;
}

int main(int argc, const char *argv[])
{
	starter = new Init();

	starter->onInit = &init;
	
	starter->Loop();

    return 0;
}
