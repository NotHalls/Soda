#pragma once

#include "SD_PCH.h"

#include "Soda/_Main/Core.h"

#include "Soda/Input/Input.h"


namespace Soda
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		
		virtual bool IsMouseClickedImpl(int keycode) override;
		virtual std::pair<float, float> GetMousePosImpl() override;
	};
}