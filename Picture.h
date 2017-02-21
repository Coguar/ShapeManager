#pragma once
#include "ShapeModel.h"
class CPicture :
	public SModelShape
{
public:
	CPicture();
	CPicture(std::string const& path, Vec2 const& position = Vec2(), Vec2 const& size = Vec2());
	~CPicture();

	std::string GetTexturePath() const;

private:
	std::string m_path;
};

