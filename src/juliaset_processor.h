#ifndef _JULIASET_PROCESSOR_H_
#define _JULIASET_PROCESSOR_H_

#include <iostream>
#include <SFML/Graphics.hpp>

#include "processor.h"

class Juliaset_processor : public Processor {

	public:

		Juliaset_processor(sf::Mutex* mutex, sf::Image* im, unsigned int zoom, unsigned int max_iteration, bool inColor);
		~Juliaset_processor();

		void Run(void);
		virtual void stop(void);
		
		void set_plan(double x1, double x2, double y1, double y2);
		void set_subimage(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

	private :

		bool _inColor;

		double _x1;
		double _x2;
		double _y1;
		double _y2;
		unsigned int _zoom;
		unsigned int _iteration_max;

		unsigned int _subimage_x;
		unsigned int _subimage_y; 
		unsigned int _subimage_width;
		unsigned int _subimage_height;

};

#endif
