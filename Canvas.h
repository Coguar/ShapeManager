#pragma once
#include "SelectFrame.h"

class SModelShape;

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
	void SetNewShapesList(std::vector<std::shared_ptr<SModelShape>> const& shapes);
	void Clear();

	void Draw(sf::RenderTarget * window, CTextureCache * cache) override;

	void DoOnShapeRectChanged(std::function<void(size_t, const CBoundingRect&)> const& action);

protected:
	bool OnMousePressed(sf::Event::MouseButtonEvent const & event) override;

private:
	std::shared_ptr<CShape> CreateShape(std::shared_ptr<SModelShape> const& data);

	void ShapeChangeRectEvent(std::shared_ptr<CShape> const& shape, sf::Event const& event);
	void ChangeShapeRect();

	std::vector<std::shared_ptr<CShape>> m_shapes;
	std::shared_ptr<CSelectFrame> m_frame;

	CBoundingRect m_oldSelectShapeRect;
	size_t m_targetShapePosition = 0;

	boost::signals2::signal<void(size_t, const CBoundingRect&)> m_onShapesRectChange;
};

