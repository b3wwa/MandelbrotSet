#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_pixel_size = { pixelWidth, pixelHeight };

	//hopefully works but its integer division idk
	m_aspectRatio = VideoMode::getDesktopMode().height / VideoMode::getDesktopMode().width;
	m_plane_center = { 0, 0 };

	/*
		Assign m_plane_size with{ BASE_WIDTH, BASE_HEIGHT * m_aspectRatio }
		Assign m_zoomCount with 0
		Assign m_State with State::CALCULATING to be ready for the initial screen
		Initialize VertexArray
		We will use this to draw a color for each pixel
		Set its primitive type to Points
		Resize it to pixelWidth* pixelHeight
	*/
}

/*
int ComplexPlane::countIterations(Vector2f coord)
{

}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{

}
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{

}

const void ComplexPlane::draw(RenderTarget& target, RenderStates states)
{

}
void ComplexPlane::zoomIn()
{

}
void ComplexPlane::zoomOut()
{

}
void ComplexPlane::setCenter(Vector2i mousePixel)
{

}
void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{

}
void ComplexPlane::loadText(Text& text)
{

}
void ComplexPlane::updateRender()
{

}

*/