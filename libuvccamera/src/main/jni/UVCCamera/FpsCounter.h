#ifndef FPSCOUNTER_H_
#define FPSCOUNTER_H_

#include <sys/time.h>

#include "utilbase.h"

#define FPS_INTERVAL_MS 2000

class FpsCounter {
public:
    FpsCounter();
    ~FpsCounter();

    void onNewFrameAvailable();

    int size() { return m_size; }
    int capacity() { return m_max_size; }
    int getCurrentFps() { return m_size * 1000 / FPS_INTERVAL_MS; }

private:
    long* timestamp;
    int m_max_size;
    int m_size;
};

#endif
