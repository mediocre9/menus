#include "includes\Menu.h"
#include <iostream>
#include <memory>

using std::cout;

const int BACKGROUND = Color.BRIGHT_WHITE_BLACK;
const int FOREGROUND = Color.BRIGHT_BLUE_BRIGHT_WHITE;

void subMenu();

void menu(){
    system("color 07 & mode 70,30");
    
    MenuItem items[] = {
        {" File    ", FOREGROUND},  
        {" Edit    ", BACKGROUND},  
        {" Search  ", BACKGROUND}, 
        {" View    ", BACKGROUND},
    };
    
    std::unique_ptr<Menu> h_menu(new HorizontalMenu());
    h_menu->setPosition(Coordinate(-10,0));
    h_menu->setOptionItems(items);
    h_menu->setTheme(Theme(BACKGROUND, FOREGROUND));
    h_menu->setInputEvent(InputKeyEvent(LEFT, RIGHT));  
    
   while(true){
    
       while(!h_menu->isItemSelected()){
           h_menu->render();
       }
        
       h_menu->setItemSelectionState(false);
       
       switch(h_menu->getItemPosition()){
           case 1:
               subMenu();
           break;
           
           case 2:
               std::cout << "2 selected";
           break;
           
           case 3:
                std::cout << "3 selected";
           break ;
           
            case 4:
                std::cout << "3 selected";
           break ;
       }
       
   }
}

void subMenu(){
    
    MenuItem optItems[] = {
        {" New      ", FOREGROUND},  
        {" Open     ", BACKGROUND},  
        {" Save     ", BACKGROUND}, 
        {" Save As  ", BACKGROUND},
    };
    
    std::unique_ptr<Menu> v_menu(new VerticalMenu());
    v_menu->setTheme(Theme(BACKGROUND, FOREGROUND));
    v_menu->setPosition(Coordinate(0,1));
    v_menu->setOptionItems(optItems);
    
    while(true){

        while(!v_menu->isItemSelected()){
            v_menu->render();
        }

        v_menu->setItemSelectionState(false);

        switch(v_menu->getItemPosition()){
            case 1:
                menu();
            break;

            case 2:
                menu();
            break;

            case 3:
                menu();
            break;

            case 4:
                menu();
            break;
        }
    }
}



// driver code
int main() {
    CursorState(1,false);
    menu();
    return 0;
}
