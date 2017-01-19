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

	std::shared_ptr<CAbstractShape> CreateShape(shape::Type type) override;
	std::vector<std::shared_ptr<CAbstractShape>> const& GetShapes()const override;
	bool OnEvent(sf::Event const& event) override;

private:
	void SetShape(std::shared_ptr<CAbstractShape> & shape);
	std::vector<std::shared_ptr<CAbstractShape>> m_shapes;
};

