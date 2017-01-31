#include "stdafx.h"
#include "ShapeModel.h"
#include "DialogManager.h"
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
			return "Circle";
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

void CFileReader::Save(std::string const & path, std::vector<std::shared_ptr<SModelShape>> const & shapes)
{
	try
	{
		boost::property_tree::ptree propertyTree;
		for (auto &shape : shapes)
		{
			boost::property_tree::ptree child;
			child.add("Type", GetShapeName(shape->m_type));
			child.add("X", std::to_string(shape->m_position.x));
			child.add("Y", std::to_string(shape->m_position.y));
			child.add("Height", std::to_string(shape->m_size.y));
			child.add("Width", std::to_string(shape->m_size.x));
			propertyTree.add_child("Shapes.Shape", child);
		}
		std::stringstream stream;
		boost::property_tree::xml_writer_settings<std::string> settings;
		settings.indent_char = '\t';
		settings.indent_count = 1;

		boost::property_tree::write_xml(stream, propertyTree, settings);

		std::ofstream out(path);
		std::string str;
		while (!stream.eof())
		{
			stream >> str;
			out << str;
		}
		out.close();
	}
	catch (boost::property_tree::xml_parser_error)
	{
		std::cout << "XML parser error!" << std::endl;
		throw;
	}
}

std::vector<std::shared_ptr<SModelShape>> CFileReader::Open(std::string const & path)
{
	std::vector<std::shared_ptr<SModelShape>> shapes;
	if (!path.empty())
	{
		try
		{
			std::ifstream stream(path);
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

					shapes.push_back(std::make_shared<SModelShape>(GetShapeType(type), Vec2(x, y), Vec2(width, height)));
				}
			}
			stream.close();
		}
		catch (boost::property_tree::xml_parser_error)
		{
			std::cout << "XML parser error!" << std::endl;
			throw;
		}
	}
	return shapes;
}
