#include "includes\Menu.h"
#include <windows.h>
#include <iostream>
#include <thread>
#include <memory>

const int BACKGROUND = Color.WHITE_BLACK;
const int HOVER = Color.BRIGHT_BLUE_BRIGHT_WHITE;

void dropDownMenu();

int main(){
    CursorState(10,false);
    system("cls & color 3f & mode 60,30");
    
    // window frame....
    std::unique_ptr<Window> 
        frame(new Frame(Dimension(20,40), Coordinate(10,5), 
        Window::LINE, Color.WHITE_BLACK));
        
    frame->shadow(true);
    frame->render();
    
    // sub window....
    std::unique_ptr<Window> 
        subFrame(new Frame(Dimension(5,33), Coordinate(12,15),
        Window::PIPE, Color.BRIGHT_WHITE_BLACK));
        
    subFrame->shadow(true);
    subFrame->render();
    
    std::unique_ptr<Menu> h_menu(new HorizontalMenu({
            {" File ", HOVER},
            {" Edit ", BACKGROUND},
            {" View ", BACKGROUND},
            {" Help ", BACKGROUND},
        }, 
        Coordinate(4, 6)
    ));
    
    h_menu->setTheme(Theme(BACKGROUND, HOVER));

    
    while(true){
        
        while(!h_menu->isItemSelected()){
            h_menu->render();
        }
        
        h_menu->setItemSelectionState(false);
        
        switch(h_menu->getItemPosition()){
            case 1:
                dropDownMenu();
            break;
            
            case 2:
                std::cout << "Edit selected";
            break;
            
            case 3:
                std::cout << "View selected";
            break;
        }
        
    }
    return 0;
}


// vertical menus........
void dropDownMenu(){
    std::unique_ptr<Menu> v_menu(new VerticalMenu({
            {" New   ", HOVER},
            {" Open  ", 0x00F0},
            {" Save  ", 0x00F0},
            {" Print ", 0x00F0},
        }, 
        Coordinate(11, 7)
    ));
    
    v_menu->setTheme(Theme(0x00F0, HOVER));

    
    while(true){
        
        while(!v_menu->isItemSelected()){
            v_menu->render();
        }
        
        v_menu->setItemSelectionState(false);
        
        switch(v_menu->getItemPosition()){
            case 1:
                main();
            break;
            
            case 2:
                std::cout << "Open selected";
            break;
            
            case 3:
                std::cout << "Save selected";
            break;
            
            case 4:
                std::cout << "Print selected";
            break;
        }
    }
}

