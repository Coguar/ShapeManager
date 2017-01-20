#pragma once
#include "CanvasInterface.h"
#include "Layer.h"
class CCanvas 
		: public ICanvas
		, public CLayer

{
public:
	CCanvas();
	~CCanvas();

	std::shared_ptr<CShape> CreateShape(ShapeType type) override;
	std::vector<std::shared_ptr<CShape>> const& GetShapes()const override;
	bool OnEvent(sf::Event const& event) override;

private:
	void SetShape(std::shared_ptr<CShape> const& shape);
	std::vector<std::shared_ptr<CShape>> m_shapes;
};

