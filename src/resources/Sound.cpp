#include "Sound.h"

Sound::Sound(const std::string& path) {
    m_ID = alutCreateBufferFromFile(path.c_str());

    alGetBufferi(m_ID, AL_SIZE, &m_Size);
    alGetBufferi(m_ID, AL_BITS, &m_Bits);
    alGetBufferi(m_ID, AL_CHANNELS, &m_Channels);
    alGetBufferi(m_ID, AL_FREQUENCY, &m_Frequency);
    
    ALfloat length_in_samples = m_Size * 8 / (m_Channels * m_Bits);
    m_Length = length_in_samples / static_cast<ALfloat>(m_Frequency);
}

Sound::~Sound() {
    alDeleteBuffers(1, &m_ID);
}
