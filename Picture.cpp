#include "stdafx.h"
#include "Picture.h"


CPicture::CPicture()
{
}

CPicture::CPicture(Vec2 const & position, Vec2 const & size, std::string const& path)
	: SModelShape(ShapeType::Picture, position, size)
	, m_path(path)
{
}


CPicture::~CPicture()
{
}

std::string CPicture::GetTexturePath() const
{
	return m_path;
}
