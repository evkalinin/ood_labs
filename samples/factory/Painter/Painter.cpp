// Painter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../libpainter/Designer.h"
#include "../libpainter/ShapeFactroy.h"
#include "../libpainter/PictureDraft.h"
#include "../libpainter/SvgCanvas.h"
#include "../libpainter/DraftPainter.h"

using namespace std;

void Help()
{
	std::cout << "Available shapes: " << std::endl;
	std::cout << "rect <pt> <size> <style>" << std::endl;
	std::cout << "ellipse <pt> <size> <style>" << std::endl;
	std::cout << "triangle <pt> <pt> <pt> <style>" << std::endl;
	std::cout << "+group" << std::endl;
	std::cout << "-group" << std::endl;
	
	std::cout << "<pt> := int int" << std::endl;
	std::cout << "<size> := int int" << std::endl;

	std::cout << "<style> := <color?> <color?> <thin?>" << std::endl;	
	std::cout << "<color?> := int32 | '-'" << std::endl;
	std::cout << "<thin?> := int | none" << std::endl;
	std::cout << std::endl;
}

void DrawStr(std::string const& str, Designer& designer, ICanvas& canvas)
{
	std::istringstream s(str);
	auto draft = designer.CreateDraft(s);
	PaintDraft(draft, canvas);
}

void DrawCar(Designer& designer, ICanvas& canvas)
{
	std::ostringstream buffer;
	buffer << "rect 180 460 400 80 0xFF0000 -  " << std::endl;
	buffer << "rect 330 400 250 60 0xFF0000 0x00 1 " << std::endl;	
	buffer << "ellipse 268 543 35 35 0xAA000000 0x00 2" << std::endl;
	buffer << "ellipse 518 540 35 35 0xAA000000 0x00 2 " << std::endl;
	DrawStr(buffer.str(), designer, canvas);
}

void DrawSun(Designer& designer, ICanvas& canvas)
{
	std::ostringstream buffer;
	buffer << "+group" << std::endl;
	buffer << "ellipse 800 0 150 90 0xFFFF00 0x99FFAA00 10" << std::endl;
	buffer << "triangle 760 125 732 197 750 197 0xFFFF00 0xAAFFBB00 2" << std::endl;
	buffer << "triangle 679 98 601 148 625 158 0xFFFF00 0xAAFFBB00 2" << std::endl;
	buffer << "triangle 601 39 495 34 502 52 0xFFFF00 0xAAFFBB00 2" << std::endl;
	buffer << "-group" << std::endl;
	
	DrawStr(buffer.str(), designer, canvas);
}

void ErrorHandler(std::exception const& e)
{
	std::cout << "Error: " << e.what() << std::endl;

	Help();
}

int main()
{
	try
	{
		ShapeFactroy shapeFactory;
		Designer designer(shapeFactory, std::bind(ErrorHandler, std::placeholders::_1));

		SvgCanvas canvas("draft.svg");
		canvas.BeginDraw(800, 600);

#if 0
		auto draft = designer.CreateDraft(std::cin);
		PaintDraft(draft, canvas);
#endif

#if 1
		DrawSun(designer, canvas);
		DrawCar(designer, canvas);
#endif

		canvas.EndDraw();
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}

