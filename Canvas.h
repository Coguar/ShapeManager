#pragma once
#include "SelectFrame.h"
//#include "AbstractShape.h"

class CCanvas : public CLayer

{
public:
	CCanvas();
	~CCanvas();

	std::shared_ptr<CShape> CreateShape(ShapeType type);
	std::vector<std::shared_ptr<CShape>> const& GetShapes()const;
	bool OnEvent(sf::Event const& event) override;
	bool OnMousePressed(sf::Event::MouseButtonEvent const & event) override;

	std::shared_ptr<CSelectFrame> const& GetFSelectFrame() const;
private:
	void SetShape(std::shared_ptr<CShape> const& shape);
	std::vector<std::shared_ptr<CShape>> m_shapes;
	std::shared_ptr<CSelectFrame> m_frame;
};

