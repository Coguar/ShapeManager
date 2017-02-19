#pragma once
#include "Canvas.h"
#include "CollectionShapesManipulator.h"
#include "DocumentManipulator.h"
#include "HistoryManipulator.h"


class CHistory;
class CShapePresenter;

class CApplicationModel
	: public ICollectionShapesManipulator
	, public IDocumentManipulator
	, public IHistoryManipulator
{
public:
	CApplicationModel();
	~CApplicationModel();

	void AddShape(ShapeType type, Vec2 const& position) override;
	void AddPicture(Vec2 const& position, std::string const& path) override;
	void DeleteShape(size_t position) override;
	void MoveShapeLayer(size_t position, bool isToUp) override;
	void Clear() override;

	Vec2 GetCanvasSize() const;

	signal::Connection DoOnShapeAdded(std::function<void(std::shared_ptr<CShapePresenter>, size_t)> const& action) override;
	signal::Connection DoOnShapeDelete(std::function<void(size_t)> const& action) override;
	signal::Connection DoOnShapesClear(std::function<void()> const& action) override;
	signal::Connection DoOnSavedStateChanged(std::function<void(bool)> const& action) override;
	signal::Connection DoOnShapesLayerMove(std::function<void(size_t, bool)> const& action) override;

	void Save(std::string const& path) override;
	void Open(std::string const& path) override;

	void RedoCommand() override;
	void UndoCommand() override;
	void ClearHistory() override;

private:
	void ShapeAdded(std::shared_ptr<SModelShape> const& shape, size_t position);

	std::unique_ptr<CHistory> m_history;

	std::unique_ptr<CCanvas> m_domainModel;

	boost::signals2::signal<void(std::shared_ptr<CShapePresenter>, size_t)> m_onAddShape;
};

