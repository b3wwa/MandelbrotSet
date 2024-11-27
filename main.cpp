//Isabella and Noor
//Isabella's version includes: different colors and font choice, in depth comments, and multithreading that may or may not be implemented properly
//Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"
int main()
{
	//Create a video mode object based on resolution
	int pixelWidth = VideoMode::getDesktopMode().width;
	int pixelHeight = VideoMode::getDesktopMode().height;
	VideoMode vm(pixelWidth, pixelHeight);

	//Create and open a window for the game
	RenderWindow window(vm, "Mandelbrot set", Style::Default);

	//Create complexplane object
	ComplexPlane plane(pixelWidth, pixelHeight);
	Font font;
	if (!font.loadFromFile("winterLemon.ttf"))
	{
		cout << "Can not load the file!" << endl;
	}
	bool update = true;

	//Main loop
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				//Zoom in when left button clicked
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					Vector2i center = { event.mouseButton.x, event.mouseButton.y };

					//multithreading
					thread th1(&ComplexPlane::zoomIn, &plane);
					th1.join();

					//multithreading
					thread th2(&ComplexPlane::setCenter, &plane, center);
					th2.join();

					update = true;
				}

				//Zoom out when right button clicked
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					Vector2i center = { event.mouseButton.x, event.mouseButton.y };

					//multithreading
					thread th1(&ComplexPlane::zoomOut, &plane);
					th1.join();

					//multithreading
					thread th2(&ComplexPlane::setCenter, &plane, center);
					th2.join();

					update = true;
				}

			}

			//Update mouse coordinates
			if (event.type == sf::Event::MouseMoved)
			{
				Vector2i location = {event.mouseMove.x, event.mouseMove.y };
				plane.setMouseLocation(location);
			}
		}

		//Close window if escape is pressed
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		//Update scene
		Text text("", font);
		plane.loadText(text);

		//If zooming in or out, call update render
		if (update)
		{
			//multithreading
			thread th(&ComplexPlane::updateRender, &plane);
			th.join();
		}

		//Display scene
		window.clear();
		window.draw(plane);
		window.draw(text);
		window.display();
	}
}
