#include <Helios/Core/Application.h>
#ifdef _WIN32
#include<Windows.h>
extern "C"
{
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

int main() {
	Helios::Application application;
	application.Run();
	return 0;
}