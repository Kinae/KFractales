#include "fractale.h"

Fractale::Fractale(sf::Mutex* mutex, unsigned int zoom, unsigned int max_iteration, bool inColor) {
	_mutex = mutex;
	_inColor = inColor;
	_zoom = zoom;
	_iteration_max = max_iteration;
}

Fractale::~Fractale() {
	while(!vec.empty()) {
		delete vec.back();
		vec.pop_back();
	}
}

void Fractale::set_plan(double x1, double x2, double y1, double y2) {
	_x1 = x1;
	_x2 = x2;
	_y1 = y1;
	_y2 = y2;
}

sf::Image* Fractale::build_image(void) {
	_image_x = static_cast<unsigned int>((_x2 - _x1) * _zoom);
	_image_y = static_cast<unsigned int>((_y2 - _y1) * _zoom);

	std::cout << "Image size : (" << _image_x << ";" << _image_y << ")" << std::endl;

	// empty black image
	_im = sf::Image(_image_x, _image_y, sf::Color::Black); 

	return &_im;
}

void Fractale::run(void) {
	unsigned int step = _image_x / 50; 

	for(unsigned int i = 0; i < (step * 50 ); i += step) {
		Mandelbrot_processor *rend = new Mandelbrot_processor(_mutex, &_im, _zoom, _iteration_max, true);
		rend->set_plan(_x1, _x2, _y1, _y2);
	
		if (i + step > _image_x) {		
			rend->set_subimage(i, 0, _image_x, _image_y);
		} else {
			rend->set_subimage(i, 0, i + step, _image_y);	
		}		

		rend->Launch();	
		vec.push_back(rend);
	}
}

void Fractale::stop(void) {
	
	while(!vec.empty()) {
		vec.back()->stop();
		vec.pop_back();
	}
	}
