#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_

#include <iostream>
#include <SFML/Graphics.hpp>

class Processor : public sf::Thread {

	public :
	
		Processor(sf::Mutex* mutex, sf::Image* im);
		virtual ~Processor();

		virtual void Run(void) = 0;
		virtual void stop(void) = 0;

	protected :

		bool _isRunning;

		sf::Image *_im;  
		sf::Mutex *_mutex;

};

#endif
