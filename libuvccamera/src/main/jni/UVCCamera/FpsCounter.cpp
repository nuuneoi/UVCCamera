#include "FpsCounter.h"

FpsCounter::FpsCounter()
:   m_size(0),
    m_max_size(100) {
    timestamp = new long[m_max_size];
}

FpsCounter::~FpsCounter() {
    SAFE_DELETE_ARRAY(timestamp)
}

void FpsCounter::onNewFrameAvailable() {
    if (this->size() >= this->capacity()) {
        m_max_size *= 2;
        long* new_array = new long[m_max_size];
        for (int i = 0; i < this->size(); i++)
            new_array[i] = timestamp[i];
        SAFE_DELETE_ARRAY(timestamp)
        timestamp = new_array;
    }

    // Add new timestamp
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long current_timestamp = (tp.tv_sec * 1000) + tp.tv_usec / 1000;
    timestamp[m_size] = current_timestamp;
    m_size++;

    // Prune
    for (int i = 0; i < m_size; i++) {
        if (timestamp[i] < current_timestamp - FPS_INTERVAL_MS) {
            timestamp[i] = timestamp[m_size - 1];
            m_size--;
            i--;
        }
    }

    // LOGI("Timestamp: %ld", current_timestamp);
    // LOGI("Fps: %d", this->getCurrentFps());
}
