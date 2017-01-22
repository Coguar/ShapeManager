#pragma once
#include "SelectFrame.h"

class CCanvas : public CParentLayer
{
public:
	CCanvas();
	~CCanvas();

	std::shared_ptr<CShape> CreateShape(ShapeType type);

	void AddShape(std::shared_ptr<CShape> const& shape);
	void AddShape(std::shared_ptr<CShape> const& shape, size_t position);
	void DeleteLastShape();
	void DeleteShapeByPosition(size_t position);
	bool DeleteSelectedShape();

	std::vector<std::shared_ptr<CShape>> const& GetShapes()const;
	bool OnEvent(sf::Event const& event) override;
	bool OnMousePressed(sf::Event::MouseButtonEvent const & event) override;

	std::shared_ptr<CSelectFrame> const& GetFSelectFrame() const;
private:
	void ShapeChangeRectEvent(std::shared_ptr<CShape> const& shape, sf::Event const& event);

	void SetShape(std::shared_ptr<CShape> const& shape);
	std::vector<std::shared_ptr<CShape>> m_shapes;
	std::shared_ptr<CSelectFrame> m_frame;

	CBoundingRect m_oldSelectShapeRect;

	size_t m_targetShapePosition = 0;
};

