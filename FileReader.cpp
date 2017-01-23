#include "stdafx.h"
#include "Canvas.h"
#include "FileManager.h"
#include <sstream>
#include <fstream>
#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\xml_parser.hpp>
#include "FileReader.h"

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

bool CFileReader::Save(std::vector<std::shared_ptr<CShape>> const & shapes)
{
	auto file = CFileManager::GetFileToSave();
	if (file.empty())
	{
		return false;
	}
	try
	{
		boost::property_tree::ptree propertyTree;
		for (auto &shape : shapes)
		{
			boost::property_tree::ptree child;
			child.add("Type", GetShapeName(shape->GetType()));
			child.add("X", std::to_string(shape->GetPosition().x));
			child.add("Y", std::to_string(shape->GetPosition().y));
			child.add("Height", std::to_string(shape->GetSize().y));
			child.add("Width", std::to_string(shape->GetSize().x));
			propertyTree.add_child("Shapes.Shape", child);
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
		return true;
	}
	catch(boost::property_tree::xml_parser_error)
	{
		std::cout << "XML parser error!" << std::endl;
		throw;
	}
	return false;
}

bool CFileReader::Open(std::shared_ptr<CCanvas> & canvas)
{
	auto file = CFileManager::GetFileToOpen();
	if (file.empty())
	{
		return false;
	}
	try
	{
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

				auto s = canvas->CreateShape(GetShapeType(type));
				s->SetBoundingRect(CBoundingRect({x, y}, {width, height}));
			}
		}
		stream.close();
		return true;
	}
	catch (boost::property_tree::xml_parser_error)
	{
		std::cout << "XML parser error!" << std::endl;
		throw;
	}
	return false;
}
