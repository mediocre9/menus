#pragma once

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "..\lib\includes\vain_engine.h"
using namespace eng;

/*
    Definition: Change the system UI values according to your 
    preference. 
*/

namespace atr
{
    const int WINDOW_BORDER_TEXTURE        = eng::Texture.SOLID;
    const int WINDOW_SURFACE_TEXTURE       = eng::Texture.SOLID;
    
    const int WINDOW_LABEL_COLOR           = eng::Color.WHITE_BLACK;
    const int WINDOW_FOOTER_LABEL_COLOR    = eng::Color.WHITE_GRAY;
    const int WINDOW_BACKGROUND_COLOR      = eng::Color.BLACK_WHITE;
    
    const int DEFAULT_OPTION_COLOR         = eng::Color.BRIGHT_BLUE_BRIGHT_WHITE;
    const int MARKER_OPTION_COLOR          = eng::Color.BRIGHT_RED_BRIGHT_WHITE;
}
#endif


