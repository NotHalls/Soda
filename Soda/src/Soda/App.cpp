// A SMALL TIP
// if there is a cpp file and also a header file, then check the header file to know more about what a function does


#include "SD_PCH.h"

#include "Core.h"

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

		glGenVertexArrays(1, &arrayBufferID);
		glBindVertexArray(arrayBufferID);

		float vertices[3 * 6]
		{
			 0.0f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f, // 0
			-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f, // 1
			 0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f, // 2
		};
		int indices[3]
		{
			0, 1, 2
		};

		m_VB.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		m_VB->Bind();

		m_IB.reset(IndexBuffer::Create(indices, sizeof(indices)));
		m_IB->Bind();

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));


		// shader code
			// vertx. shdr.
		std::string vrtxShdr = R"(
			#version 410 core
			
			layout(location = 0) in vec3 a_vrtxPosition;
			layout(location = 1) in vec3 a_color;
			out vec3 o_objColor;

			void main()
			{
				gl_Position = vec4(a_vrtxPosition, 1.0);
				o_objColor = a_color;
			}
		)";

		std::string fragShdr = R"(
			#version 410 core

			layout(location = 0) out vec4 o_Color;
			in vec3 o_objColor;

			void main()
			{
				o_Color = vec4(o_objColor, 1.0);
			}
		)";

		m_BasicShader.reset(new Shader(vrtxShdr, fragShdr));
	}

	App::~App()
	{}


	// this function takes the event it was called with in the callback function
	// and dispatches the right function for that event
	void App::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_FN(App::OnWindowClose));

		for (auto itr = m_LayerStack.end(); itr != m_LayerStack.begin();)
		{
			(*--itr)->OnEvent(event);

			if (event.m_Handled)
				break;
		}
	}

	void App::Run()
	{
		// our main gameloop (engineloop i guess)
		while (IsRunning)
		{
			glBindVertexArray(arrayBufferID);
			m_BasicShader->Bind();


			glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_imguiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiUpdate();
			m_imguiLayer->End();

			m_MainWindow->OnUpdate();
		}
	}

	void App::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void App::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool App::OnWindowClose(WindowCloseEvent& _WindowCloseEvent)
	{
		IsRunning = false;
		return true;
	}
}