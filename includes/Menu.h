/**
* 
* @file Menu.h  
* @brief A GUI component library, built on top of the vain-engine library.
*
* @author Mediocre
* @date 20th/July/2022
*/

#if __cplusplus < 201103L
    #error This project can only be compiled with a compiler that supports c++11 or above.
#else 
#ifndef MENU_H
#define MENU_H


#include <string>
#include "AbstractTypes.h"
#include "..\lib\includes\vain_engine.h"

#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>


/*
* Defining ASCII-Based Graphics 
* Texture Values...
*/

#define NONE                          0
#define SCROLL_BAR                    219


/*
* Single border texture values.
*/
#define SINGLE_BOTTOM_RIGHT_EDGE      217
#define SINGLE_TOP_LEFT_EDGE          218
#define SINGLE_TOP_RIGHT_EDGE         191
#define SINGLE_BOTTOM_LEFT_EDGE       192
#define SINGLE_VERTICAL_STROKE        179
#define SINGLE_HORIZONTAL_STROKE      196


/*
* Double border texture values.
*/
#define DOUBLE_TOP_LEFT_EDGE          201
#define DOUBLE_BOTTOM_LEFT_EDGE       200
#define DOUBLE_TOP_RIGHT_EDGE         187
#define DOUBLE_BOTTOM_RIGHT_EDGE      188
#define DOUBLE_VERTICAL_STROKE        186
#define DOUBLE_HORIZONTAL_STROKE      205



/*
* A wrapper over winapi
* window control system
*/
struct WinApi {
    static void videoMode(const std::string& title, const Dimension& dimension, Color color = eng::Color.BLACK_BLACK) {
        SetConsoleTitle(title.c_str());
        HWND consoleWindow = GetConsoleWindow();
        RECT rect = {100, 100, dimension.width_, dimension.length_} ;
        MoveWindow(consoleWindow, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);
        
        DWORD style = GetWindowLong(consoleWindow, GWL_STYLE);
        style &= ~WS_MAXIMIZEBOX;
        SetWindowLong(consoleWindow, GWL_STYLE, style);
        SetWindowPos(consoleWindow, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);

        // for disabling resizable window.... 
        SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

        // for removing side scroll bar... 
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(handle, &info);
        COORD new_size ;
        new_size.X = info.srWindow.Right - info.srWindow.Left + 1;
        new_size.Y = info.srWindow.Bottom - info.srWindow.Top + 1;
        SetConsoleScreenBufferSize(handle, new_size);

        // direct passing of color param
        // to system() call...
        std::string windowColorCmd = "color ";
        std::ostringstream stream;
        stream << std::hex << color;
        std::string convertedHexVal = stream.str();
        
        windowColorCmd
            .append({convertedHexVal[0]})
            .append({convertedHexVal[1]})
            .append(" & cls");
    
            system(windowColorCmd.c_str()); 
        eng::CursorState(10,false);
        eng::SetPosition(-1, -1);
    }
};


/*
* /////////////////////////////////////
* 
* [MenuItem] is an ADT class
* to construct menu options.
* And this class only serves
* purpose to populate vectors for 
* rendering the menu option items.
* 
* /////////////////////////////////////
*/
class MenuItem {
public:

    MenuItem() 
    : data_("Not defined!")
    , color_(eng::Color.BLACK_WHITE) {}


    MenuItem(const std::string& data, const Color& color) 
    : data_(data), color_(color) {
        ++count_;
    }


    MenuItem& setData(const std::string& data) {
        data_ = data;
        return *this;
    }


    MenuItem& setColor(const Color& color) {
        color_ = color;
        return *this;
    }


    const std::string& getData() {
        return data_;
    }

    const Color& getColor() {
        return color_;
    }

    static int getCount() {
        return count_;
    }

    static int count_;

private:
    std::string data_;
    Color color_;
};
int MenuItem::count_ = 0;



/*
* //////////////////////////////////////////////////
*
* [Entity] is an abstract and the heart of
* of all classes to construct the concrete widget 
* classes. And many other future implmentations
* of widgets will be inheriting from this
* Entity class.
* 
* /////////////////////////////////////////////////
*/
template <class T_Entity>
class Entity {
public:
    Entity() {
        coordinate_.x_ = 0; 
        coordinate_.y_ = 0; 
        color_ = eng::Color.BLACK_WHITE;
    }
    
    T_Entity& setPosition(const Coordinate& coordinate) {
        coordinate_ = coordinate;
        return static_cast<T_Entity&>(*this);
    }
    
    T_Entity& setColor(const Color& color) {
        color_ = color;
        return static_cast<T_Entity&>(*this);
    } 
    
