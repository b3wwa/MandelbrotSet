#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Thread.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
using namespace sf;
using namespace std;


const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

enum class State { CALCULATING, DISPLAYING };

struct RGB
{
	Uint8 r, g, b;
};

class ComplexPlane : public Drawable
{
	public:
		ComplexPlane(int pixelWidth, int pixelHeight);
		void draw(RenderTarget& target, RenderStates states) const;
		void zoomIn();
		void zoomOut();
		void setCenter(Vector2i mousePixel);
		void setMouseLocation(Vector2i mousePixel);
		void loadText(Text& text);
		void updateRender();

	private:
		VertexArray m_vArray;
		State m_state;
		Vector2f m_mouseLocation;
		Vector2i m_pixel_size;
		Vector2f m_plane_center;
		Vector2f m_plane_size;
		int m_zoomCount;
		float m_aspectRatio;

		int countIterations(Vector2f coord);
		RGB iterationsToRGB(size_t count, RGB pixelColor);
		Vector2f mapPixelToCoords(Vector2i mousePixel);
};