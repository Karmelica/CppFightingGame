#include <thread>

#include "Core.h"

using namespace std::chrono_literals;

int main()
{
	Core* core = new Core();
	core->Start();
	do
	{
		std::this_thread::sleep_for(0.016s);
		core->Update();
	} while(!core->LoopEnded);
	core->End();
	return 0;
}
