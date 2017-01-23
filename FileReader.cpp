#include "stdafx.h"
#include "FileReader.h"
#include "AbstractShape.h"
#include "FileManager.h"
#include <sstream>
#include <fstream>
#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\xml_parser.hpp>

namespace
{
	std::string GetShapeName(ShapeType type)
	{
		switch (type)
		{
		case ShapeType::Circle:
			return "Circle";
		case ShapeType::Triangle:
			return "Triangle";
		case ShapeType::Rectangle:
			return "Rectangle";
		default:
			break;
		}
	}

	ShapeType GetShapeType(std::string const& typeStr)
	{
		if (typeStr == "Circle")
		{
			return ShapeType::Circle;
		}
		else if (typeStr == "Triangle")
		{
			return ShapeType::Triangle;
		}
		else
		{
			return ShapeType::Rectangle;
		}
	}
}

void CFileReader::Save(std::vector<std::shared_ptr<CShape>> const & shapes)
{
	auto file = CFileManager::GetFileToSave();
	try
	{
		boost::property_tree::ptree propertyTree;
		for (auto &shape : shapes)
		{
			propertyTree.put("Shapes.Shape.Type", GetShapeName(shape->GetType()));
			propertyTree.put("Shapes.Shape.X", std::to_string(shape->GetPosition().x));
			propertyTree.put("Shapes.Shape.Y", std::to_string(shape->GetPosition().y));
			propertyTree.put("Shapes.Shape.Height", std::to_string(shape->GetSize().y));
			propertyTree.put("Shapes.Shape.Width", std::to_string(shape->GetSize().x));
		}
		std::stringstream stream;
		boost::property_tree::write_xml(stream, propertyTree);

		std::ofstream out(file);
		std::string str;
		while (!stream.eof())
		{
			stream >> str;
			out << str;
		}
		out.close();
	}
	catch(boost::property_tree::xml_parser_error)
	{
		std::cout << "XML parser error!" << std::endl;
		throw;
	}
}

void CFileReader::Open(std::vector<std::shared_ptr<CShape>>& shapesVec)
{
	auto file = CFileManager::GetFileToOpen();
	try
	{
		shapesVec.clear();
		std::ifstream stream(file);
		boost::property_tree::ptree propertyTree;
		boost::property_tree::read_xml(stream, propertyTree);
		for (auto &shape : propertyTree.get_child("Shapes"))
		{
			if (shape.first == "Shape")
			{
				std::string type = shape.second.get<std::string>("Type");
				double x = shape.second.get<double>("X");
				double y = shape.second.get<double>("Y");
				double height = shape.second.get<double>("Height");
				double width = shape.second.get<double>("Width");

				auto shape = std::make_shared<CShape>(GetShapeType(type));
				shape->SetBoundingRect(CBoundingRect({x, y}, {width, height}));
				shapesVec.push_back(shape);
			}
		}
		stream.close();
	}
	catch (boost::property_tree::xml_parser_error)
	{
		shapesVec.clear();
		std::cout << "XML parser error!" << std::endl;
		throw;
	}
}
