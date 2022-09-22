# menus
Menus is a DOS based graphics lib that is built on vain-engine library. It can be used to create simple GUI applications. It offers various GUI components from tear-down menus to window frames etc.

## Usage

```c++
    std::unique_ptr<Menu> h_menu(new HorizontalMenu({
            {" File ", HOVER},
            {" Edit ", BACKGROUND},
            {" View ", BACKGROUND},
            {" Help ", BACKGROUND},
        }, 
        Coordinate(4, 6)
    ));
```

