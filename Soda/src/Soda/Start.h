#pragma once


#ifdef SD_PLATFORM_WIN

extern Soda::App* Soda::CreateApp();

int main(int argc, char** argv)
{
	Soda::Log::Init();
	
	SD_ENGINE_INFO("CORE LOG");
	SD_INFO("USER LOG");
	
	auto app = Soda::CreateApp();
	app->Run();
	delete app;
}

#endif