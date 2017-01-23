#pragma once
#include "Reseiver.h"
#include "CommandInterface.h"

class CCanvas;

class CHistory :
	public IReseiver
{
public:
	CHistory(std::shared_ptr<CCanvas> const& canvas);
	~CHistory();
	void AddShape(ShapePtr const& shape) override;
	void DeleteShape(ShapePtr const& shape, int num) override;
	void ChangeRect(ShapePtr const& shape, CBoundingRect const& rect) override;

	void Redo() override;
	void Undo() override;

	void Clear() override;

private:
	void ClearOutdatedBranch();

	std::shared_ptr<CCanvas> m_canvas;
	std::vector<std::shared_ptr<ICommand>> m_doneCommands;
	size_t m_currentCommandNumber = 0;
};

