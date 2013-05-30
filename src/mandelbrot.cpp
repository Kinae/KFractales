#include "mandelbrot.h"

Mandelbrot::Mandelbrot(sf::Mutex* mutex, unsigned int zoom, unsigned int max_iteration, bool inColor) {
	_mutex = mutex;
	_inColor = inColor;
	_zoom = zoom;
	_iteration_max = max_iteration;
}

Mandelbrot::~Mandelbrot() {
	_isRunning = false;

	while(!vec.empty()) {
		delete vec.back();
		vec.pop_back();
	}

}

void Mandelbrot::set_plan(double x1, double x2, double y1, double y2) {
	_x1 = x1;
	_x2 = x2;
	_y1 = y1;
	_y2 = y2;
}

sf::Image* Mandelbrot::build_image(void) {
	_image_x = static_cast<unsigned int>((_x2 - _x1) * _zoom);
	_image_y = static_cast<unsigned int>((_y2 - _y1) * _zoom);

	std::cout << "Image size : (" << _image_x << ";" << _image_y << ")" << std::endl;

	// empty black image
	_im = sf::Image(_image_x, _image_y, sf::Color::Black); 

	return &_im;
}

void Mandelbrot::run(void) {
	unsigned int step = _image_y / 50; 

	// Fixme, leak of pixels possible
	for(unsigned int i = 0; i < (step * 50 ); i += step) {
		Mandelbrot_processor *rend = new Mandelbrot_processor(_mutex, &_im, _zoom, _iteration_max, false);
		rend->set_plan(_x1, _x2, _y1, _y2);
		rend->set_subimage(0, i, _image_x, i + step);
		rend->Launch();	
		vec.push_back(rend);
	}

}

void Mandelbrot::stop(void) {
	_isRunning = false;
}
