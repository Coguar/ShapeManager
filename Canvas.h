#pragma once
#include "AbstractShape.h"

class CCanvas : public CLayer

{
public:
	CCanvas();
	~CCanvas();

	std::shared_ptr<CShape> CreateShape(ShapeType type);
	std::vector<std::shared_ptr<CShape>> const& GetShapes()const;
	bool OnEvent(sf::Event const& event) override;

private:
	void SetShape(std::shared_ptr<CShape> const& shape);
	std::vector<std::shared_ptr<CShape>> m_shapes;
};

