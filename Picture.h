#pragma once
#include "ShapeModel.h"
class CPicture :
	public SModelShape
{
public:
	CPicture();
	CPicture(Vec2 const& position = Vec2(), Vec2 const& size = Vec2(), std::string const& path = std::string());
	~CPicture();

	std::string GetTexturePath() const;

private:
	std::string m_path;
};

