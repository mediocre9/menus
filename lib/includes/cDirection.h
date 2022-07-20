#pragma once
#define DLL __declspec(dllexport)

class DLL Direction
{
    public:
        enum ACCESS_KEYS {
            ESCAPE = 27, SPACE = 32, A = 65, B, C,
            D, E, F, G, H, I,
            J, K, L, M, N, O,
            P, Q, R, S, T, U,
            V, W, X, Y, Z
        };

        int UP(int& object, int colour, int& position_X, int& position_Y, ACCESS_KEYS keys, int speed);
        int DOWN(int& object, int colour, int& position_X, int& position_Y, ACCESS_KEYS Keys, int speed);
        int RIGHT(int& object, int colour, int& position_X, int& position_Y, ACCESS_KEYS Keys, int speed);
        int LEFT(int& object, int colour, int& position_X, int& position_Y, ACCESS_KEYS Keys, int speed);
    private:
        int object , Keys , speed ;
        int position_X, position_Y , colour;
};

