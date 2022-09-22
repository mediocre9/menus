# Menus
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
                /* Do stuff from here */
            break;
            
            case 2:
                /* Do stuff from here */
            break;
            
            case 3:
                /* Do stuff from here */
            break;
        }
    }
```
![](previews/menu.png?raw=true "")

**Same procedure for vertical (drop-down) menus.**
```c++
    std::unique_ptr<Menu> v_menu(new VerticalMenu({
            {" New   ", HOVER},
            {" Open  ", 0x0070},
            {" Save  ", 0x0070},
            {" Print ", 0x0070},
        }, 
        Coordinate(5, 3)
    ));
    
    v_menu->setTheme(Theme(0x0070, HOVER));
```
![](previews/menus_demo.gif?raw=true "")

**Window frame class.**
```c++
    std::unique_ptr<Window> frame(new Frame(Dimension(10,30), 
        Coordinate(3,5), 
        Window::LINE, 
        Color.WHITE_BLACK)
    );
        
    frame->shadow(true);
    frame->render();
```

![](previews/frame.png?raw=true "")



