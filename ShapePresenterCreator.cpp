#include "stdafx.h"
#include "ShapeModel.h"
#include "History.h"
#include "ShapePresenter.h"
#include "ShapePresenterCreator.h"


CShapePresenterCreator::CShapePresenterCreator(CHistory * history)
	: m_history(history)
{
}

CShapePresenterCreator::~CShapePresenterCreator()
{
}

std::shared_ptr<CShapePresenter> CShapePresenterCreator::CreatePresenter(std::shared_ptr<SModelShape> const & model)
{
	auto presenter = std::make_shared<CShapePresenter>(model);
	presenter->SetHistory(m_history);
	return presenter;
}
