#include "Soda.h"

#include "imgui.h"

class SampleLayer : public Soda::Layer
{
public:
	SampleLayer()
		: Layer("Sample"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		m_VA.reset(Soda::VertexArray::Create());


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

		std::shared_ptr<Soda::VertexBuffer> m_VB;
		m_VB.reset(Soda::VertexBuffer::Create(vertices, sizeof(vertices)));
		m_VB->Bind();

		std::shared_ptr<Soda::IndexBuffer> m_IB;
		m_IB.reset(Soda::IndexBuffer::Create(indices, sizeof(indices) / sizeof(int)));
		m_IB->Bind();



		Soda::BufferLoadout loadout = {
			{ "a_position", Soda::ShaderDataType::Vec3 },
			{ "a_color", Soda::ShaderDataType::Vec3 }
		};

		m_VB->SetLoadout(loadout);

		m_VA->AddVertexBuffer(m_VB);
		m_VA->AddIndexBuffer(m_IB);

		//***/ Obj 1 /***//


		//*** Obj 2 ***//

		m_squareVA.reset(Soda::VertexArray::Create());

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

		Soda::BufferLoadout SquareLoadout = {
			{ "a_squarePosition", Soda::ShaderDataType::Vec3 },
			{ "a_squareColor", Soda::ShaderDataType::Vec3 }
		};

		std::shared_ptr<Soda::VertexBuffer> m_squareVB;
		m_squareVB.reset(Soda::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		m_squareVB->Bind();

		std::shared_ptr<Soda::IndexBuffer> m_squareIB;
		m_squareIB.reset(Soda::IndexBuffer::Create(squareIndices, 24));
		m_squareIB->Bind();

		m_squareVB->SetLoadout(SquareLoadout);

		m_squareVA->AddVertexBuffer(m_squareVB);
		m_squareVA->AddIndexBuffer(m_squareIB);

		//***/ Obj 2 /***//


		//*** Obj 3 ***//

		m_sA.reset(Soda::VertexArray::Create());

		float sVertices[4 * 6]
		{
			 1.6f,   0.0f, 0.0f,		0.0f, 0.9f, 0.8f, // 0
			 2.0f,   0.0f, 0.0f,		0.0f, 0.9f, 0.8f, // 1
			 2.0f,  -0.1f, 0.0f,		0.0f, 0.9f, 0.8f, // 2
			 1.6f,  -0.1f, 0.0f,		0.0f, 0.9f, 0.8f, // 3

		};
		int sIndices[6]
		{
			0, 1, 2, 0, 2, 3
		};

		Soda::BufferLoadout sLoadout = {
			{ "a_sPosition", Soda::ShaderDataType::Vec3 },
			{ "a_sColor", Soda::ShaderDataType::Vec3 }
		};

		std::shared_ptr<Soda::VertexBuffer> m_sVB;
		m_sVB.reset(Soda::VertexBuffer::Create(sVertices, sizeof(sVertices)));
		m_sVB->Bind();

		std::shared_ptr<Soda::IndexBuffer> m_sIB;
		m_sIB.reset(Soda::IndexBuffer::Create(sIndices, 24));
		m_sIB->Bind();

		m_sVB->SetLoadout(sLoadout);

		m_sA->AddVertexBuffer(m_sVB);
		m_sA->AddIndexBuffer(m_sIB);

		//***/ Obj 3 /***//


		//*** shader ***//
			// vertx. shdr.
		std::string vrtxShdr = R"(
			#version 410 core
			
			layout(location = 0) in vec3 a_vrtxPosition;
			layout(location = 1) in vec3 a_color;
			out vec3 o_objColor;

			uniform mat4 u_PVMat;

			void main()
			{
				gl_Position = u_PVMat * vec4(a_vrtxPosition, 1.0);
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

		m_BasicShader.reset(new Soda::Shader(vrtxShdr, fragShdr));
	}


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


	void OnUpdate(Soda::Timestep dt) override
	{
		SD_LOG(dt);

		if (Soda::Input::IsKeyPressed(SD_KEY_W))
			camPosition.y += 0.1 * camSpeed * dt;
		else if (Soda::Input::IsKeyPressed(SD_KEY_S))
			camPosition.y -= 0.1 * camSpeed * dt;

		if (Soda::Input::IsKeyPressed(SD_KEY_A))
			camPosition.x -= 0.1 * camSpeed * dt;
		else if (Soda::Input::IsKeyPressed(SD_KEY_D))
			camPosition.x += 0.1 * camSpeed * dt;


		if (Soda::Input::IsKeyPressed(SD_KEY_Q))
			camRotation += 180.0 * dt;
		else if (Soda::Input::IsKeyPressed(SD_KEY_E))
			camRotation -= 180.0 * dt;


		// suggest not using these right now
		if (Soda::Input::IsKeyPressed(SD_KEY_PERIOD))
			camSpeed += 2.5f;
		else if (Soda::Input::IsKeyPressed(SD_KEY_COMMA) && camSpeed > 5.0)
			camSpeed -= 2.5f;


		Soda::Renderer::StartScene(m_Camera);
		{
			Soda::RenderCommand::ClearScreen();

			m_Camera.SetPosition(camPosition);
			m_Camera.SetRotation(camRotation);

			Soda::Renderer::PushThis(m_sA, m_BasicShader);
			Soda::Renderer::PushThis(m_squareVA, m_BasicShader);
			Soda::Renderer::PushThis(m_VA, m_BasicShader);
		}
		Soda::Renderer::StopScene();
	}

private:
	Soda::OrthoCamera m_Camera;

	std::shared_ptr<Soda::Shader> m_BasicShader;

	std::shared_ptr<Soda::VertexArray> m_VA;
	std::shared_ptr<Soda::VertexArray> m_squareVA;
	std::shared_ptr<Soda::VertexArray> m_sA;

private:
	glm::vec3 camPosition = {0.0f, 0.0f, 0.0f};
	float camRotation = 0.0f;

	float camSpeed = 25.0f;
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