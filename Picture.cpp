#include "stdafx.h"
#include "Picture.h"


CPicture::CPicture()
{
}

CPicture::CPicture(std::string const& path, Vec2 const & position, Vec2 const & size)
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
