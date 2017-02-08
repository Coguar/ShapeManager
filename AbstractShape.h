#pragma once
#include "ParentLayer.h"
#include "ShapesTypes.h"

class CShapePresenter;

class CShape 
	: public CSolidLayer
{
public:
	CShape(ShapeType type);
	~CShape() = default;

	ShapeType GetType()const;
	virtual bool IsPointIntoShape(Vec2 const& point)const;

	bool OnMousePressed(sf::Event::MouseButtonEvent const& event) override;
	bool OnMouseReleased(sf::Event::MouseButtonEvent const& event) override;
	bool OnMouseMoved(sf::Event::MouseMoveEvent const& event) override;

	bool IsMooved() const;
	void SetAllowableArea(CBoundingRect const& rect);
	CBoundingRect const& GetAllowableArea() const;

	void SetBoundingRect(CBoundingRect const& rect) override;

	boost::signals2::scoped_connection DoOnProgramChangeRect(std::function<void()> const& action);
	boost::signals2::scoped_connection DoOnChangeRect(std::function<void()> const& action);

	void OnChangeRect();

	void SetPresenter(std::shared_ptr<CShapePresenter> const& presenter);

private:
	void SetInAllowableArea();

	ShapeType m_type;
	bool m_isMoved = false;
	Vec2 m_offset;

	CBoundingRect m_allowableArea;

	std::shared_ptr<CShapePresenter> m_presenter;

	boost::signals2::signal<void()> m_onProgramChangeRect;
	boost::signals2::signal<void()> m_onChangeRect;
};

