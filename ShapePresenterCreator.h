#pragma once

class CHistory;
class CShapePresenter;
class SModelShape;

class CShapePresenterCreator
{
public:
	CShapePresenterCreator() = default;
	CShapePresenterCreator(CHistory * history);
	~CShapePresenterCreator();

	std::shared_ptr<CShapePresenter> CreatePresenter(std::shared_ptr<SModelShape> const& model);

private:
	CHistory * m_history = nullptr;
};

