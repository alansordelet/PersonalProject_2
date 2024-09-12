#pragma once
#include "SFML/Audio.hpp"
#include<deque>
#include<map>
#include"stateManager.h"
#include"tools.h"

enum AudioEnum
{
	ZERO,
	MUSIC,
	SOUND
};
struct AudioType
{
	std::string type;
	int typo;
};

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	inline void loadSound(const std::string& name, const std::string& filename)
	{
		soundBuffers[name].loadFromFile("..\\Ressources\\SoundnMusic\\" + filename);
		sounds[name].setBuffer(soundBuffers[name]);
		mysoundmanagerisbroken = false;
		OnePlay = false;
	}

	inline void loadMusic(const std::string& name, const std::string& filename)
	{
		soundBuffers[name].loadFromFile("..\\Ressources\\" + filename);
		sounds[name].setBuffer(soundBuffers[name]);
	
	}
	
	void LoadSoundMenu();
	void LoadSoundBiome();
	void playSoundGame();
	void playSound(const std::string& name)
	{
		if (playOnce == false)
		{
			sounds[name].play();
			playOnce = true;
		}

		if (sounds[name].getStatus() == Sound::Stopped)
			playOnce = false;
	}

	void playSoundQuick(const std::string& name)
	{
		if (DuoOnce == true)
			DuoOnce = false;
		if (DuoOnce == false)
		{
			sounds[name].play();
			DuoOnce = true;
		}
	}

	void playSoundsRandom(const std::string& _name, const std::string& _name2)
	{
		TimerRandom += tools::GetTimeDelta();
		if (TimerRandom > 1)
		{
			Random = tools::iRand(1, 2);
		}
		if (Random == 1)
		{
			if (playRandom == false)
			{
				sounds[_name].play();
				playRandom = true;
			}
		}
		if (Random == 2)
		{
			if (playRandom == false)
			{
				sounds[_name2].play();
				playRandom = true;
			}
		}
		if (TimerRandom > 5)
		{
			playRandom = false;
			TimerRandom = 0;
		}
	}

	void playSoundRandom(const std::string& _name, float SecondstoPlay, float SecondstoReset)
	{
		TimerPlay += tools::GetTimeDelta();
		if (TimerPlay > SecondstoPlay)
		{
			if (playRandom == false)
			{
				sounds[_name].play();	
				playRandom = true;
			}
			TimerPlay = 0;
		}
		else
		{
			playRandom = false;
		}
		
	}

	void playSoundOnce(const std::string& _name)
	{
		if (OnePlay == false)
		{
			sounds[_name].play();
			OnePlay = true;
		}
	}
	void playSoundOnce2(const std::string& _name)
	{
		if (mysoundmanagerisbroken == false)
		{
			sounds[_name].play();
			mysoundmanagerisbroken = true;
		}
	}

	void stopSound(const std::string& name)
	{
		sounds[name].stop();
	}

	void stopSoundAll()
	{
		/*if (stopsounds == true)
			stopsounds = false;*/
		for (auto& i : sounds)
		{
			if (stopsounds == false)
			{
				i.second.stop();
				stopsounds = true;
			}
		}
	}

	void pauseSound(const std::string& name)
	{
		sounds[name].pause();
	}

	void setSoundLoop(const std::string& name, bool loop)
	{
		sounds[name].setLoop(loop);
	}

	void setSoundVolumeSOUND(const std::string& name, float volume)
	{
		for (auto& i : sounds)
		{
			if (i.first == name)
			{
				i.second.setVolume(volume);
			}
		}
	}

	void setSoundVolumeMUSIC(const std::string& name)
	{
		for (auto& i : sounds)
		{
			if (i.first == name)
			{
				i.second.setVolume(volumeMusic);
			}
		}
	}

	void setAllSoundVolumeSOUND()
	{
		for (auto& i : sounds)
		{
			i.second.setVolume(volumeSons);
		}
	}

	void setAllSoundVolumeMUSIC()
	{
		for (auto& i : sounds)
		{
			i.second.setVolume(volumeMusic);
		}
	}

	inline int GetMusicVol() { return volumeMusic; }
	inline int GetSoundVol() { return volumeSons; }

	inline void addVolumeMusic(int _addedVolume) { setAllSoundVolumeMUSIC(); volumeMusic = volumeMusic + _addedVolume; }
	inline void addVolumeSound(int _addedVolume) { setAllSoundVolumeSOUND(); volumeSons = volumeSons + _addedVolume; }

private:
	std::map<std::string, sf::SoundBuffer> soundBuffers;
	std::map<std::string, sf::Sound> sounds;
	int volumeSons;
	int volumeMusic;
	bool playOnce = false;
	bool DuoOnce = false;
	bool playRandom = false;
	bool OnePlay = false;
	bool stopsounds = false;
	bool mysoundmanagerisbroken = false;
	float BufferTimer;
	float TimerRandom;
	float TimerPlay;
	int Random;
};

class Audio3D
{
public:
	Audio3D() {};
	~Audio3D() {};

	void loadSound3D(const std::string& name, const std::string& filename, float _MinDistance, float _Attenuation)
	{
		soundBuffers3D[name].loadFromFile("..\\Ressources\\Sounds\\" + filename);
		sounds3D[name].setBuffer(soundBuffers3D[name]);
		sounds3D[name].setMinDistance(_MinDistance);
		sounds3D[name].setAttenuation(_Attenuation);
	}

	void playSound(const std::string& name, sf::Vector3f pos)
	{
		sounds3D[name].setPosition(pos);
		sounds3D[name].play();
	}

	void setListenerPosition(sf::Vector3f pos)
	{
		sf::Listener::setPosition(pos);
	}

	void setListenerDirection(sf::Vector3f dir)// relative to direction of player (Y = Z in 2D games)
	{
		sf::Listener::setDirection(dir);
	}

	void setAttenuation(const std::string& name, float _attenuation)
	{
		sounds3D[name].setAttenuation(_attenuation);
	}

	void setMinimumDistance(const std::string& name, float _Distance)
	{
		sounds3D[name].setMinDistance(_Distance);
	}

	void setSoundVolumeSOUND3D(const std::string& name, float volume)
	{
		if (AudioType == SOUND)
			sounds3D[name].setVolume(volume);
	}

	void setSoundVolumeMUSIC3D(const std::string& name, float volume)
	{
		if (AudioType == MUSIC)
			sounds3D[name].setVolume(volume);
	}

private:
	static int AudioType;
	std::map<std::string, sf::SoundBuffer> soundBuffers3D;
	std::map<std::string, sf::Sound> sounds3D;
};




