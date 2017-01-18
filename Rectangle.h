#pragma once
#include "RectangleInterface.h"

class CRectangle : public IRectangle
{
public:
	CRectangle() = default;
	CRectangle(SCoords const& positon, SSize const& size);
	~CRectangle() = default;

	bool IsPointIntoRect(SCoords const& point) override;
	SSize GetSize() const override;
	SCoords GetPosition() const override;
	void SetSize(SSize const& size) override;
	void SecPosition(SCoords const& position) override;

private:

	SCoords m_position;
	SSize m_size;
};

