#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

void sounding(std::vector <sf::Sound>& sounds, std::vector <sf::SoundBuffer>& buffers, bool& pressing)
{
	int count{0};
	assert(count == 0);
	
	int counting{0};
	assert(counting == 0);
		
	while (count < static_cast<int>(sounds.size()))
	{
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(count + 27)))
		{
			if (!pressing)
			{
				sounds[count].setBuffer(buffers[count]);			
				sounds[count].play();				
			}
			
			pressing = true;
			
			counting = 0;
		}
		else if (pressing)
		{
			++counting;
		}

		++count;
	}
	
	if (counting == static_cast<int>(sounds.size()) && pressing)
	{
		pressing = false;
	}
}

int window_loop(const std::string& program_name, std::vector <sf::Sound>& sounds, std::vector <sf::SoundBuffer>& buffers,
				sf::Music& music)
{
	assert(program_name != "");
	
	int count{0};
	assert(count == 0);
	
	const float windes{100.0f};
	assert(windes > 0.0f);
	
	bool pressing{false};
	assert(!pressing);
	
	const sf::Color black{sf::Color(0, 0, 0)};
	
	sf::RenderWindow window(sf::VideoMode(windes, windes), program_name, sf::Style::Default);
	
	music.setLoop(true);
	music.play();
	
	while (window.isOpen())
	{
		sf::Event event;		
		window.clear(black);
		
		sounding(sounds, buffers, pressing);
		
		window.display();
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			music.stop();
			window.close();
			return 0;
		}
		
		while (window.pollEvent(event))
		{			
			if (event.type == sf::Event::Closed)
			{
				music.stop();
				window.close();
				return 0;
			}		
		}
	}
	
	return 1;
	
}

int main()
{
	std::string program_name{"Soundy V0.2"};
	assert(program_name != "");
	
	std::vector <std::string> sound_names;
	sound_names.push_back("Bassy.wav");
	sound_names.push_back("Stringy.wav");
	sound_names.push_back("Synthy.wav");
	
	const std::string music_name{"Drummy_Loopy.wav"};
	assert(music_name != "");
	
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
		
		const sf::Sound sound;		
		sounds.push_back(sound);		
		
		++count;
	}
	
	sf::Music music;
	
	if (!music.openFromFile(music_name))
	{
		return -1;
	}
	
	return window_loop(program_name, sounds, buffers, music);	
}
