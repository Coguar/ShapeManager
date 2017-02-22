#pragma once

struct IHistory;
class CShape;
class SModelShape;

class CShapePresenter
{
public:
	CShapePresenter(std::shared_ptr<SModelShape> const& model, IHistory * history);
	~CShapePresenter();

	void SetShapeView(std::shared_ptr<CShape> & shape);

private:
	void AddCommand();

	void SetConnects();
	void InitView(std::shared_ptr<CShape> & shape);
	

	IHistory * m_history;
	CShape * m_shape;
	std::shared_ptr<SModelShape> m_model;

	std::vector<signal::ScopedConnection> m_connections;
};

