#pragma once

#include "Soda.h"

class SodaCan2D : public Soda::Layer
{
public:
	SodaCan2D();
    virtual ~SodaCan2D() = default;

    void OnAttach() override;
    void OnDetach() override;

	void OnUpdate(Soda::Timestep dt) override;
	void OnEvent(Soda::Event& event) override;
	void OnImGuiUpdate() override;

private:
    Soda::OrthoCameraController m_CameraController;

    std::shared_ptr<Soda::Texture2D> m_BoxTexture;

    // temp, this will std::shared_ptr<Soda::Sprite> m_Sprite;
    std::shared_ptr<Soda::VertexArray> m_BoxVA;
    std::shared_ptr<Soda::Shader> m_Shader2D;
private:    
    glm::mat4 m_BoxTransform = glm::mat4(1.0f);
    glm::vec3 m_BoxPosition = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_BoxScale = { 1.0f, 1.0f, 1.0f };
    float m_BoxRotation = 0.0f;
    glm::vec4 m_BoxColor = { 0.8f, 0.2f, 0.3f, 1.0f };
};