#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_pixel_size = { pixelWidth, pixelHeight };

	//hopefully works but its integer division idk
	m_aspectRatio = VideoMode::getDesktopMode().height / VideoMode::getDesktopMode().width;
	m_plane_center = { 0, 0 };
	m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
	m_zoomCount = 0;
	m_state = State::CALCULATING;
	VertexArray(Points, pixelWidth * pixelHeight);
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}

void ComplexPlane::updateRender()
{
	if (m_state == State::CALCULATING)
	{
		for (int i = 0; i < m_pixel_size.x; i++)
		{
			for (int j = 0; j < m_pixel_size.y; j++)
			{
				/*
				
					update render function

				*/
			}
		}
	}
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	int xSize = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	int ySize = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size = { xSize, ySize };
	m_state == State::CALCULATING;
}

void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	int xSize = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	int ySize = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size = { xSize, ySize };
	m_state == State::CALCULATING;
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

void ComplexPlane::setCenter(Vector2i mousePixel)
{

}
void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{

}
void ComplexPlane::loadText(Text& text)
{

}

*/