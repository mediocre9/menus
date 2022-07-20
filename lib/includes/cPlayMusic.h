#pragma once
//#include <string>
#define DLL __declspec(dllexport)

// Independent PlayMusic class...
class DLL PlayMusic
{
    public:
        void Play(const char* t_sound_name, const char* t_instance_window, const int t_volume) ;
        void Stop(void);
    private:
        std::string m_sound_name, m_instance_window;
        int m_volume;
};
