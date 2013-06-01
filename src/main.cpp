#include <iostream>
#include <SFML/Graphics.hpp>
#include <getopt.h>

#include "fractale.h"

const unsigned int WIDTH = 1360;
const unsigned int HEIGHT = 768;

int main(int argc, char** argv) {

	unsigned int zoom = 0;
	unsigned int iteration = 0;
	int app_mode = 0;
	
	int optch;
	extern int opterr;
	char format[] = "z:i:MJ";

	opterr = 1;

	while((optch = getopt(argc, argv, format)) != -1) {
		switch(optch) {
			case 'z':
				zoom = atoi(optarg);
				break;
			case 'i':
				iteration = atoi(optarg);
				break;
			case 'M':
				app_mode = MANDELBROT;
				break;
			case 'J':
				app_mode = JULIASET;
				break;
		}
	}

	if(zoom == 0) {
		return EXIT_FAILURE;		
	}

	if(iteration == 0) {
		return EXIT_FAILURE;
	} 

	if(app_mode == 0) {
		return EXIT_FAILURE;
	}

	sf::Mutex mutex;
	sf::Image* im = NULL;

	sf::RenderWindow App(sf::VideoMode(WIDTH, HEIGHT, 32), "Fractales");
	App.SetFramerateLimit(60);

	Fractale fractale(&mutex, zoom, iteration, true);
	fractale.set_plan(app_mode);
	im = fractale.build_image();

	sf::Sprite spr;
	spr.SetImage(*im);

	sf::Clock clock, elapsed;
	const float time = 0.25;

	sf::View view(sf::Vector2f(im->GetWidth()/2, im->GetHeight()/2), sf::Vector2f(WIDTH/2, HEIGHT/2));
	App.SetView(view);

	fractale.run();

	while(App.IsOpened()) {

		sf::Event Event;
		while (App.GetEvent(Event)) {

			if (Event.Type == sf::Event::Closed) {
				fractale.stop();
				App.Close();
			} else if(Event.Type == sf::Event::MouseWheelMoved) {
				if(Event.MouseWheel.Delta > 0) {
					view.Zoom(1.5);
				} else {
					view.Zoom(0.75f);
				}
			}
			else if(Event.Type == sf::Event::KeyPressed) {
				if(Event.Key.Code == sf::Key::Left) {
					view.Move(-20,0);
				} else if(Event.Key.Code == sf::Key::Right) {
					view.Move(20,0);
				} else if(Event.Key.Code == sf::Key::Up) {
					view.Move(0,-20);
				} else if(Event.Key.Code == sf::Key::Down) {
					view.Move(0,20);
				}
			}
		}

		if(clock.GetElapsedTime() > time) {
			clock.Reset();
			mutex.Lock(); 
			App.Clear();
			App.Draw(spr);
			App.Display();
			mutex.Unlock();
		}
	}
	
	fractale.stop();
	
	std::cout << "Render is over (" << elapsed.GetElapsedTime() << "s) ! Saving..." << std::endl;
	im->SaveToFile("Fractal.png");
	std::cout << "Saved in \"Fractal.png\""<< std::endl;

	return EXIT_SUCCESS;
}
