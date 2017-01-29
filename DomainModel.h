#pragma once
#include "ShapeModel.h"
#include "Observer.h"

const enum class DomEventType
{
	Add = 0,
	Del,
	Change,
	Clear,
	Saved,
};

struct DomEvent
{
	DomEvent(DomEventType type, size_t pos, std::shared_ptr<SModelShape> const& element)
		: m_type(type)
		, m_pos(pos)
		, m_element(element)
	{}

	DomEventType m_type;
	size_t m_pos;
	std::shared_ptr<SModelShape> m_element;
};

using DataType = std::vector<DomEvent>;

class CDomainModel
	: public CObservable<DataType>
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
	void DataChanged();

	std::vector<std::shared_ptr<SModelShape>> const& GetData() const;

protected:
	DataType GetChangedData()const override;

private:
	std::vector<std::shared_ptr<SModelShape>> m_shapes;

	DataType m_events;
};

