#include "includes\Menu.h"
#include <memory>

const int DEFAULT = Color.WHITE_BLACK;
const int HIGHLIGHT = Color.BRIGHT_BLUE_BRIGHT_WHITE;

void tearDownMenu();

int main(){
    CursorState(10,false);
    system("title Menus (demo) & mode 40,10 & cls & color 87");
    
    // window frame....
    std::unique_ptr<Window> frame(new Frame(Dimension(5,27), 
        Coordinate(5,3), 
        Window::PIPE, 
        Color.WHITE_BLACK)
    );
    frame->setShadow(true);
    frame->render();

    
    std::unique_ptr<Menu> h_menu(new HorizontalMenu({
            {"  File   ", HIGHLIGHT},
            {"  Edit   ", DEFAULT},
            {"  View   ", DEFAULT},
            {"  Help   ", DEFAULT},
        }, 
        Coordinate(-10, 0)
    ));
    
    h_menu->setTheme(Theme(DEFAULT, HIGHLIGHT));

    while(true){
        
        while(!h_menu->isItemSelected()){
            h_menu->render();
        }
        
        h_menu->setItemSelectionState(false);
        
        switch(h_menu->getItemPosition()){
            case 1:
                tearDownMenu();
            break;
            
            case 2:
            	 /* Do stuff from here */
            break;
            
            case 3:
            	 /* Do stuff from here */
            break;
            
            case 4:
            	 /* Do stuff from here */
            break;
        }
        
    }
    return 0;
}


// vertical menus........
void tearDownMenu(){
    std::unique_ptr<Menu> v_menu(new VerticalMenu({
            {" New   ", HIGHLIGHT},
            {" Open  ", 0x00F0},
            {" Save  ", 0x00F0},
            {" Close ", 0x00F0},
        }, 
        Coordinate(0, 1)
    ));
    
    v_menu->setTheme(Theme(0x00F0, HIGHLIGHT));

    
    while(true){
        
        while(!v_menu->isItemSelected()){
            v_menu->render();
        }
        
        v_menu->setItemSelectionState(false);
        
        switch(v_menu->getItemPosition()){
            case 1:
                
            break;
            
            case 2:
            	 /* Do stuff from here */
            break;
            
            case 3:
            	 /* Do stuff from here */
            break;
            
            case 4:
            	main();
            break;
        }
    }
}
