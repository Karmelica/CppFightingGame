#include <iostream>
#include <thread>

#include "Core.h"

using namespace std::chrono_literals;

int main()
{
	Core* core = new Core();
	core->Start();
	do
	{
		clock_t time = clock();
		std::this_thread::sleep_for(0.016s);
		time = clock() - time;
		float ms = static_cast<float>(time) / CLOCKS_PER_SEC * 1000;
		core->Update(ms/1000.f);

	} while(!core->LoopEnded);
	core->End();
	return 0;
}
