#include "processor.h"

Processor::Processor(sf::Mutex* mutex, sf::Image* im) {
	_mutex = mutex;
	_im = im;
}

Processor::~Processor() {
}
