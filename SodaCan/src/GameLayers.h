#pragma once

#include <Soda.h>


class SampleLayer : public Soda::Layer
{
public:
	SampleLayer();

	virtual void OnEvent(Soda::Event& e) override;
	virtual void OnUpdate(Soda::Timestep ts) override;

	virtual void OnImGuiUpdate() override;

private:
	Soda::OrthoCamera m_Camera;

	std::shared_ptr<Soda::Shader> m_positionColor;
	std::shared_ptr<Soda::Shader> m_BasicShader;
	std::shared_ptr<Soda::Shader> m_TextureShader;

	std::shared_ptr<Soda::Texture2D> m_Texture;

	std::shared_ptr<Soda::VertexArray> m_VA;
	std::shared_ptr<Soda::VertexArray> m_squareVA;

private:
	uint32_t FPS = 0.0f;

	glm::vec3 camPosition = { 0.0f, 0.0f, 0.0f };
	float camRotation = 0.0f;
	float camSpeed = 40.0f;

	glm::vec3 boxPosition = { 0.7f, 0.5f, 0.0f };
	float boxRotation = 0.0f;
	glm::vec3 boxScale = glm::vec3(1.5);
	glm::mat4 boxTransform;

	glm::vec4 color = { 0.9f, 0.6f, 0.2f, 1.0f };


	glm::vec3 playerPos = { -1.0f, 0.0f, 0.0f };
	float playerRotation = 0.0f;
	glm::vec3 playerScale = { 0.5f, 0.5f, 0.5f };
	glm::mat4 playerTransform;

	float playerSpeed = 20.0f;
};