    const Color& getColor() {
        return color_;
    }
    
    const Coordinate& getCoordinate() {
        return coordinate_;
    }

    int getPositionX() const {
        return coordinate_.x_;
    }

    int getPositionY() const {
        return coordinate_.y_;
    }
    
    virtual void render() = 0;

private:
    Color color_;
    Coordinate coordinate_;
};




/*
* //////////////////////////////////////////////////////
*
* Menu is an abstract and core implementation to render
* menus from handling the graphics data to input events. 
*
* //////////////////////////////////////////////////////
*/
class Menu : public Entity<Menu> {
public:

    Menu() 
    : itemIndex_(0)
    , isItemSelected_(false)
    , isScrollActive_(false) {
        
        key_.key_one_ = UP;
        key_.key_two_ = DOWN; 
        
        theme_.background_  =  eng::Color.WHITE_BLACK;
        theme_.highlight_   =  eng::Color.BLUE_WHITE;
    }


    Menu(const std::vector<MenuItem>& items, const InputKey& key, const Coordinate& coordinate) 
    : Menu() {
        addItems(items);
        setInputKeys(key);
        setPosition(coordinate);
    }


    void addItems(const std::vector<MenuItem>& items) {
        items_ = items;
    }


    void addItem(const MenuItem& item) {
        items_.push_back(item);
    }


    const MenuItem& getMenuItemAt(int index) const {
        return items_.at(index);
    }
    
    
   void dropAllMenuItems() {
        items_.clear();
    }


    Menu& setInputKeys(const InputKey& key) {
        key_ = key;
        return *this;
    }
    

    Menu& setTheme(const Theme& theme) {
        theme_ = theme;
        return *this;
    }


    void restart()  {
        isItemSelected_ = false;
    }


    Menu& enableScroll(bool active) {
        isScrollActive_ = active;
        return *this;
    }


    bool isScrollActive() {
        return isScrollActive_;
    }


    bool isItemSelected() {
        return isItemSelected_;
    }
    
    
    bool isItemNotSelected() {
        return !isItemSelected_;
    }


    const Theme& getThemeObject() {
        return theme_;
    }


    // index starts from 1
    int getItemPosition() {
        return itemIndex_ + 1;
    }


    bool popLastItem() {
        if (!items_.empty()) {
            items_.pop_back();
            return true;
        }
        return false;
    }



protected:
	
    // Handling Input events
    void awaitSelectionInputEvent() {
        int vectorSize = items_.size();
        
        // waiting for input event
        inputKey_ = getch();


        // For UP / LEFT keys
        if (inputKey_ == key_.key_one_) {
            itemIndex_--;
            if (itemIndex_ < 0) {
                itemIndex_ = vectorSize - 1;
            }
        }


        // For DOWN / RIGHT keys
        if (inputKey_ == key_.key_two_) {
            ++itemIndex_;
            if (itemIndex_ >= vectorSize) {
                itemIndex_ *= 0;
            }
        }
    }


    void reInitVectorItemColors() {
        for (MenuItem& vecItem : items_) {
            vecItem.setColor(theme_.background_);
        }
    }


    void awaitEnterInputEvent() {
        const char ENTER = '\r';
        
        if (itemIndex_ >= 0) {
            
            MenuItem item = items_.at(itemIndex_);
            item.setColor(theme_.highlight_);
            
            if (inputKey_ == ENTER) {
                isItemSelected_ = true;
            }
        }
    }
    
    
    bool isVectorOfItemsEmpty() {
        return items_.empty();
    }
    
    std::vector<MenuItem>& getVectorOfMenuItems() {
        return items_;
    }
    
    
private:
    char inputKey_;
    int itemIndex_; 
    bool isItemSelected_;
    bool isScrollActive_;
    InputKey key_;
    Theme theme_;
    std::vector<MenuItem> items_; 
};




/*
* //////////////////////////////////////////////////////
*
* HorizontalMenu is a concrete specialized class to render
* menus horizontally on x-plane.
*
* //////////////////////////////////////////////////////
*/
class HorizontalMenu : public Menu {

public:
    HorizontalMenu() : Menu() {}

    HorizontalMenu(const std::vector<MenuItem>& items, const Coordinate& coordinate)
        : Menu(items, InputKey(UP, DOWN), Coordinate(coordinate)) {}

