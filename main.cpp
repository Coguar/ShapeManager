#include "stdafx.h"
#include "Application.h"
#include <vld.h>

int main(int argc, char* argv[])
{
	CApplication app;
	std::string filePath = "";
	if (argc > 1)
	{
		filePath = argv[1];
	}
	app.Start(filePath);
	return 0;
}

