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

void Fractale::set_plan(int fractale_type) {
	_fractale_type = fractale_type;
	if(_fractale_type == MANDELBROT) {
		_x1 = -2.1;
		_x2 = 0.6;
		_y1 = -1.2;
		_y2 = 1.2;
	} else {
		_x1 = -1.1;
		_x2 = 1;
		_y1 = -1.2;
		_y2 = 1.2;
	} 
}

sf::Image* Fractale::build_image(void) {
	_image_x = static_cast<unsigned int>((_x2 - _x1) * _zoom);
	_image_y = static_cast<unsigned int>((_y2 - _y1) * _zoom);

	std::cout << "Image size : (" << _image_x << ";" << _image_y << ")" << std::endl;

	_im = sf::Image(_image_x, _image_y, sf::Color::Black); 

	return &_im;
}

void Fractale::run(void) {
	unsigned int step = _image_x / 50; 

	for(unsigned int i = 0; i < (step * 50 ); i += step) {
		Processor *proc = NULL;
		if(_fractale_type == MANDELBROT) {
			proc = new Mandelbrot_processor(_mutex, &_im, _zoom, _iteration_max, true);			
		} else {
			proc = new Juliaset_processor(_mutex, &_im, _zoom, _iteration_max, true);		
		}

		proc->set_plan(_x1, _x2, _y1, _y2);
	
		if (i + step > _image_x) {		
			proc->set_subimage(i, 0, _image_x, _image_y);
		} else {
			proc->set_subimage(i, 0, i + step, _image_y);	
		}		

		proc->Launch();	
		vec.push_back(proc);
	}
}

void Fractale::stop(void) {
	
	while(!vec.empty()) {
		vec.back()->stop();
		vec.pop_back();
	}
	}
