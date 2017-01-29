#pragma once
#include "Observer.h"

class CApplicationModel;
struct SEvent;
enum class ShapeType;

class CViewObserver :
	public IObserver<SEvent>
{
public:
	CViewObserver();
	~CViewObserver();

	void Update(SEvent const& data) override;
	void SetModel(CApplicationModel * appModel);

private:
	void EditEvent(SEvent const& data);

	void AddShapeEvent(ShapeType type, Vec2 const& position);
	void DeleteShapeEvent(size_t number);
	void ChangeShapeRectEvent(size_t number, CBoundingRect const& newRect);
	void RedoEvent();
	void UndoEvent();
	void SaveEvent(std::string const& path);
	void OpenEvent(std::string const& path);

	CApplicationModel * m_appModel;
};

