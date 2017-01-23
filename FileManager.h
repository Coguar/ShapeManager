#pragma once
#include <memory>
#include <vector>

class CShape;

struct IFileManager
{
	virtual void Save(std::vector<std::shared_ptr<CShape>> const& shapes) = 0;
	virtual std::vector<std::shared_ptr<CShape>> const& OpenFile() = 0;
	virtual ~IFileManager() = default;
};