#include "mandelbrot.h"
 
Mandelbrot::Mandelbrot(sf::Mutex* mutex, unsigned int zoom, unsigned int max_iteration, bool inColor) {
 			_mutex = mutex;
      _inColor = inColor;
      _zoom = zoom;
      _iteration_max = max_iteration;
}

Mandelbrot::~Mandelbrot() {
	_isRunning = false;
}

void Mandelbrot::setPlan(int x1, int x2, int y1, int y2) {
      _x1 = x1;
      _x2 = x2;
      _y1 = y1;
      _y2 = y2;
}

sf::Image* Mandelbrot::buildImage(void) {
      _image_x = static_cast<unsigned int>((_x2 - _x1) * _zoom);
      _image_y = static_cast<unsigned int>((_y2 - _y1) * _zoom);

      std::cout << "Image size : (" << _image_x << ";" << _image_y << ")" << std::endl;

			// empty black image
      _im = sf::Image(_image_x, _image_y, sf::Color::Black); 
      
      return &_im;
}
 
void Mandelbrot::Run(void) {
	_isRunning = true;
	for(unsigned int x = 0; x < _image_x && _isRunning; x++) {
	  for(unsigned int y = 0; y < _image_y && _isRunning; y++) {

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
	          _im.SetPixel(x, y, sf::Color(0, 0, static_cast<int>(i * 255 / _iteration_max)));
          }
	      } else {
	        if(i == _iteration_max) { 
	          _im.SetPixel(x, y, sf::Color::White);
          }
        }
        
        _mutex->Unlock();
      }
    }
  }

  if(_isRunning) {
	  std::cout << "Render is over (" << _elapsed.GetElapsedTime() << "s) ! Saving..." << std::endl;
    _im.SaveToFile("Fractal.png");
    std::cout << "Saved in \"Fractal.png\""<< std::endl;
  } else {
  	std::cout << "Rendering aborded" << std::endl;
  }
}

void Mandelbrot::stop(void) {
	_isRunning = false;
}

