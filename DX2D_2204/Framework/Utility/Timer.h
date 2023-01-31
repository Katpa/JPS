#pragma once

class Timer
{
private:
    Timer();
    ~Timer();

public:
    static Timer* Get()
    {
        if (instance == nullptr)
            instance = new Timer();

        return instance;
    }
    static void Delete()
    {
        delete instance;
    }

    void Update();

    void SetLockFPS(float lockFPS) { this->lockFPS = lockFPS; }

    int GetFPS() { return frameRate; }
    float GetElapsedTime() { return timeElapsed; }

private:
    static Timer* instance;

    float timeScale = 0;
    float timeElapsed = 0;

    __int64 curTime = 0;
    __int64 lastTime = 0;
    __int64 periodFrequency = 0;

    int frameRate = 0;
    int frameCount = 0;

    float oneSecCount = 0;

    float lockFPS = 0;
};