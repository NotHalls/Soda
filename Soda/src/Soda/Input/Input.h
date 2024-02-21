#pragma once

#include "SD_PCH.h"

#include "Soda/_Main/Core.h"


namespace Soda
{
	class Input
	{
	public:
		inline static bool IsKeyPressed(int keycode)
		{ return s_Input->IsKeyPressedImpl(keycode); }

		
		inline static bool IsMouseClicked(int button)
		{ return s_Input->IsMouseClickedImpl(button); }

		inline static std::pair<float, float> GetMousePos()
		{ return s_Input->GetMousePosImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseClickedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;
	private:
		static Input* s_Input;
	};
}