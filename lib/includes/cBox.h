#pragma once
#define DLL __declspec(dllexport)

// Heirarchical inheritance
// Our Parent class: Box
// Hierarchy of our classes structure
// Box -> Triangle
// Box -> ProgressBar -> Line
class DLL Box
{
    public:
        Box();
        Box(int length,  int width, int position_X, int position_Y, int border, int middle_block, int colour);
        virtual void Render(void);
    protected:
        int border, middle_block;
        int length, width;
        int position_X, position_Y;
        int colour;
};
