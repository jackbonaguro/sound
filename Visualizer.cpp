#include "main.hpp"
#include "main.hpp"
#include "Sampler.hpp"
#include "Synth.hpp"
#include <SFML/Graphics.hpp>

const int winw = 600;
const int winh = 400;

///////////////////////////////////////////////////////////////////////////////////
sf::ContextSettings settings(0,0,7);
sf::RenderWindow win(sf::VideoMode(winw,winh,32), "Test", sf::Style::Titlebar, settings);
sf::Event event;
sf::Clock gameclock;
//////////////////////////////////////////////////////////////////////////////////

int len = winw;
float points[len];

Synth ss(winw, 0.1, 40.0);

void update(float dt){
	win.clear(sf::Color::Black);
	for(int i=0; i<len; i++){

	}
	win.display();
}

int main(){
	while (win.isOpen()){
		while (win.pollEvent(event)){
			if (event.type == sf::Event::Closed){
				win.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				win.close();
			}
		}
		float dt = gameclock.getElapsedTime().asSeconds();
		gameclock.restart();
		update(dt);
	}
	return 0;
}
