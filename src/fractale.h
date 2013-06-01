#ifndef _FRACTALE_H_
#define _FRACTALE_H_

#define MANDELBROT 	1
#define JULIASET		2

#include <iostream>
#include <SFML/Graphics.hpp>

#include "processor.h"
#include "mandelbrot_processor.h"
#include "juliaset_processor.h"

class Fractale {

	public:

		Fractale(sf::Mutex* mutex, unsigned int zoom, unsigned int max_iteration, bool inColor);
		~Fractale();

		void run(void);
		void stop(void);

		void set_plan(int fractale_type);
		sf::Image* build_image(void);

	private :

		int  _fractale_type;				
		bool _inColor;

		double _x1;
		double _x2;
		double _y1;
		double _y2;
		unsigned int _zoom;
		unsigned int _iteration_max;

		unsigned int _image_x;
		unsigned int _image_y;

		sf::Image _im;  
		sf::Mutex *_mutex;

		std::vector<Processor*> vec;
};

#endif
