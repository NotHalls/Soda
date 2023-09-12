#include <stdio.h>

#include <CE.h>


class Playground : public CE::App
{
public:
	Playground()
	{
	}

	~Playground()
	{
	}
};

CE::App* CE::CreateApp()
{
	return new Playground();
}