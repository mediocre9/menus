# menus
Menus is a DOS based graphics lib that is built on vain-engine library. It can be used to create simple GUI applications. It offers various GUI components from tear-down menus to window frames etc.

## Usage

```c++
    const int& BACKGROUND = Color.BRIGHT_WHITE_BLACK;
    const int& HIGHLIGHT = Color.BRIGHT_BLUE_BRIGHT_WHITE;
    
    // create an object pass vector initializer...
    std::unique_ptr<Menu> h_menu(new HorizontalMenu({
            {" File ", HIGHLIGHT},
            {" Edit ", BACKGROUND},
            {" View ", BACKGROUND},
            {" Help ", BACKGROUND},
        }, 
        Coordinate(-2, 6)
    ));
    
    // initialize theme data....
    h_menu->setTheme(Theme(BACKGROUND, HOVER));
    
    // inifinite loop to handle the input events.... 
    while(true){
        
        // if an item is not selected, then keep rendering the object
        // because an [ENTER] input key will always be in a waiting state
        // for an event generation.
        // And if any input event occurs, then the internal loop
        // will break and will return the index...
        while(!h_menu->isItemSelected()){
            h_menu->render();
        }
        
        h_menu->setItemSelectionState(false);
        
        switch(h_menu->getItemPosition()){
            case 1:
                // event call from here...
            break;
            
            case 2:
                // event call from here...
            break;
            
            case 3:
                // event call from here...
            break;
        }
    }
```




