#include "stdafx.h"
#include "AbstractShape.h"
#include "ShapePresenter.h"
#include "Reseiver.h"

CShape::CShape(ShapeType type)
	: m_type(type)
{}

ShapeType CShape::GetType() const
{
	return m_type;
}

bool CShape::IsPointIntoShape(Vec2 const & point) const
{
	return false;
}

bool CShape::OnMousePressed(sf::Event::MouseButtonEvent const & event)
{
	if (IsPointIntoShape({ double(event.x), double(event.y) }))
	{
		auto position = GetBoundingRect().position;
		m_offset = { position.x - double(event.x), position.y - double(event.y)};
		m_isMoved = true;
		return true;
	}
	return false;
}

bool CShape::OnMouseReleased(sf::Event::MouseButtonEvent const & event)
{
	if (m_isMoved)
	{
		m_isMoved = false;
		return true;
	}
	return false;
}

bool CShape::OnMouseMoved(sf::Event::MouseMoveEvent const & event)
{
	if (m_isMoved)
	{
		SetPosition({ double(event.x) + m_offset.x, double(event.y) + m_offset.y });
		SetInAllowableArea();
		return true;
	}
	return false;
}

bool CShape::IsMooved() const
{
	return m_isMoved;
}

void CShape::SetAllowableArea(CBoundingRect const & rect)
{
	m_allowableArea = rect;
}

CBoundingRect const & CShape::GetAllowableArea() const
{
	return m_allowableArea;
}

void CShape::SetBoundingRect(CBoundingRect const& rect)
{
	CLayer::SetBoundingRect(rect);
	m_onProgramChangeRect();
}

boost::signals2::scoped_connection CShape::DoOnProgramChangeRect(std::function<void()> const & action)
{
	return m_onProgramChangeRect.connect(action);
}

boost::signals2::scoped_connection CShape::DoOnChangeRect(std::function<void()> const & action)
{
	return m_onChangeRect.connect(action);
}

void CShape::OnChangeRect()
{
	m_onChangeRect();
}

void CShape::SetPresenter(std::shared_ptr<CShapePresenter> const & presenter)
{
	m_presenter = presenter;
}

void CShape::SetInAllowableArea()
{
	auto position = GetPosition();
	auto size = GetSize();
	position.x = std::min(std::max(position.x, m_allowableArea.position.x), m_allowableArea.position.x + m_allowableArea.size.x - size.x);
	position.y = std::min(std::max(position.y, m_allowableArea.position.y), m_allowableArea.position.y + m_allowableArea.size.y - size.y);
	SetPosition(position);
}
