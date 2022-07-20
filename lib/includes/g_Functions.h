#pragma once
#define DLL __declspec(dllexport) 

// declaring global functions...
DLL void Paint(int hex);
DLL void SetPosition(int X, int Y);
DLL void Clear(void);
DLL void CursorState(int size, bool b_visibility) ;
