#include "Soda.h"


class Playground : public Soda::App
{
public:
	Playground()
	{
	}
	
	~Playground()
	{
	}
};

Soda::App* Soda::CreateApp()
{
	return new Playground();
}