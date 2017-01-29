#pragma once
#include "SelectFrame.h"
#include "ViewEvent.h"

struct SModelShape;

class CCanvas : public CParentLayer
{
public:
	CCanvas();
	~CCanvas();

	bool OnEvent(sf::Event const& event) override;

	std::shared_ptr<CSelectFrame> const& GetFSelectFrame() const;
	size_t GetSelectedShapeNum() const;

	void AddShape(std::shared_ptr<SModelShape> const& shape, size_t pos);
	void DeleteShape(size_t pos);
	void UpdateShape(size_t pos, CBoundingRect const& rect);
	void SetNewShapesList(std::vector<std::shared_ptr<SModelShape>> const& shapes);
	void Clear();

	void Update() override;
	void Draw(sf::RenderTarget * window, CTextureCache * cache) override;

	SEvent GetLastEvent();
protected:
	bool OnMousePressed(sf::Event::MouseButtonEvent const & event) override;

private:
	std::shared_ptr<CShape> CreateShape(SModelShape const& data);

	void ShapeChangeRectEvent(std::shared_ptr<CShape> const& shape, sf::Event const& event);

	std::vector<std::shared_ptr<CShape>> m_shapes;
	std::shared_ptr<CSelectFrame> m_frame;

	CBoundingRect m_oldSelectShapeRect;
	size_t m_targetShapePosition = 0;
	SEvent m_event;
};

