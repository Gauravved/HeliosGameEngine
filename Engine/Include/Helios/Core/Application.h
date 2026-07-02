#pragma once
#include<memory>

#include<Helios/Window/Window.h>
//defining application namespace 
namespace Helios{
	class Application {
	private:
		bool m_Running = true;
		std::unique_ptr<Helios::Window> m_Window;
	public:
		Application();
		virtual ~Application();
		void Run();

	};
}