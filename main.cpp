#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
	//Get Desktop Resolution
	int resWidth = VideoMode::getDesktopMode().width;
	int resHeight = VideoMode::getDesktopMode().height;
	
	//Construct RenderWindow
	//https://www.sfml-dev.org/documentation/2.6.2/classsf_1_1RenderWindow.php
	//the resolution is divided by 2 for speed, can change later to actual size
	RenderWindow window(VideoMode(resWidth / 2, resHeight / 2), "SFML window", Style::Default);

	ComplexPlane(1, 1);

	//Construct Font object
	Font font;

	if (!font.loadFromFile("LinLibertine_R.ttf"))
	{
		cout << "Error loading font" << endl;
		return -1;
	};

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			// Request for closing the window
			if (event.type == Event::Closed)
			{
				window.close();
			}
			
			/*
			
				MAIN LOOP GOES HERE!!!
			
			*/

		}

		//Format text
		Text text("bottom text", font);
		text.setCharacterSize(24);
		text.setFillColor(Color::White);
		text.setPosition(resWidth/4, resHeight/4);

		//Clear RenderWindow
		window.clear();

		//Draw Text object
		window.draw(text);
 
		//Display RenderWindow object
		window.display();
	}
	return 0;
}