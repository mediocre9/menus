#pragma once
#define DLL __declspec(dllexport) 

// derived class of progressbar
class DLL Line : public ProgressBar 
{
	public:
		Line();
		Line(int length, int t_Line, int position_X, int position_Y, int colour);
		void Render(void);
	private:
	    int t_Line;
};
