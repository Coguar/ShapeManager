#pragma once
#include "DomainModel.h"

class CHistory;

class CApplicationModel
	: public IObserver<DataType>
	, public CObservable<DataType>
{
public:
	CApplicationModel();
	~CApplicationModel();

	void Update(DataType const& data) override;

	void AddShape(ShapeType type, Vec2 const& position);
	void DeleteShape(size_t number);
	void ChangeShapeRect(size_t number, Vec2 const& pos, Vec2 const& size);

	void RedoCommand();
	void UndoCommand();

	void Save(std::string const& path);
	void Open(std::string const& path);

	void Clear();

protected:
	DataType GetChangedData()const override;

private:
	std::unique_ptr<CHistory> m_history;

	std::unique_ptr<CDomainModel> m_domainModel;
	DataType m_domainEvents;
};

