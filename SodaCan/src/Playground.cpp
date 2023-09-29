#include "Soda.h"


class SampleLayer : public Soda::Layer
{
public:
	SampleLayer()
		: Layer("Sample")
	{}

	void OnEvent(Soda::Event& event) override
	{
		// uncoment this if you wanna see what event was called
		/* SD_MSG("{0}", event); */
	}
};


class Playground : public Soda::App
{
public:
	Playground()
	{
		PushLayer(new SampleLayer());
		PushOverlay(new Soda::ImGuiLayer());
	}
	
	~Playground()
	{
	}
};

Soda::App* Soda::CreateApp()
{
	return new Playground();
}