#pragma once
#define DLL __declspec(dllexport) 

class DLL Triangle:public Box {
	public:
		Triangle() ;
		Triangle(int length, int position_X, int position_Y, int texture, int colour) ;
		void Render(void) ;
	private:
	    int texture ;
};
