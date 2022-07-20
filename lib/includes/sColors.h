#pragma once
#define DLL __declspec(dllexport)

// structure of colors...
extern struct Color {
    enum HexaDecimalColours {
        BLACK_BLACK         =   0x0000,
        BLACK_BLUE          =   0x0001,
        BLACK_GREEN         =   0x0002,
        BLACK_AQUA          =   0x0003,
        BLACK_RED           =   0x0004,
        BLACK_PURPLE        =   0x0005,
        BLACK_YELLOW        =   0x0006,
        BLACK_WHITE         =   0x0007,
        BLACK_GRAY          =   0x0008,
        BLACK_BRIGHT_BLUE   =   0x0009,

        //BLUE
        BLUE_BLACK          =   0x0010,
        BLUE_BLUE           =   0x0011,
        BLUE_GREEN          =   0x0012,
        BLUE_AQUA           =   0x0013,
        BLUE_RED            =   0x0014,
        BLUE_PURPLE         =   0x0015,
        BLUE_YELLOW         =   0x0016,
        BLUE_WHITE          =   0x0017,
        BLUE_GRAY           =   0x0018,

        // GREEN
        GREEN_BLACK         =   0x0020,
        GREEN_BLUE          =   0x0021,
        GREEN_GREEN         =   0x0022,
        GREEN_AQUA          =   0x0023,
        GREEN_RED           =   0x0024,
        GREEN_PURPLE        =   0x0025,
        GREEN_YELLOW        =   0x0026,
        GREEN_WHITE         =   0x0027,
        GREEN_GRAY          =   0x0028,

        // AQUA
        AQUA_BLACK          =   0x0030,
        AQUA_BLUE           =   0x0031,
        AQUA_GREEN          =   0x0032,
        AQUA_AQUA           =   0x0033,
        AQUA_RED            =   0x0034,
        AQUA_PURPLE         =   0x0035,
        AQUA_YELLOW         =   0x0036,
        AQUA_WHITE          =   0x0037,
        AQUA_GRAY           =   0x0038,

        //RED
        RED_BLACK           =   0x0040,
        RED_BLUE            =   0x0041,
        RED_GREEN           =   0x0042,
        RED_AQUA            =   0x0043,
        RED_RED             =   0x0044,
        RED_PURPLE          =   0x0045,
        RED_YELLOW          =   0x0046,
        RED_WHITE           =   0x0047,
        RED_GRAY            =   0x0048,

        // PURPLE
        PURPLE_BLACK        =   0x0050,
        PURPLE_BLUE         =   0x0051,
        PURPLE_GREEN        =   0x0052,
        PURPLE_AQUA         =   0x0053,
        PURPLE_RED          =   0x0054,
        PURPLE_PURPLE       =   0x0055,
        PURPLE_YELLOW       =   0x0056,
        PURPLE_WHITE        =   0x0057,
        PURPLE_GRAY         =   0x0058,

        // YELLOW
        YELLOW_BLACK        =   0x0060,
        YELLOW_BLUE         =   0x0061,
        YELLOW_GREEN        =   0x0062,
        YELLOW_AQUA         =   0x0063,
        YELLOW_RED          =   0x0064,
        YELLOW_PURPLE       =   0x0065,
        YELLOW_YELLOW       =   0x0066,
        YELLOW_WHITE        =   0x0067,
        YELLOW_GRAY         =   0x0068,

        // WHITE
        WHITE_BLACK         =   0x0070,
        WHITE_BLUE          =   0x0071,
        WHITE_GREEN         =   0x0072,
        WHITE_AQUA          =   0x0073,
        WHITE_RED           =   0x0074,
        WHITE_PURPLE        =   0x0075,
        WHITE_YELLOW        =   0x0076,
        WHITE_WHITE         =   0x0077,
        WHITE_GRAY          =   0x0078,

        //GREY
        GRAY_BLACK          =   0x0080,
        GRAY_BLUE           =   0x0081,
        GRAY_GREEN          =   0x0082,
        GRAY_AQUA           =   0x0083,
        GRAY_RED            =   0x0084,
        GRAY_PURPLE         =   0x0085,
        GRAY_YELLOW         =   0x0086,
        GRAY_WHITE          =   0x0087,
        GRAY_GRAY           =   0x0088,

        // BRIGHT GREEN
        BRIGHT_GREEN_BLACK      =   0x00A0,
        BRIGHT_GREEN_BLUE       =   0x00A1,
        BRIGHT_GREEN_GREEN      =   0x00A2,
        BRIGHT_GREEN_AQUA       =   0x00A3,
        BRIGHT_GREEN_RED        =   0x00A4,
        BRIGHT_GREEN_PURPLE     =   0x00A5,
        BRIGHT_GREEN_YELLOW     =   0x00A6,
        BRIGHT_GREEN_WHITE      =   0x00A7,
        BRIGHT_GREEN_GRAY       =   0x00A8,

        //BRIGHT AQUA
        BRIGHT_AQUA_BLACK       =   0x00B0,
        BRIGHT_AQUA_BLUE        =   0x00B1,
        BRIGHT_AQUA_GREEN       =   0x00B2,
        BRIGHT_AQUA_AQUA        =   0x00B3,
        BRIGHT_AQUA_RED         =   0x00B4,
        BRIGHT_AQUA_PURPLE      =   0x00B5,
        BRIGHT_AQUA_YELLOW      =   0x00B6,
        BRIGHT_AQUA_WHITE       =   0x00B7,
        BRIGHT_AQUA_GRAY        =   0x00B8,

        // BRIGHT RED
        BRIGHT_RED_BLACK        =   0x00C0,
        BRIGHT_RED_BLUE         =   0x00C1,
        BRIGHT_RED_GREEN        =   0x00C2,
        BRIGHT_RED_AQUA         =   0x00C3,
        BRIGHT_RED_RED          =   0x00C4,
        BRIGHT_RED_PURPLE       =   0x00C5,
        BRIGHT_RED_YELLOW       =   0x00C6,
        BRIGHT_RED_WHITE        =   0x00C7,
        BRIGHT_RED_GRAY         =   0x00C8,


        // BRIGHT PURPLE
        BRIGHT_PURPLE_BLACK     =   0x00D0,
        BRIGHT_PURPLE_BLUE      =   0x00D1,
        BRIGHT_PURPLE_GREEN     =   0x00D2,
        BRIGHT_PURPLE_AQUA      =   0x00D3,
        BRIGHT_PURPLE_RED       =   0x00D4,
        BRIGHT_PURPLE_PURPLE    =   0x00D5,
        BRIGHT_PURPLE_YELLOW    =   0x00D6,
        BRIGHT_PURPLE_WHITE     =   0x00D7,
        BRIGHT_PURPLE_GRAY      =   0x00D8,


        // BRIGHT YELLOW
        BRIGHT_YELLOW_BLACK     =   0x00E0,
        BRIGHT_YELLOW_BLUE      =   0x00E1,
        BRIGHT_YELLOW_GREEN     =   0x00E2,
        BRIGHT_YELLOW_AQUA      =   0x00E3,
        BRIGHT_YELLOW_RED       =   0x00E4,
        BRIGHT_YELLOW_PURPLE    =   0x00E5,
        BRIGHT_YELLOW_YELLOW    =   0x00E6,
        BRIGHT_YELLOW_WHITE     =   0x00E7,
        BRIGHT_YELLOW_GRAY      =   0x00E8,

        // WHITE
        BRIGHT_WHITE_BLACK      =   0x00F0,
        BRIGHT_WHITE_BLUE       =   0x00F1,
        BRIGHT_WHITE_GREEN      =   0x00F2,
        BRIGHT_WHITE_AQUA       =   0x00F3,
        BRIGHT_WHITE_RED        =   0x00F4,
        BRIGHT_WHITE_PURPLE     =   0x00F5,
        BRIGHT_WHITE_YELLOW     =   0x00F6,
        BRIGHT_WHITE_WHITE      =   0x00F7,
        BRIGHT_WHITE_GRAY       =   0x00F8,

        // BRIGHTSSS
        BRIGHT_GREEN_BRIGHT_BLUE        =   0x00A9,
        BRIGHT_GREEN_BRIGHT_GREEN       =   0x00AA,
        BRIGHT_GREEN_BRIGHT_AQUA        =   0x00AB,
        BRIGHT_GREEN_BRIGHT_RED         =   0x00AC,
        BRIGHT_GREEN_BRIGHT_PURPLE      =   0x00AD,
        BRIGHT_GREEN_BRIGHT_YELLOW      =   0x00AE,
        BRIGHT_GREEN_BRIGHT_WHITE       =   0x00AF,

        // BLUE
        BRIGHT_BLUE_BRIGHT_BLUE         =   0x0099,
        BRIGHT_BLUE_BRIGHT_GREEN        =   0x009A,
        BRIGHT_BLUE_BRIGHT_AQUA         =   0x009B,
        BRIGHT_BLUE_BRIGHT_RED          =   0x009C,
        BRIGHT_BLUE_BRIGHT_PURPLE       =   0x009D,
        BRIGHT_BLUE_BRIGHT_YELLOW       =   0x009E,
        BRIGHT_BLUE_BRIGHT_WHITE        =   0x009F,

        // AQUA
        BRIGHT_AQUA_BRIGHT_BLUE         =   0x00B9,
        BRIGHT_AQUA_BRIGHT_GREEN        =   0x00BA,
        BRIGHT_AQUA_BRIGHT_AQUA         =   0x00BB,
        BRIGHT_AQUA_BRIGHT_RED          =   0x00BC,
        BRIGHT_AQUA_BRIGHT_PURPLE       =   0x00BD,
        BRIGHT_AQUA_BRIGHT_YELLOW       =   0x00BE,
        BRIGHT_AQUA_BRIGHT_WHITE        =   0x00BF,

        // RED
        BRIGHT_RED_BRIGHT_BLUE          =   0x00C9,
        BRIGHT_RED_BRIGHT_GREEN         =   0x00CA,
        BRIGHT_RED_BRIGHT_AQUA          =   0x00CB,
        BRIGHT_RED_BRIGHT_RED           =   0x00CC,
        BRIGHT_RED_BRIGHT_PURPLE        =   0x00CD,
        BRIGHT_RED_BRIGHT_YELLOW        =   0x00CE,
        BRIGHT_RED_BRIGHT_WHITE         =   0x00CF,

        // PURPLE
        BRIGHT_PURPLE_BRIGHT_BLUE       =   0x00D9,
        BRIGHT_PURPLE_BRIGHT_GREEN      =   0x00DA,
        BRIGHT_PURPLE_BRIGHT_AQUA       =   0x00DB,
        BRIGHT_PURPLE_BRIGHT_RED        =   0x00DC,
        BRIGHT_PURPLE_BRIGHT_PURPLE     =   0x00DD,
        BRIGHT_PURPLE_BRIGHT_YELLOW     =   0x00DE,
        BRIGHT_PURPLE_BRIGHT_WHITE      =   0x00DF,

        //YELLOW
        BRIGHT_YELLOW_BRIGHT_BLUE       =   0x00E9,
        BRIGHT_YELLOW_BRIGHT_GREEN      =   0x00EA,
        BRIGHT_YELLOW_BRIGHT_AQUA       =   0x00EB,
        BRIGHT_YELLOW_BRIGHT_RED        =   0x00EC,
        BRIGHT_YELLOW_BRIGHT_PURPLE     =   0x00ED,
        BRIGHT_YELLOW_BRIGHT_YELLOW     =   0x00EE,
        BRIGHT_YELLOW_BRIGHT_WHITE      =   0x00EF,

        // WHITE
        BRIGHT_WHITE_BRIGHT_BLUE        =   0x00F9,
        BRIGHT_WHITE_BRIGHT_GREEN       =   0x00FA,
        BRIGHT_WHITE_BRIGHT_AQUA        =   0x00FB,
        BRIGHT_WHITE_BRIGHT_RED         =   0x00FC,
        BRIGHT_WHITE_BRIGHT_PURPLE      =   0x00FD,
        BRIGHT_WHITE_BRIGHT_YELLOW      =   0x00FE,
        BRIGHT_WHITE_BRIGHT_WHITE       =   0x00FF
    };
}
Color;

