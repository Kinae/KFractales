#include <iostream>
#include <SFML/Graphics.hpp>

class Mandelbrot : public sf::Thread {

public:

	Mandelbrot(sf::Mutex* mutex, unsigned int zoom, unsigned int max_iteration, bool inColor);
	~Mandelbrot();
	
	virtual void Run(void);
	void stop(void);
	
	void setPlan(int x1, int x2, int y1, int y2);
	sf::Image* buildImage(void);
	
private :

	bool _isRunning;
  bool _inColor;

	double _x1;
  double _x2;
  double _y1;
  double _y2;
  unsigned int _zoom;
  unsigned int _iteration_max;
 
  unsigned int _image_x;
  unsigned int _image_y;
 
  sf::Clock _elapsed;  
  sf::Image _im;  
  sf::Mutex *_mutex;

};