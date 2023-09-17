#pragma once


#ifdef SD_PLATFORM_WIN

extern Soda::App* Soda::CreateApp();

int main(int argc, char** argv)
{
	Soda::Log::Init();
	
	SD_INFO("HAMSTERS ARE CUTE!");
	SD_CORE_WARN("UGHH THIS IS GONNA BE A SANITY DRAINING PROCESS...");
	SD_ERROR("HUH!!!");
	SD_CORE_FATAL("UH HUHHH!!!");
	SD_MSG("okk......");
	SD_CORE_TRACE("there we go.");
	
	auto app = Soda::CreateApp();
	app->Run();
	delete app;
}

#endif