#include "Soda.h"


class SampleLayer : public Soda::Layer
{
public:
	SampleLayer()
		: Layer("Sample")
	{}

	void OnUpdate() override
	{

	}

	void OnEvent(Soda::Event& event) override
	{
		if(event.GetEventType() == Soda::EventType::KeyPress)
		{
			Soda::KeyPressEvent& keyEvent = (Soda::KeyPressEvent&)event;
			SD_MSG("{0}", (char)keyEvent.GetKeyCode());

			if(Soda::Input::IsKeyPressed(SD_KEY_TAB))
				SD_MSG("{0}, is pressed", "Menu");
		}
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