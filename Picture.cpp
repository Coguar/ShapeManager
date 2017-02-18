#include "stdafx.h"
#include "Picture.h"


CPicture::CPicture()
{
}

CPicture::CPicture(Vec2 const & position, Vec2 const & size)
	: SModelShape(ShapeType::Picture, position, size)
{
}


CPicture::~CPicture()
{
}

void CPicture::SetTexturePath(std::string const & path)
{
	m_path = path;
}

std::string CPicture::GetTexturePath() const
{
	return m_path;
}
