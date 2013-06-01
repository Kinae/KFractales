#include "juliaset_processor.h"

Juliaset_processor::Juliaset_processor(sf::Mutex* mutex, sf::Image* im, unsigned int zoom, unsigned int max_iteration, bool inColor)
: Processor(mutex, im) {
	_inColor = inColor;
	_zoom = zoom;
	_iteration_max = max_iteration;
}

Juliaset_processor::~Juliaset_processor() {
	_isRunning = false;
}

void Juliaset_processor::set_plan(double x1, double x2, double y1, double y2) {
	_x1 = x1;
	_x2 = x2;
	_y1 = y1;
	_y2 = y2;
}

void Juliaset_processor::set_subimage(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	_subimage_x = x;
	_subimage_y = y;
	_subimage_width = width;
	_subimage_height = height;
}

void Juliaset_processor::Run(void) {
	_isRunning = true;
	for(unsigned int x = _subimage_x; x < _subimage_width && _isRunning; x++) {
		for(unsigned int y = _subimage_y; y < _subimage_height && _isRunning; y++) {

			double c_r = 0.285;
			double c_i = 0.01;
			double z_r = x / static_cast<double>(_zoom) + _x1;
			double z_i = y / static_cast<double>(_zoom) + _y1;
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

void Juliaset_processor::stop(void) {
	_isRunning = false;
}
