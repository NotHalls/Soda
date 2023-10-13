#include "Soda.h"

#include "imgui.h"

class SampleLayer : public Soda::Layer
{
public:
	SampleLayer()
		: Layer("Sample")
	{}


	void OnEvent(Soda::Event& event) override
	{
		if(event.GetEventType() == Soda::EventType::KeyPress)
		{
			Soda::KeyPressEvent& keyEvent = (Soda::KeyPressEvent&)event;
			SD_LOG("{0}", (char)keyEvent.GetKeyCode());

			if(Soda::Input::IsKeyPressed(SD_KEY_TAB))
				SD_LOG("{0}, is pressed", "Menu");

			
			Soda::MouseButtonEvent& mouseEvent = (Soda::MouseButtonEvent&)event;

			if(Soda::Input::IsMouseClicked(SD_MOUSE_BUTTON_0))
				SD_LOG("{0}, was clicked", mouseEvent.GetButtonClicked());
		}
	}
};


class Playground : public Soda::App
{
public:
	Playground()
	{
		PushLayer(new SampleLayer());
	}
	
	~Playground()
	{
	}
};

Soda::App* Soda::CreateApp()
{
	return new Playground();
}