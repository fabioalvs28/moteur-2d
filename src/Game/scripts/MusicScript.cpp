#include "pch.h"
#include "MusicScript.h"


MusicScript::MusicScript(const std::string& musicFile)
{
    if (!m_music.openFromFile(musicFile))
    {
        Debug::Log("Error loading music");
        return;
    }
    
    m_music.setLooping(true);
    m_music.play();
}

void MusicScript::OnUpdate()
{
    m_activeSounds.erase(std::remove_if(
        m_activeSounds.begin(), m_activeSounds.end(),
        [](const sf::Sound& sound) {
            return sound.getStatus() == sf::Sound::Status::Stopped;
        }),
        m_activeSounds.end());
}

void MusicScript::PlayMusic(int key)
{
    auto it = m_musicPaths.find(key);
    if (it != m_musicPaths.end())
    {
        if (!m_music.openFromFile(it->second))
        {
            std::cerr << "Erreur chargement musique key=" << key << std::endl;
            return;
        }
        m_music.setLooping(true);
        m_music.play();
    }
}

void MusicScript::AddMusic(int key, const std::string& filepath)
{
    m_musicPaths[key] = filepath;
}

void MusicScript::AddSound(const std::string& SoundName, const std::string& filepath)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filepath))
    {
        std::cerr << "Erreur chargement son: " << filepath << std::endl;
        return;
    }

    m_soundBuffers[SoundName] = std::move(buffer);
}

void MusicScript::PlaySoundScript(const std::string& SoundName)
{
    auto it = m_soundBuffers.find(SoundName);
    if (it != m_soundBuffers.end())
    {
        sf::Sound sound(it->second);
        sound.play();
        m_activeSounds.push_back(std::move(sound));
    }
}
void MusicScript::PauseMusic()
{
    m_music.pause();
}

void MusicScript::StopMusic()
{
    m_music.stop();
}

void MusicScript::SetVolume(float volume)
{
    m_music.setVolume(volume);
}