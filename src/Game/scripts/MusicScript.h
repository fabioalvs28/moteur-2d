#pragma once
#include "scripts/script.h"

class MusicScript : public IScript
{
public:
    MusicScript(const std::string& musicFile);
    MusicScript() = default;
    
    void OnUpdate() override;
    void PlayMusic(int key);
    void PlaySoundScript(const std::string& SoundName);
    void PauseMusic();
    void StopMusic();
    void SetVolume(float volume);

    void AddMusic(int key, const std::string& filepath);
    void AddSound(const std::string& SoundName, const std::string& filepath);

private:
    sf::Music m_music;
    std::map<int, std::string> m_musicPaths;

    std::map<std::string, sf::SoundBuffer> m_soundBuffers;
    std::vector<sf::Sound> m_activeSounds;
};