    void render() override {
        int posY = getPositionY();

        try {
            if (!isVectorOfItemsEmpty()) {
                
                for (auto& i : getVectorOfMenuItems()) {
                    
                    eng::Paint(i.getColor());
                    eng::SetPosition(getCoordinate().x_, posY++);

                    char texture = (isScrollActive()) ? SCROLL_BAR : NONE;
                    std::cout << texture << i.getData() ;
                }
                
            } else {
                throw "\nVector container is empty. Initialize MenuItem objects.";
            }
        } catch (const char* e) {
            std::cerr << e;
            exit(0);
        }
        
        awaitSelectionInputEvent();
        reInitVectorItemColors();
        awaitEnterInputEvent();
    }
};




/*
* //////////////////////////////////////////////////////
*
* VerticalMenu is a concrete specialized class to render
* menus vertically on y-plane.
*
* //////////////////////////////////////////////////////
*/
class VerticalMenu : public Menu {

public:
    VerticalMenu() : Menu() {}
    
    VerticalMenu(const std::vector<MenuItem>& items, const Coordinate& coordinate)
        : Menu(items, InputKey(LEFT, RIGHT), Coordinate(coordinate)) {}

    void render() override {
        int itemWidth = getMenuItemWidthSize();
        int posX = getPositionX();

        try {
            if (!isVectorOfItemsEmpty()) {
                
                for (auto& i : getVectorOfMenuItems()) {
                    
                    eng::Paint(i.getColor());
                    eng::SetPosition(posX += itemWidth, getCoordinate().y_);

                    char texture = (isScrollActive()) ? SCROLL_BAR : NONE;
                    std::cout << texture << i.getData();
                }
                
            } else {
                throw "\nVector container is empty. Initialize MenuItem objects.";
            }
        } catch (const char* e) {
            std::cerr << e;
            exit(0);
        }

       awaitSelectionInputEvent();
       reInitVectorItemColors();
       awaitEnterInputEvent();
    }


private:
    
    // returns [MenuItem] string width size to 
    // increment the positional coordinates on x-plane...
    //
    // EXAMPLE: " Option " Item class object....
    //
    // The above item width is 6 char long without whitespaces.
    // We are calculating the item width 
    // to position the next item on x-axis to avoid 
    // the overlapping of multiple rendered objects....
    // InshAllah i'll try to implement [MenuItem] string padding 
    // to equalize the object placement....
    int getMenuItemWidthSize() {
        MenuItem& item = getVectorOfMenuItems().at(0);
        return item.getData().length() + 1;
    }
};




class Window : public Entity<Window> {
public:
    
    enum Border{
        PIPE,
        LINE,
    };
    
    
    Window() : Entity() {
        shadow_ = false;
        border_ = LINE;
        dimension_.length_ = 10;
        dimension_.width_ = 10;
        setColor(eng::Color.WHITE_BLACK);
    }
    
    
    Window& setDimension(const Dimension& dimension) {
        dimension_ = dimension;
        return static_cast<Window&>(*this);
    }
    
    
    
    Window& enableShadow(const bool& active) {
        shadow_ = active;
        return static_cast<Window&>(*this);
    }
    
    
    Window& setBorderType(const Window::Border& border) {
        border_ = border;
        return static_cast<Window&>(*this);
    }
    
    
    Dimension& getDimension() {
        return dimension_;
    }
    
    
    const Border& getBorderType() {
        return border_;
    }
    
    
    bool isShadowEnabled() {
        return shadow_;
    }  
    
    
private:
    bool shadow_;
    Border border_;
    Dimension dimension_;
};


class Frame : public Window {
public:
    Frame() : Window() {}
    
    Frame(const Dimension& dimension, const Coordinate& coordinate) 
    : Window() {
        setPosition(coordinate);
        setDimension(dimension);
    }
    
    void render() override {

        if (isShadowEnabled()) {

            // lib vain-engine Box api call....
            backFrameBox_ = eng::Box (
                                    getDimension().length_,
                                    getDimension().width_,
                                    getCoordinate().x_ + 3,
                                    getCoordinate().y_,
                                    eng::Texture.SOLID,
                                    eng::Texture.SOLID,
                                    eng::Color.BLACK_BLACK
                                );

            // Note: Render() method is an API call from
            // vain-engine library and render() method is a
            // method from Entity class.
            // Both are different in terms of their
            // usage.
            backFrameBox_.Render();
        }

        switch(getBorderType()){
            case PIPE:
                pipeBorderFrame();
            break;
            
            case LINE:
                lineBorderFrame();
            break;
        }
    }

private:
    
