#include "includes\Menu.h"
#include <memory>

const Color DEFAULT   = eng::Color.BRIGHT_WHITE_BLACK;
const Color HIGHLIGHT = eng::Color.BRIGHT_RED_BRIGHT_WHITE;

void tearDownMenu();
void subTearDownMenu();
void createNewWindow();

int main() {
    WinApi::videoMode("Demo", Dimension(700, 934), eng::Color.BLUE_BLACK);

    // window frame....
    Frame(Dimension(20,48), Coordinate(5,4))
	.setBorderType(Window::LINE)
	.enableShadow(true)
	.render();
	


    // Text widget . . . 
    Text("I am a normal text", Coordinate(16,9), Text::NORMAL);
    Text("I am an underlined text", Coordinate(16,11), Text::SINGLE, eng::Color.WHITE_RED);
    Text("I am a double underlined text", Coordinate(16,13), Text::DOUBLE, eng::Color.WHITE_BLUE);
    Text("I am a dotted underlined text", Coordinate(16,15), Text::DOTTED, eng::Color.WHITE_GREEN);
    

    // Menus . . .
    std::unique_ptr<Menu> h_menu(new VerticalMenu({
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


// horizontal menus........
void tearDownMenu() {
    std::unique_ptr<Menu> v_menu(new HorizontalMenu({
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
    std::unique_ptr<Menu> v_menu(new HorizontalMenu({
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
    Frame(Dimension(10,28), Coordinate(65,4))
	.setBorderType(Window::PIPE)
    .enableShadow(true)
    .render();

    Text("New Window", Coordinate(70, 5));
}
