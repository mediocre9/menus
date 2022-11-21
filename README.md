# Menus
Menus is a DOS-inspired graphics class that is built upon the vain-engine library. It can be used to build basic DOS-based GUI applications that offer a variety of GUI elements, such as window frames and tear-down menus.


## #Getting Started
Add the `libVain Engine.a` library to the linker and copy the `Vain-Engine.dll` file from the lib folder to the main directory where you'll be running the program.
Use the namespace `eng` for the 'Vain-Engine' library functions.

### Note: 
**_Run `build.sh` file to build the project, if dev-c++ is not installed on your machine._**

## Usage

```c++
    const int DEFAULT = Color.BRIGHT_WHITE_BLACK;
    const int HIGHLIGHT = Color.BRIGHT_BLUE_BRIGHT_WHITE;
    
    // pass vector initializer list...
    std::unique_ptr<Menu> h_menu(new HorizontalMenu({
            {" File ", HIGHLIGHT},
            {" Edit ", DEFAULT},
            {" View ", DEFAULT},
            {" Help ", DEFAULT},
        }, 
        Coordinate(0, -1)
    ));
    
    // initialize theme data....
    h_menu->setTheme(Theme(DEFAULT, HIGHLIGHT));
    
    // infinite loop to handle the input events.... 
    while(true){
        
        // If an item is not selected, then keep rendering the object
        // because an [ENTER] input key will always be in a waiting state 
        // for an event generation.
        // And if any input event occurs, then the internal loop
        // will break and return the index...
        while(!h_menu->isItemSelected()){
            h_menu->render();
        }
        
        h_menu->restart();
        
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
            {" New   ", HIGHLIGHT},
            {" Open  ", DEFAULT},
            {" Save  ", DEFAULT},
            {" Print ", DEFAULT},
        }, 
        Coordinate(0, 0)
    ));
    
    v_menu->setTheme(Theme(DEFAULT, HIGHLIGHT));

```
![](previews/menus_demo.gif?raw=true "")

**Window frame class.**
```c++
    std::unique_ptr<Window> frame(new Frame(Dimension(10,30), 
        Coordinate(3,5))
    );
        
    frame->setShadow(true);
    frame->render();
```

![](previews/frame.png?raw=true "")



