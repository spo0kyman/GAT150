#pragma once
#include "Component.h"
#include "Audio/AudioChannel.h"

namespace nc {
	class AudioComponent : public Component {
	public:
		virtual void Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual void Update() override;

		void Read(const rapidjson::Value& value) override;

		void Play();
		void Stop();
		void SetSoundName(const std::string& soundName) { m_soundName = soundName; }

	protected:
		std::string m_soundName;
		bool m_loop{ false };
		bool m_playOnAwake{ false };

		AudioChannel m_channel;
	};
}