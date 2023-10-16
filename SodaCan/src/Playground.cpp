#include "Soda.h"

#include "imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
			-0.5f,  0.5f, 0.0f,		1.0f, 0.9f, 0.8f, // 0
			 0.5f,  0.5f, 0.0f,		1.0f, 0.9f, 0.8f, // 1
			 0.5f, -0.5f, 0.0f,		1.0f, 0.9f, 0.8f, // 2
			-0.5f, -0.5f, 0.0f,		1.0f, 0.9f, 0.8f, // 3

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


		//*** shader ***//
			// vertx. shdr.
		std::string vrtxShdr = R"(
			#version 410 core
			
			layout(location = 0) in vec3 a_vrtxPosition;
			layout(location = 1) in vec3 a_color;
			out vec3 o_objColor;

			uniform mat4 u_PVMat;
			uniform mat4 u_ModelMat;

			void main()
			{
				gl_Position = u_PVMat * u_ModelMat * vec4(a_vrtxPosition, 1.0);
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

			if (Soda::Input::IsKeyPressed(SD_KEY_PERIOD))
				camSpeed += 2.5f;
			else if (Soda::Input::IsKeyPressed(SD_KEY_COMMA) && camSpeed > 5.0)
				camSpeed -= 2.5f;
		}
	}

	void OnImGuiUpdate()
	{
		ImGui::Begin("Stats");
		ImGui::Text("FPS: %d", FPS);
		ImGui::End();


		ImGui::Begin("Camera");
		ImGui::Text("Transform");
		ImGui::DragFloat2("Camera Position", &camPosition.x, 0.1f);
		ImGui::DragFloat("Camera Rotation", &camRotation, 0.1f);
		ImGui::Text("");
		ImGui::Text("Properties");
		ImGui::DragFloat("Camera Speed", &camSpeed, 0.1f);
		ImGui::End();


		ImGui::Begin("Box");
		ImGui::Text("Transform");
		ImGui::DragFloat2("Box Position", &boxPosition.x, 0.1f);
		ImGui::DragFloat("Box Rotation", &boxRotation, 0.1f);
		ImGui::DragFloat2("Box Scale", &boxScale.x, 0.1f);
		ImGui::End();
	}

	void OnUpdate(Soda::Timestep dt) override
	{
		FPS = 1.0f / dt;

		boxTransform = glm::translate(glm::mat4(1.0f), boxPosition) *
			glm::rotate(glm::mat4(1.0f), glm::radians(boxRotation), glm::vec3(0, 0, 1)) *
			glm::scale(glm::mat4(1.0f), boxScale);

		// camera movement
		if (Soda::Input::IsKeyPressed(SD_KEY_UP))
			camPosition.y += 0.1 * camSpeed * dt;
		else if (Soda::Input::IsKeyPressed(SD_KEY_DOWN))
			camPosition.y -= 0.1 * camSpeed * dt;

		if (Soda::Input::IsKeyPressed(SD_KEY_LEFT))
			camPosition.x -= 0.1 * camSpeed * dt;
		else if (Soda::Input::IsKeyPressed(SD_KEY_RIGHT))
			camPosition.x += 0.1 * camSpeed * dt;


		if (Soda::Input::IsKeyPressed(SD_KEY_KP_SUBTRACT))
			camRotation += 180.0 * dt;
		else if (Soda::Input::IsKeyPressed(SD_KEY_KP_ADD))
			camRotation -= 180.0 * dt;


		Soda::Renderer::StartScene(m_Camera);
		{
			Soda::RenderCommand::ClearScreen();

			m_Camera.SetPosition(camPosition);
			m_Camera.SetRotation(camRotation);

			Soda::Renderer::PushThis(m_squareVA, m_BasicShader, boxTransform);
			Soda::Renderer::PushThis(m_VA, m_BasicShader);
		}
		Soda::Renderer::StopScene();
	}

private:
	Soda::OrthoCamera m_Camera;

	std::shared_ptr<Soda::Shader> m_BasicShader;

	std::shared_ptr<Soda::VertexArray> m_VA;
	std::shared_ptr<Soda::VertexArray> m_squareVA;

private:
	uint32_t FPS = 0.0f;

	glm::vec3 camPosition = {0.0f, 0.0f, 0.0f};
	float camRotation = 0.0f;
	float camSpeed = 25.0f;

	glm::vec3 boxPosition = { 0.0f, 0.0f, 0.0f };
	float boxRotation = 0.0f;
	glm::vec3 boxScale = glm::vec3(1.5);
	glm::mat4 boxTransform;
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