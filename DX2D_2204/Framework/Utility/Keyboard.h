#pragma once

#define KEY_MAX 255

class Keyboard
{
private:
    enum KeyState
    { 
        NONE, DOWN, UP, PRESS
    };

    Keyboard();
    ~Keyboard();


public:
    static Keyboard* Get()
    {
        if (instance == nullptr)
            instance = new Keyboard();

        return instance;
    }

    static void Delete() { delete instance; }

    void Update();

    bool Down(UINT key) { return mapState[key] == DOWN; }
    bool Up(UINT key) { return mapState[key] == UP; }
    bool Press(UINT key) { return mapState[key] == PRESS; }

private:
    static Keyboard* instance;

    BYTE curState[KEY_MAX];
    BYTE oldState[KEY_MAX];
    KeyState mapState[KEY_MAX];
};