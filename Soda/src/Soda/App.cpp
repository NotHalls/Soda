// A SMALL TIP
// if there is a cpp file and also a header file, then check the header file to know more about what a function does


#include "SD_PCH.h"

#include "App.h"

#include "glad/glad.h"


namespace Soda
{
	App* App::m_app = nullptr;

	App::App()
	{
		SD_ENGINE_ASSERT(!m_app, "App already exists!");
		m_app = this;

		m_MainWindow = std::unique_ptr<SodaWindow>(SodaWindow::Create());
		m_MainWindow->SetCallbackFn(BIND_FN(App::OnEvent));

		m_imguiLayer = new ImGuiLayer();
		PushOverlay(m_imguiLayer);

		unsigned int id;
		glGenVertexArrays(1, &id);
	}

	App::~App()
	{}


	// this function takes the event it was called with in the callback function
	// and dispatches the right function for that event
	void App::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_FN(App::OnWindowClose));

		for(auto itr = m_LayerStack.end(); itr != m_LayerStack.begin();)
		{
			(*--itr)->OnEvent(event);

			if(event.m_Handled)
				break;
		}
	}

	void App::Run()
	{
		// our main gameloop (engineloop i guess)
		while (IsRunning)
		{
			glClearColor(1.0f, 0.8f, 0.4f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			for(Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_imguiLayer->Begin();
				for(Layer* layer : m_LayerStack)
					m_imguiLayer->OnImGuiRender();
			m_imguiLayer->End();

			m_MainWindow->OnUpdate();
		}
	}

	void App::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}
	void App::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	bool App::OnWindowClose(WindowCloseEvent& _WindowCloseEvent)
	{
		IsRunning = false;
		return true;
	}
}