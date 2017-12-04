#include "AudioLoader.h"
#include <SDL.h>
#include <SDL_mixer.h>

namespace Common 
{
   void AudioClip::play()
   {
      m_usedChannel = Mix_PlayChannel(-1, m_mixChunk, 0);
   }

   void AudioClip::stop()
   {
      if (m_usedChannel != -1)
      {
         Mix_HaltChannel(m_usedChannel);
         m_usedChannel = -1;
      }      
   }

   void AudioClip::load(const std::wstring filePath)
   {
      m_mixChunk = Mix_LoadWAV(std::string(filePath.begin(), filePath.end()).c_str());
   }
   void AudioClip::freeMem() const
   {
      Mix_FreeChunk(m_mixChunk);
   }

   AudioLoader::~AudioLoader()
   {
      for (auto clip : m_clips)
      {
         clip->freeMem();
      }
   }

   bool AudioLoader::init()
   {
      //Initialize SDL_mixer
      if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
      {
         return false;
      }
      return true;
   }

   std::shared_ptr<AudioClip> AudioLoader::createAndLoadAudioClip(const std::wstring filePath)
   {
      std::shared_ptr<AudioClip> newClip = std::make_shared<AudioClip>();
      newClip->load(filePath);
      m_clips.push_back(newClip);

      return newClip;
   }

  
}