    void lineBorderFrame() {        
        int tempY = getCoordinate().y_;
        
        for (int i = 0 ; i < getDimension().length_ ; i++) {
            
            eng::SetPosition(getCoordinate().x_, tempY + i);
            eng::Paint(getColor());
            
            if (i == 0)
                std::cout << (char)SINGLE_TOP_LEFT_EDGE;
            
            else if (i == getDimension().length_ - 1)
                std::cout << (char)SINGLE_BOTTOM_LEFT_EDGE;
            
            else
                std::cout << (char)SINGLE_VERTICAL_STROKE;
            
        
            for (int j = 0 ; j < getDimension().width_ ; j++) {
            
                if ((j >= 0 && j <= getDimension().width_ - 2) && (i == 0 || i == getDimension().length_ - 1))
                    std::cout << (char)SINGLE_HORIZONTAL_STROKE;
            
                else if (j == getDimension().width_ - 1 && i == 0)
                    std::cout << (char)SINGLE_TOP_RIGHT_EDGE;
                
                else if (j == getDimension().width_ - 1 && i == getDimension().length_ - 1 )
                    std::cout << (char)SINGLE_BOTTOM_RIGHT_EDGE;
                
                else if (j == getDimension().width_ - 1)
                    std::cout << (char)SINGLE_VERTICAL_STROKE;
                    
                else if (j <= getDimension().width_ - 1){
                    eng::Paint(getColor());
                    std::cout << " ";
                }
            }
            std::cout << "\n";
        }
    }
    
    
    void pipeBorderFrame() {
        int tempY = getCoordinate().y_;
        
        for (int i = 0 ; i < getDimension().length_ ; i++) {
            
            eng::SetPosition(getCoordinate().x_, tempY + i);
            eng::Paint(getColor());
            
            if (i == 0)
                std::cout << (char)DOUBLE_TOP_LEFT_EDGE;
                
            else if (i == getDimension().length_ - 1) 
                std::cout << (char)DOUBLE_BOTTOM_LEFT_EDGE;
            
            else 
                std::cout << (char)DOUBLE_VERTICAL_STROKE;
            
        
            for (int j = 0 ; j < getDimension().width_ ; j++) {
            
                if ((j >= 0 && j <= getDimension().width_ - 2) && (i == 0 || i == getDimension().length_ - 1))
                    std::cout << (char)DOUBLE_HORIZONTAL_STROKE;
            
                else if (j == getDimension().width_ - 1 && i == 0)
                    std::cout << (char)DOUBLE_TOP_RIGHT_EDGE;
                
                else if (j == getDimension().width_ - 1 && i == getDimension().length_- 1)
                    std::cout << (char)DOUBLE_BOTTOM_RIGHT_EDGE;
                
                else if (j == getDimension().width_ - 1)
                    std::cout << (char)DOUBLE_VERTICAL_STROKE;
                    
                else if (j <= getDimension().width_ - 1) {
                    eng::Paint(getColor());
                    std::cout << " ";
                }
            }
            std::cout << "\n";
        }
    }

private:
    eng::Box frontFrameBox_;
    eng::Box backFrameBox_;
};


class Text : public Entity<Text> {
public:
    
    enum TextStyle {
        NORMAL,
        SINGLE,
        DOUBLE,
        DOTTED,
    };
    
    Text() : Entity() {
        setPosition(Coordinate(0, 0));
        style_ = Text::NORMAL;
        setColor(eng::Color.BLACK_WHITE);
    }
    
    Text(const std::string& text, Coordinate coord, TextStyle style = Text::NORMAL, Color color = eng::Color.WHITE_BLACK) 
    : Entity() {
        setText(text);
        setPosition(coord);
        setColor(color);
        setStyle(style);
        render();
    }

    
    Text& setStyle(TextStyle style) {
        style_ = style;
        return *this;
    }
        
    Text& setText(const std::string& text) {
        this->text_ = text;
        return *this;
    }
    
    std::string& getText()  {
        return text_;
    }
    
    void render() override {
        eng::Paint(getColor());
        eng::SetPosition(getCoordinate().x_, getCoordinate().y_);
        
        switch(style_) {
            case Text::NORMAL:
            std::cout << text_;
            break;
            
            case Text::SINGLE:{
                std::cout << getText();
                eng::SetPosition(getCoordinate().x_, getCoordinate().y_ + 1);
                for (auto& i : getText()) {
                    std::cout << char(196);
                }
                break;
            }
            
            case Text::DOUBLE: {
                std::cout << getText();
                eng::SetPosition(getCoordinate().x_, getCoordinate().y_ + 1);
                for (auto& i : getText()) {
                    std::cout << char(205);
                }
                break;
            }
            
            case Text::DOTTED: {
                std::cout << getText();
                eng::SetPosition(getCoordinate().x_, getCoordinate().y_ + 1);
                for (auto& i : getText()) {
                    std::cout << char(249);
                }
                break;
            }
        }
    }
    
private:
    std::string text_;
    TextStyle style_;
};
#endif
#endif
