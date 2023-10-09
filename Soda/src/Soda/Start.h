#pragma once

// this is the main function in the project
// this is where the Engine starts from


// for Windows systems
#ifdef SD_PLATFORM_WIN

extern Soda::App* Soda::CreateApp();

int main(int argc, char** argv)
{
	Soda::Log::Init();
	
	SD_ENGINE_LOG("CORE LOG");
	SD_LOG("USER LOG");
	
	// creating an app and executing it
	auto app = Soda::CreateApp();
	app->Run();
	delete app;
}

#endif