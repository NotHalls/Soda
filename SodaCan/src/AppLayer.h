#pragma once

#include "Soda.h"


namespace Soda
{
    class SodaCan : public Layer
    {
    public:
        SodaCan();
        virtual ~SodaCan() = default;

        void OnAttach() override;
        void OnDetach() override;

        void OnUpdate(Timestep dt) override;
        void OnEvent(Event& event) override;
        void OnImGuiUpdate() override;

    private:
        OrthoCameraController m_CameraController;

        Ref<Texture2D> m_BoxTexture;

        // could make a Object2D class to store all of this data
        Ref<VertexArray> m_BoxVA;
        Ref<Shader> m_Shader2D;

        Ref<Framebuffer> m_Framebuffer;
    private:
        glm::vec3 m_BoxPosition = { 0.0f, 0.0f, 0.1f };
        glm::vec2 m_BoxScale = { 1.0f, 1.0f };
        float m_BoxRotation = 0.0f;
        glm::vec4 m_BoxColor = { 0.8f, 0.2f, 0.3f, 1.0f };

        float m_GradFactor = 5.0f;
        float m_MulFactor = 1.0f;

    private:
        glm::vec2 m_ViewportSize = glm::vec2(0.0f);

    private:
        enum Settings : char
        {
            None = 0,
            EnableRendererStats = BIT(0),
            ADD_SOMETHING_HERE  = BIT(1) // for future settings
        };
        Settings m_DefaultSettings = Settings::None;

        void toggoleSetting(Settings& defaultSetting, Settings settingToToggle)
        { defaultSetting = static_cast<Settings>(defaultSetting ^ settingToToggle); }
    };
}