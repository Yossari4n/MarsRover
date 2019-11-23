#include "AudioSource.h"
#include "Transform.h"

AudioSource::AudioSource() {
    alGenSources(1, &m_ID);
}

void AudioSource::Initialize() {

}

void AudioSource::Destroy() {

}
