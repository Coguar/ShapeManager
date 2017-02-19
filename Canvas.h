#pragma once
#include "ShapeModel.h"
#include "CanvasSignaller.h"
#include "ShapeCollection.h"

class CCanvas
	: public ICanvasSignaller
	, public IShapeCollection
{
public:
	CCanvas();
	~CCanvas();

	void AddShape(std::shared_ptr<SModelShape> const& shape) override;
	void AddShape(std::shared_ptr<SModelShape> const& shape, size_t position) override;
	std::shared_ptr<SModelShape> DeleteLastShape() override;
	std::shared_ptr<SModelShape> DeleteShapeByPosition(size_t position) override;
	void MoveShapeUp(size_t position) override;
	void MoveShapeDown(size_t position) override;

	void Clear();
	void SetNewShapeList(std::vector<std::shared_ptr<SModelShape>> const& shapes);

	std::vector<std::shared_ptr<SModelShape>> const& GetData() const;

	Vec2 GetSize() const;

	signal::Connection DoOnShapeAdd(std::function<void(std::shared_ptr<SModelShape>, size_t )> const& action) override;
	signal::Connection DoOnShapeDelete(std::function<void(size_t)> const& action) override;
	signal::Connection DoOnShapesClear(std::function<void()> const& action) override;
	signal::Connection DoOnShapesLayerMove(std::function<void(size_t, bool)> const& action) override;
	signal::Connection DoOnResourceBecomingUnusable(std::function<void(std::string)> const& action) override;

private:

	boost::signals2::signal<void(std::shared_ptr<SModelShape>, size_t)> m_onShapeAdded;
	boost::signals2::signal<void(size_t)> m_onShapeDelete;
	boost::signals2::signal<void()> m_onShapeListClear;
	boost::signals2::signal<void(size_t, bool)> m_onMoveShapesLayer;
	boost::signals2::signal<void(std::string)> m_resHasBecomeUnusable;
	std::vector<std::shared_ptr<SModelShape>> m_shapes;
	Vec2 m_size;
};

