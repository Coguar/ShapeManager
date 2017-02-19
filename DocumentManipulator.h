#pragma once
#include <string>

struct IDocumentManipulator
{
	virtual void Save(std::string const& path) = 0;
	virtual void Open(std::string const& path, std::string const& tempResFolder = std::string()) = 0;
	virtual ~IDocumentManipulator() = default;
};