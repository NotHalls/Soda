#pragma once


#ifdef CT_PLATFORM_WIN

extern CE::App* CE::CreateApp();

int main(int argc, char** argv)
{
	auto app = CE::CreateApp();
	app->Run();
	delete app;
}

#endif