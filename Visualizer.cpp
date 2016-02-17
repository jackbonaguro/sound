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

float points[winw];
int mode = 0;

int phase = 0;
Synth ss(2*SAMPLE_RATE*NUM_SECONDS, 1.0, 40.0);

void update(float dt){
	for(int i=0; i<winw; i++){
		points[i] = ss.data[2*(i+phase)];
	}
	if(mode == 1 && phase < ss.len){
		phase++;
	}else if(mode == 2 && phase > 0){
		phase --;
	}

	win.clear(sf::Color::Black);
	sf::VertexArray ls(sf::LinesStrip, winw);
	for(int i = 0; i<winw; i++){
		if(2*(i+phase) % (SAMPLE_RATE/4) == 0) {
			sf::VertexArray second(sf::LinesStrip, 2);
			second[0].color = sf::Color::Blue;
			second[0].position = sf::Vector2f(i, 0);
			second[1].color = sf::Color::Red;
			second[1].position = sf::Vector2f(i, winh);
			win.draw(second);
		}
		ls[i].color = sf::Color::Green;
		ls[i].position = sf::Vector2f(i, ((winh/2) + (100*points[i])));
	}
	win.draw(ls);
	win.display();
}

int main(){
	ss.generate();
	while (win.isOpen()){
		while (win.pollEvent(event)){
			if (event.type == sf::Event::Closed){
				win.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				win.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
				mode = 1;
			}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
				mode = 2;
			}else{
				mode = 0;
			}
		}
		float dt = gameclock.getElapsedTime().asSeconds();
		gameclock.restart();
		update(dt);
	}
	return 0;
}
