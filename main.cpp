#include "includes\Menu.h"
#include <memory>
#include <thread>

const int DEFAULT   = eng::Color.BRIGHT_WHITE_BLACK;
const int HIGHLIGHT = eng::Color.BRIGHT_BLUE_BRIGHT_WHITE;

void tearDownMenu();
void subTearDownMenu();
void createNewWindow();

int main() {
    
    eng::CursorState(10,false);
    system("title Menus (demo) & mode 100,27 & cls & color 87");
    
    
    // window frame....
    std::unique_ptr<Window> frame(new Frame(Dimension(20,48), 
        Coordinate(5,4))
    );
    frame->setBorderType(Window::LINE);
    frame->setShadow(true);
    frame->render();


    // Text widget . . . 
    Text("I am a normal text", Coordinate(16,9), Text::NORMAL);
    Text("I am an underlined text", Coordinate(16,11), Text::SINGLE, eng::Color.WHITE_RED);
    Text("I am a double underlined text", Coordinate(16,13), Text::DOUBLE, eng::Color.WHITE_BLUE);
    Text("I am a dotted underlined text", Coordinate(16,15), Text::DOTTED, eng::Color.WHITE_GREEN);
    

    // Menus . . .
    std::unique_ptr<Menu> h_menu(new HorizontalMenu({
            {"  New    ", HIGHLIGHT},
            {"  File   ", DEFAULT},
            {"  Edit   ", DEFAULT},
            {"  View   ", DEFAULT},
            {"  Find   ", DEFAULT},
            {"  Tools  ", DEFAULT},
            {"  Goto   ", DEFAULT},
            {"  Search ", DEFAULT},
            {" Project ", DEFAULT},
            {"  Help   ", DEFAULT},
        }, 
        Coordinate(-10, 0)
    ));
    
    
    h_menu->setTheme(Theme(DEFAULT, HIGHLIGHT));


    for(;;) {
        
        while(h_menu->isItemNotSelected()){
            h_menu->render();
        }
        
        h_menu->restart();
        
        switch(h_menu->getItemPosition()) {
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
void tearDownMenu() {
    std::unique_ptr<Menu> v_menu(new VerticalMenu({
            {"  New      ", HIGHLIGHT},
            {"  Open     ", DEFAULT},
            {"  Save     ", DEFAULT},
            {"  Print    ", DEFAULT},
            {"  Window > ", DEFAULT},
            {"  Close    ", DEFAULT},
        }, 
        Coordinate(0, 1)
    ));
    
    v_menu->setTheme(Theme(DEFAULT, HIGHLIGHT));

    
    while(true){
        
        while(v_menu->isItemNotSelected()){
            v_menu->render();
        }
        
        v_menu->restart();
        
        switch(v_menu->getItemPosition()){
            case 1:
                /* Do stuff from here */
            break;
            
            case 2:
                /* Do stuff from here */
            break;
            
            case 3:
                /* Do stuff from here */
            break;
            
            case 5:
                subTearDownMenu();
            break;
            
            case 6:
                main();
            break;
        }
    }
}


void subTearDownMenu() {
    std::unique_ptr<Menu> v_menu(new VerticalMenu({
            {"  Window ", HIGHLIGHT},
            {"  Time   ", DEFAULT},
            {"  Insert ", DEFAULT},
            {"  Header ", DEFAULT},
            {"  Close  ", DEFAULT},
        }, 
        Coordinate(11, 5)
    ));
    
    v_menu->setTheme(Theme(DEFAULT, HIGHLIGHT));
    
    for(;;) {
        
        while(v_menu->isItemNotSelected()){
            v_menu->render();
        }
        
        v_menu->restart();
        
        switch(v_menu->getItemPosition()){
            case 1:
                createNewWindow();
            
            
            case 2:
                /* Do stuff from here */
            break;
            
            case 3:
                /* Do stuff from here */
            break;
            
            case 5:
                main();
            break;
        }
    }
}


void createNewWindow() {
    std::unique_ptr<Window> frame(new Frame(Dimension(10,28), 
        Coordinate(65,4))
    );
    frame->setBorderType(Window::PIPE);
    frame->setShadow(true);
    frame->render();


    Text("New Window", Coordinate(70, 5));
}
