#pragma once
#include "SelectFrame.h"

class CShapePresenter;

class CCanvasView : public CParentLayer
{
public:
	CCanvasView();
	~CCanvasView();

	bool OnEvent(sf::Event const& event) override;

	std::shared_ptr<CSelectFrame> const& GetFSelectFrame() const;
	size_t GetSelectedShapeNum() const;

	void AddShape(std::shared_ptr<CShapePresenter> const& shape, size_t pos);
	void DeleteShape(size_t pos);
	void MoveShapeLayer(size_t position, bool isToUp);
	void Clear();

	void Draw(sf::RenderTarget * window, CTextureCache * cache) override;

protected:
	bool OnMousePressed(sf::Event::MouseButtonEvent const & event) override;

private:
	std::shared_ptr<CShape> CreateShape(std::shared_ptr<CShapePresenter> const& data);

	void ShapeChangeRectEvent(std::shared_ptr<CShape> const& shape, sf::Event const& event);

	void MoveShapeUp(size_t position);
	void MoveShapeDown(size_t position);

	std::vector<std::shared_ptr<CShape>> m_shapes;
	std::shared_ptr<CSelectFrame> m_frame;

	CBoundingRect m_oldSelectShapeRect;
	size_t m_targetShapePosition = 0;
};

