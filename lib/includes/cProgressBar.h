#pragma once
#define DLL __declspec(dllexport)

// derived class of our Box class
class DLL ProgressBar : public Box
{
    public:
        ProgressBar();
        ProgressBar(int length, int position_X, int position_Y, int colour, int sleep);
        void Render(void);
    protected:
        int sleep;
};
