#pragma once
#include "Reseiver.h"
#include "Canvas.h"
#include "CommandInterface.h"

class CHistory :
	public IReseiver
{
public:
	CHistory(std::shared_ptr<CCanvas> const& canvas);
	~CHistory();
	void AddShape(ShapePtr const& shape) override;
	void DeleteShape(ShapePtr const& shape, int num) override;
	void MoveShape(ShapePtr const& shape, Vec2 const& newPos) override;
	void ResizeShape(ShapePtr const& shape, Vec2 const& oldSize) override;
	void ChangeRect(ShapePtr const& shape, CBoundingRect const& rect) override;

	void Redo() override;
	void Undo() override;

private:
	void ClearOutdatedBranch();

	std::shared_ptr<CCanvas> m_canvas;
	std::vector<std::shared_ptr<ICommand>> m_doneCommands;
	size_t m_currentCommandNumber = 0;
};

