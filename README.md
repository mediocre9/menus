# menus
Menus is a DOS based graphics lib that is built on vain-engine library. It can be used to create simple GUI applications. It offers various GUI components from tear-down menus to window frames etc.

## Usage

```c++
    // create an object pass vector initializer...
    std::unique_ptr<Menu> h_menu(new HorizontalMenu({
            {" File ", HOVER},
            {" Edit ", BACKGROUND},
            {" View ", BACKGROUND},
            {" Help ", BACKGROUND},
        }, 
        Coordinate(-2, 6)
    ));
    
    h_menu->setTheme(Theme(BACKGROUND, HOVER));

    while(true){
        
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




