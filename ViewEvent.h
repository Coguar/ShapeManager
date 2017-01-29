#pragma once
#include "Rectangle.h"

const enum class EventType
{
	AddCircle = 0,
	AddRectangle,
	AddTriangle,
	DeleteShape,
	ChangeShapeRect,
	Redo,
	Undo,
	Open, 
	Save,
	NotEvent,
};

struct SEvent
{
	SEvent(EventType type = EventType::NotEvent, size_t shapeNumber = 0, CBoundingRect oldRect = CBoundingRect(), CBoundingRect newRect = CBoundingRect())
		: m_type(type)
		, m_shapeNumber(shapeNumber)
		, m_oldRect(oldRect)
		, m_newRect(newRect)
	{}
	EventType m_type;
	CBoundingRect m_oldRect;
	CBoundingRect m_newRect;
	size_t m_shapeNumber;
	std::string m_filePath;
};