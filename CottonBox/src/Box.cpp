#include <CE.h>


class CBox : public CE::App
{
public:
	CBox()
	{
	}

	~CBox()
	{
	}
};

CE::App* CE::CreateApp()
{
	return new CBox();
}