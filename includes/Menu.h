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

#include <iostream>
#include <vector>
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
    , color_(0x00CF) {}


    MenuItem(const std::string& data, const int& color) 
    : data_(data), color_(color) {
        ++count_;
    }


    void setData(const std::string& data) {
        data_ = data;
    }


    void setColor(const int& color) {
        color_ = color;
    }


    const std::string& getData() {
        return data_;
    }


    int getColor() {
        return color_;
    }

    static int getCount() {
        return count_;
    }
    
    ~MenuItem() {
        count_ *= 0;
    }

    static int count_;

private:
    std::string data_;
    int color_;
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
class Entity {
public:
    Entity() {
        coordinate_.x_ = 0; 
        coordinate_.y_ = 0; 
        color_ = eng::Color.BLACK_WHITE;
    }
    
    void setPosition(const Coordinate& coordinate) {
        coordinate_ = coordinate;
    }
    
    void setColor(const int& color) {
        color_ = color;
    } 
    
    int getColor() {
        return color_;
    }
    
    const Coordinate& getCoordinate() {
        return coordinate_;
    }
    
    virtual void render() = 0;

private:
    int color_;
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
class Menu : public Entity {
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
        setItems(items);
        setInputEvent(key);
        setPosition(coordinate);
    }


    void setItems(const std::vector<MenuItem>& items) {
        items_ = items;
    }


    void setItem(const MenuItem& item) {
        items_.push_back(item);
    }


    const MenuItem& getOptionItem(int index) const {
        return items_.at(index);
    }
    
    
   void clearItemContainer() {
        items_.clear();
    }


    void setInputEvent(const InputKey& key) {
        key_ = key;
    }
    

    void setTheme(const Theme& theme) {
        theme_ = theme;
    }


    void restart()  {
        isItemSelected_ = false;
    }


    void setScroll(bool active) {
        isScrollActive_ = active;
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


    const Theme& getTheme() {
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


    ~Menu() {
        itemIndex_ = 0;
        isItemSelected_ = false;
        items_.clear();
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
            
            (items_.at(itemIndex_)).setColor(theme_.highlight_);
            
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
* VerticalMenu is a concrete specialized class to render
* menus vertically on x-plane.
*
* //////////////////////////////////////////////////////
*/
class VerticalMenu : public Menu {

public:
    VerticalMenu() : Menu() {}

    VerticalMenu(const std::vector<MenuItem>& items, const Coordinate& coordinate)
        : Menu(items, InputKey(UP, DOWN), Coordinate(coordinate)) {}

    void render() override {
        int posY = getCoordinate().y_;

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
* HorizontalMenu is a concrete specialized class to render
* menus horizontally on y-plane.
*
* //////////////////////////////////////////////////////
*/
class HorizontalMenu : public Menu {

public:
    HorizontalMenu() : Menu() {}
    
    HorizontalMenu(const std::vector<MenuItem>& items, const Coordinate& coordinate)
        : Menu(items, InputKey(LEFT, RIGHT), Coordinate(coordinate)) {}

    void render() override {
        int itemWidth = getMenuItemWidthSize();
        int posX = getCoordinate().x_;

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
    // increment the positional coordinateinate on x-plane...
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




class Window : public Entity {
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
    
    
    void setDimension(const Dimension& dimension) {
        dimension_ = dimension;
    }
    
    
    const Dimension& getDimension() {
        return dimension_;
    }
    
    
    void setShadow(const bool& active) {
        shadow_ = active;
    }
    
    
    void setBorderType(const Window::Border& border) {
        border_ = border;
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


class Frame : public Window{
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

            // lib vain-engine API Render() method.
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
#endif
#endif
