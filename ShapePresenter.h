#pragma once

class CHistory;
class CShape;
class SModelShape;

class CShapePresenter
{
public:
	CShapePresenter(std::shared_ptr<SModelShape> const& model);
	~CShapePresenter();

	void SetHistory(CHistory * history);
	void SetShapeView(std::shared_ptr<CShape> & shape);

private:
	void AddCommand();

	void SetConnects();
	void InitView(std::shared_ptr<CShape> & shape);
	

	CHistory * m_history;
	CShape * m_shape;
	std::shared_ptr<SModelShape> m_model;

	boost::signals2::scoped_connection m_connection;
};

