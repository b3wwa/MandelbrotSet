#include "ComplexPlane.h"

//Constructor
ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight) : m_vArray(Points, 1)
{
	m_pixel_size = { pixelWidth, pixelHeight };
	m_aspectRatio = static_cast<float>(pixelHeight)/pixelWidth;
	m_plane_center = { 0,0 };
	m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
	m_zoomCount = 0;
	m_state = State::CALCULATING;
	m_vArray.resize(pixelWidth * pixelHeight);
}

//Override draw function
void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}

//Zoom IN by increasing zoom count and changing plane size
void ComplexPlane::zoomIn()
{
	++m_zoomCount;
	float x = static_cast<float>(BASE_WIDTH) * pow(BASE_ZOOM, m_zoomCount);
	float y = static_cast<float>(BASE_HEIGHT) * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size = { x, y };
	m_state = State::CALCULATING;
}

//Zoom OUT by decreasing zoom count and changing plane size
void ComplexPlane::zoomOut()
{
	--m_zoomCount;
	float x = static_cast<float>(BASE_WIDTH) * pow(BASE_ZOOM, m_zoomCount);
	float y = static_cast<float>(BASE_HEIGHT) * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size = { x, y };
	m_state = State::CALCULATING;
}

//Call mapPixelToCoords to calculate the center of the plane
void ComplexPlane::setCenter(Vector2i mousePixel)
{
	m_plane_center = mapPixelToCoords(mousePixel);
	m_state = State::CALCULATING;
}

//Calculate mouse location by corresponding mouse pixel location to screen coordinates
void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
	m_mouseLocation = mapPixelToCoords(mousePixel);
}

//Use stringstream to set text
void ComplexPlane::loadText(Text& text)
{
	stringstream ss;
	text.setCharacterSize(16);
	text.setColor(Color::White);
	text.setPosition(20, 20);
	ss << "Mandelbrot set" << endl;
	ss << "Center: (" << m_plane_center.x << "," << m_plane_center.y << ")" << endl;
	ss << "Cursor: (" << m_mouseLocation.x << "," << m_mouseLocation.y << ")" << endl;
	ss << "Left-click to Zoom in" << endl;
	ss << "Right-click to Zoom out" << endl;
	text.setString(ss.str());
}

//If in a calculating state, use a double for loop to:
	//1. Loop through all pixels
	//2. Count the iterations of the current pixel
		//a. Access current pixel with
			//int index = j + i * m_pixel_size.x;
			//m_vArray[index].position = { (float)j, (float)i };
		//b. Call countIterations to find iteration count
	//3. Convert the iteration count to an rgb value and set the pixel value
		//a. iterationsToRGB(iterations, r, g, b);
		//b. m_vArray[index].color = Color(r, g, b);
	//4. Change state to Displaying

void ComplexPlane::updateRender()
{
	if (m_state == State::CALCULATING)
	{
		for (int i = 0; i < m_pixel_size.y; i++)
		{
			for (int j = 0; j < m_pixel_size.x; j++)
			{
				int index = j + i * m_pixel_size.x;

				m_vArray[index].position = {(float)j, (float)i};
				
				Vector2i pixelCoord(j, i);
				Vector2f coords = mapPixelToCoords(pixelCoord);

				size_t iterations = countIterations(coords);

				RGB color{ 0, 0, 0 };

				color = iterationsToRGB(iterations, color);

				m_vArray[index].color = Color(color.r, color.g, color.b);
			}
		}
		m_state = State::DISPLAYING;
	}
}

//Calculate number of iterations it takes for a pixel to escape
int ComplexPlane::countIterations(Vector2f coord)
{
	float x = 0.0f;
	float y = 0.0f;

	int iterations = 0;

	while(x*x + y*y <= 4.0f && iterations < MAX_ITER)
	{
		float tempX = x * x - y * y + coord.x;
		y = 2.0f * x * y + coord.y;
		x = tempX;
		++iterations;
	}
	return iterations;
}

//Convert iteration value to an RGB value
//If count is at max (64), set RGB value to (0, 0, 0) (black)
//Else, RGB value is calculated by multiplying and modding the pixel's iteration value
	//High R value, low G value, a little higher B value = mostly red and purple 
RGB ComplexPlane::iterationsToRGB(size_t count, RGB pixelColor)
{
	if (count == MAX_ITER)
	{
		pixelColor.r = pixelColor.g = pixelColor.b = 0;
	}
	else
	{
		pixelColor.r = (count * 20) % 256;
		pixelColor.g = (count * 5) % 20;
		pixelColor.b = (count * 15) % 100;
	}
	return pixelColor;
}

//Convert pixel value to screen x, y coordinates
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	float x = ((mousePixel.x - 0) / static_cast<float>(1920 - 0)) * m_plane_size.x + (m_plane_center.x - m_plane_size.x / 2.0f);

	float y = ((mousePixel.y - 1080) / static_cast<float>(0 - 1080)) * m_plane_size.y + (m_plane_center.y - m_plane_size.y / 2.0f);

	return Vector2f(x, y);
}