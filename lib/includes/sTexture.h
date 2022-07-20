#pragma once
#define DLL __declspec(dllexport)

// Textural Parameters for graphics...
extern struct Texture {
    enum texture
    {
        BRAILLE = 176,
        GRAIN = 177,
        PATTERN = 178,
        SOLID = 219,
        BRICK,
        lPILLAR,
        rPILLAR,
        BRICK2,
        BRICK3 = 254
    };
} Texture;
