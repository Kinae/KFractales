#include "mandelbrot_processor.h"

Mandelbrot_processor::Mandelbrot_processor(sf::Mutex* mutex, sf::Image* im, unsigned int zoom, unsigned int max_iteration, bool inColor) {
	_mutex = mutex;
	_im = im;
	_inColor = inColor;
	_zoom = zoom;
	_iteration_max = max_iteration;
}

Mandelbrot_processor::~Mandelbrot_processor() {
	_isRunning = false;
}

void Mandelbrot_processor::set_plan(double x1, double x2, double y1, double y2) {
	_x1 = x1;
	_x2 = x2;
	_y1 = y1;
	_y2 = y2;
}

void Mandelbrot_processor::set_subimage(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	_subimage_x = x;
	_subimage_y = y;
	_subimage_width = width;
	_subimage_height = height;
}

void Mandelbrot_processor::Run(void) {
	_isRunning = true;
	for(unsigned int x = _subimage_x; x < _subimage_width && _isRunning; x++) {
		for(unsigned int y = _subimage_y; y < _subimage_height && _isRunning; y++) {

			double c_r = x / static_cast<double>(_zoom) + _x1;
			double c_i = y / static_cast<double>(_zoom) + _y1;
			double z_r = 0;
			double z_i = 0;
			double i = 0;

			do {
				double tmp = z_r;
				z_r = z_r * z_r - z_i *z_i + c_r;
				z_i = 2 * z_i * tmp + c_i;
				i++;
			}
			while((z_r * z_r + z_i * z_i < 4) && (i < _iteration_max) && _isRunning);

			if(_isRunning) {
				_mutex->Lock();

				if(_inColor) {
					if(i != _iteration_max) {
						_im->SetPixel(x, y, sf::Color(static_cast<int>(i), static_cast<int>(i*2), static_cast<int>(i*3)));
					}	
				} else {
					if(i == _iteration_max)
						_im->SetPixel(x, y, sf::Color::White);
				}

				_mutex->Unlock();
			}
		}
	}
}

void Mandelbrot_processor::stop(void) {
	_isRunning = false;
}

