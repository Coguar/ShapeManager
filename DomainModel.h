#pragma once
#include "ShapeModel.h"


class CDomainModel
{
public:
	CDomainModel();
	~CDomainModel();

	void AddShape(std::shared_ptr<SModelShape> const& shape);
	void AddShape(std::shared_ptr<SModelShape> const& shape, size_t position);
	std::shared_ptr<SModelShape> DeleteLastShape();
	std::shared_ptr<SModelShape> DeleteShapeByPosition(size_t position);
	void ChangeShapeSettings(size_t shapeNum, Vec2 const& pos, Vec2 const& size);

	void Clear();
	void SetNewShapeList(std::vector<std::shared_ptr<SModelShape>> const& shapes);

	void DataSaved();

	std::vector<std::shared_ptr<SModelShape>> const& GetData() const;

	void DoOnShapeAdd(std::function<void(std::shared_ptr<SModelShape> const& shape, size_t number)> const& action);
	void DoOnShapeDelete(std::function<void(size_t number)> const& action);
	void DoOnShapesClear(std::function<void()> const& action);
	void DoOnDataSaved(std::function<void()> const& action);
	void DoOndataChanged(std::function<void()> const& action);

private:

	boost::signals2::signal<void(std::shared_ptr<SModelShape> const& shape, size_t number)> m_onShapeAdded;
	boost::signals2::signal<void(size_t number)> m_onShapeDelete;
	boost::signals2::signal<void()> m_onShapeListClear;
	boost::signals2::signal<void()> m_onDataSaved;
	boost::signals2::signal<void()> m_onDataChange;

	std::vector<std::shared_ptr<SModelShape>> m_shapes;
};

