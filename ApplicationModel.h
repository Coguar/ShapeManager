#pragma once
#include "Canvas.h"

class CHistory;
class CShapePresenter;

class CApplicationModel
{
public:
	CApplicationModel();
	~CApplicationModel();

	void AddShape(ShapeType type, Vec2 const& position);
	void DeleteShape(size_t position);

	void RedoCommand();
	void UndoCommand();

	void Save(std::string const& path);
	void Open(std::string const& path);

	void Clear();

	void SetCanvasSize(Vec2 const& size);
	Vec2 GetCanvasSize() const;

	void DoOnShapeAdded(std::function<void(std::shared_ptr<CShapePresenter>, size_t)> const& action);
	void DoOnShapeDelete(std::function<void(size_t)> const& action);
	void DoOnShapesClear(std::function<void()> const& action);
	void DoOnSavedStateChanged(std::function<void(bool)> const& action);

private:
	void ShapeAdded(std::shared_ptr<SModelShape> const& shape, size_t position);

	std::unique_ptr<CHistory> m_history;

	std::unique_ptr<CCanvas> m_domainModel;

	boost::signals2::signal<void(std::shared_ptr<CShapePresenter>, size_t)> m_onAddShape;
};

