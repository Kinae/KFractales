#include <iostream>
#include <SFML/Graphics.hpp>
#include "mandelbrot.h"

const unsigned int WIDTH = 1360;
const unsigned int HEIGHT = 768; 

int main(int argc, char** argv) {

	sf::Mutex mutex;
	sf::Image* im = NULL;

	sf::RenderWindow App(sf::VideoMode(WIDTH, HEIGHT, 32), "Fractales");
	App.SetFramerateLimit(60);

	Mandelbrot rend(&mutex, 3000, 100, true);
	rend.set_plan(-2.1,0.6,-1.2,1.2);
	im = rend.build_image();

	sf::Sprite spr;
	spr.SetImage(*im);

	sf::Clock clock, elapsed;
	const float time = 0.25;

	sf::View view(sf::Vector2f(im->GetWidth()/2, im->GetHeight()/2), sf::Vector2f(WIDTH/2, HEIGHT/2));
	App.SetView(view);

	rend.run();

	while(App.IsOpened()) {

		sf::Event Event;
		while (App.GetEvent(Event)) {

			if (Event.Type == sf::Event::Closed) {
				rend.stop();
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
	
	rend.stop();
	
	std::cout << "Render is over (" << elapsed.GetElapsedTime() << "s) ! Saving..." << std::endl;
	im->SaveToFile("Fractal.png");
	std::cout << "Saved in \"Fractal.png\""<< std::endl;

	return EXIT_SUCCESS;
}
