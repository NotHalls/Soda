#pragma once


#ifdef CT_PLATFORM_WIN

extern CE::App* CE::CreateApp();

int main(int argc, char** argv)
{
	CE::Log::Init();
	
	CT_INFO("HAMSTERS ARE CUTE!");
	CT_CORE_WARN("UGHH THIS IS GONNA BE A SANITY DRAINING PROCESS...");
	CT_ERROR("HUH!!!");
	CT_CORE_FATAL("UH HUHHH!!!");
	CT_DEBUG("okk......");
	
	auto app = CE::CreateApp();
	app->Run();
	delete app;
}

#endif