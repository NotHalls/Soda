// A SMALL TIP
// if there is a cpp file and also a header file, then check the header file to know more about what a function does


#include "SD_PCH.h"

#include "Core.h"

#include "App.h"

#include "Renderer/Render.h"


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


		m_VA.reset(VertexArray::Create());


		//*** Obj 1 ***//

		float vertices[3 * 6]
		{
			 0.0f,  0.5f, 0.0f,		1.0f,  0.25f, 0.25f, // 0
			-0.5f, -0.5f, 0.0f,		0.25f, 1.0f,  0.25f, // 1
			 0.5f, -0.5f, 0.0f,		0.25f, 0.25f, 1.0f, // 2
		};
		int indices[3]
		{
			0, 1, 2
		};

		std::shared_ptr<VertexBuffer> m_VB;
		m_VB.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		m_VB->Bind();

		std::shared_ptr<IndexBuffer> m_IB;
		m_IB.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(int)));
		m_IB->Bind();



		BufferLoadout loadout = {
			{ "a_position", ShaderDataType::Vec3 },
			{ "a_color", ShaderDataType::Vec3 }
		};

		m_VB->SetLoadout(loadout);

		m_VA->AddVertexBuffer(m_VB);
		m_VA->AddIndexBuffer(m_IB);

		//***/ Obj 1 /***//


		//*** Obj 2 ***//

		m_squareVA.reset(VertexArray::Create());

		float squareVertices[4 * 6]
		{
			-0.65f,  0.65f, 0.0f,		1.0f, 0.9f, 0.8f, // 0
			 0.65f,  0.65f, 0.0f,		1.0f, 0.9f, 0.8f, // 1
			 0.65f, -0.65f, 0.0f,		1.0f, 0.9f, 0.8f, // 2
			-0.65f, -0.65f, 0.0f,		1.0f, 0.9f, 0.8f, // 3

		};
		int squareIndices[6]
		{
			0, 1, 2, 0, 2, 3
		};

		BufferLoadout SquareLoadout = {
			{ "a_squarePosition", ShaderDataType::Vec3 },
			{ "a_squareColor", ShaderDataType::Vec3 }
		};

		std::shared_ptr<VertexBuffer> m_squareVB;
		m_squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		m_squareVB->Bind();

		std::shared_ptr<IndexBuffer> m_squareIB;
		m_squareIB.reset(IndexBuffer::Create(squareIndices, 24));
		m_squareIB->Bind();

		m_squareVB->SetLoadout(SquareLoadout);

		m_squareVA->AddVertexBuffer(m_squareVB);
		m_squareVA->AddIndexBuffer(m_squareIB);

		//***/ Obj 2 /***//



		//*** shader ***//
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
			m_BasicShader->Bind();

			Renderer::StartRenderer();
			{
				RenderCommand::ClearScreen();

				Renderer::PushThis(m_squareVA);
				Renderer::PushThis(m_VA);
			}
			Renderer::StopRenderer();

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