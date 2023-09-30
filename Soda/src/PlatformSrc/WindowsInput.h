#pragma once

#include "SD_PCH.h"

#include "Soda/Core.h"

#include "Soda/Input.h"


namespace Soda
{
	class SD_DLL WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		
		virtual bool IsMouseClickedImpl(int keycode) override;
		virtual std::pair<float, float> GetMousePosImpl() override;
	};
}