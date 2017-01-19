#pragma once
#include <functional>
#include "Signal.h"


struct IButton
{
	virtual void SetAction(signal::Signal<void()>::slot_type const& action) = 0;

	virtual ~IButton() = default;
};