
#ifdef HM_PLATFORM_WINDOWS
#include "Core.h"
#include  "BubbleBobble.h"
#undef main
int main(int, char[])
{
	auto engine = HiveMind::BubbleBobble{};
	engine.Run();
	return 0;

}
#endif