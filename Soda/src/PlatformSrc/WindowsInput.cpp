#include "SD_PCH.h"

#include "WindowsInput.h"

#include "Soda/_Main/App.h"

#include "GLFW/glfw3.h"


namespace Soda
{
	Input* Input::s_Input = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(App::Get().App::GetWindow().GetTheWindow());

		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}


	bool WindowsInput::IsMouseClickedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(App::Get().App::GetWindow().GetTheWindow());

		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(App::Get().App::GetWindow().GetTheWindow());

		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return { (float)xPos, (float)yPos };
	}
}