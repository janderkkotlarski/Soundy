#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int sounding(std::vector <sf::Sound>& sounds, const int which_sound)
{
	int count{0};
	assert(count == 0);
	
	while (count < static_cast<int>(sounds.size()))
	{
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(count + 27)))
		{
			if (which_sound != -1)
			{
				sounds[count].stop();
			}
						
			sounds[count].play();
			return count;
		}
				
		++count;
	}
	
	return -1;	
}

int window_loop(const std::string& program_name, std::vector <sf::Sound>& sounds)
{
	assert(program_name != "");
	
	int count{0};
	assert(count == 0);
	
	const float windes{100.0f};
	assert(windes > 0.0f);
	
	int which_sound{-1};
	assert(which_sound == -1);
	
	const sf::Color black{sf::Color(0, 0, 0)};
	
	sf::RenderWindow window(sf::VideoMode(windes, windes), program_name, sf::Style::Default);
	
	while (window.isOpen())
	{
		sf::Event event;		
		window.clear(black);
		
		which_sound = sounding(sounds, which_sound);
		
		window.display();
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
			return 0;
		}
		
		while (window.pollEvent(event))
		{			
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return 0;
			}		
		}
	}
	
	return 1;
	
}

int main()
{
	std::string program_name{"Soundy V0.1"};
	assert(program_name != "");
	
	std::vector <std::string> sound_names;
	sound_names.push_back("Bassy.wav");
	
	int count{0};
	assert(count == 0);
	
	std::vector <sf::SoundBuffer> buffers;
	std::vector <sf::Sound> sounds;
	
	while (count < static_cast<int>(sound_names.size()))
	{
		assert(sound_names[count] != "");
		
		sf::SoundBuffer buffer;
		
		if (!buffer.loadFromFile(sound_names[count]))
		{
			return 1;
		}
		
		buffers.push_back(buffer);
		
		
		sf::Sound sound;
		sound.setBuffer(buffers[count]);
		
		sounds.push_back(sound);
		
		++count;
	}
	
	return window_loop(program_name, sounds);	
}
