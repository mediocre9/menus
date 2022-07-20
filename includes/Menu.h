#ifndef MENU_H
#define MENU_H


#include <string>
#include "AbstractTypes.h"
#include "..\lib\includes\vain_engine.h"

#include <iostream>
#include <conio.h>
#include <vector>
using namespace eng;

// option item entity....
class MenuItem {
public:

    MenuItem() : data_("Not defined!"), color_(0) {}


    MenuItem(std::string data, int color) : data_(data), color_(color) {
        ++count_;
    }


    void setData(std::string data) {
        data_ = data;
    }


    void setColor(int color) {
        color_ = color;
    }


    std::string getData() {
        return data_;
    }


    int getColor() {
        return color_;
    }


    static int getCount() {
        return count_;
    }
    
    ~MenuItem(){
        count_ *= 0;
    }

    static int count_;

private:
    std::string data_;
    int color_;
};
int MenuItem::count_ = 0;







class Entity{
public:
    Entity() {
        coord_.x_ = 0; 
        coord_.y_ = 0; 
        color_ = Color.BRIGHT_BLUE_BRIGHT_WHITE;
    }
    
    void setPosition(Coordinate coord){
        coord_.x_ = coord.x_;
        coord_.y_ = coord.y_;
    }
    
    void setColor(int color){
        color_ = color;
    } 
    
    int getColor(){
        return color_;
    }
    
    Coordinate getCoordinate() {
        return coord_;
    }
    
    
    virtual void render() = 0;
private:
    int color_;
    Coordinate coord_;
};




// abstract Menu class...
class Menu : public Entity{
public:

    Menu() : itemIndex_(0), itemSelected_(false), active_(false) {
        key_.key_one_ = UP;
        key_.key_two_ = DOWN;
        theme_.background_ = Color.WHITE_BLACK;
        theme_.marker_ = Color.BLUE_WHITE;
    }


    void setOptionItems(const MenuItem items[]) {
        const int SIZE = items->getCount();
        for (int i = 0; i < SIZE ; i++) {
            menuItem_.push_back(items[i]);
        }
    }


    void setOptionItem(const MenuItem& item){
        menuItem_.push_back(item);
    }

    MenuItem getOptionItem(){
        return menuItem_.at(0);
    }
    
   void clearItemContainer(){
        menuItem_.clear();
    }

    void setInputEvent(InputKeyEvent key) {
        key_.key_one_ = key.key_one_;
        key_.key_two_ = key.key_two_;
    }
    

    void setTheme(Theme theme){
        theme_.background_ = theme.background_;
        theme_.marker_ = theme.marker_;
    }


    void setItemSelectionState(bool itemSelected) {
        itemSelected_ = itemSelected;
    }


    void setScroll(bool active) {
        active_ = active;
    }


    bool isScrollActive() {
        return active_;
    }


    bool isItemSelected() {
        return itemSelected_;
    }

    Theme getTheme() {
        return theme_;
    }

    // index starts from 1
    int getItemPosition() {
        return itemIndex_ + 1;
    }


    bool popLastItem() {
        if (!menuItem_.empty()) {
            menuItem_.pop_back();
            return true;
        }
        return false;
    }


    ~Menu() {
        itemIndex_ = 0;
        itemSelected_ = false;
        menuItem_.clear();
    }


    virtual void render() {}


protected:
    
    // Input Key is the worst mechanism
    // that i have created...
    // uneccessary setInputEvent() method....
    // and now this method.... they just dont follow the
    // single resposibility rule....
    // InputEvent class can be created to handle the input stuff...
    void waitForSelectionInputEvent() {
        inputKey_ = getch();

        // UP / LEFT key
        if (inputKey_ == key_.key_one_) {
            itemIndex_--;
            if (itemIndex_ < 0) {
                itemIndex_ = menuItem_.size() - 1;
            }
        }

        // DOWN / RIGHT
        if (inputKey_ == key_.key_two_) {
            ++itemIndex_;
            if (itemIndex_ >= menuItem_.size()) {
                itemIndex_ *= 0;
            }
        }
    }


    void reInitializeOptionItemColors() {
        int i = 0;
        while (i < menuItem_.size()) {
            (menuItem_.at(i)).setColor(getTheme().background_);
            i++;
        }
    }


    void waitForEnterInput() {
        const char ENTER = '\r';
        if (itemIndex_ >= 0) {
            (menuItem_.at(itemIndex_)).setColor(getTheme().marker_);
            if (inputKey_ == ENTER) {
                itemSelected_ = true;
            }
        }
    }

protected:
    char inputKey_;
    int itemIndex_; // possible memory leak operation due to raw pointers...
    bool itemSelected_, active_;
    InputKeyEvent key_;
    Theme theme_;
    std::vector<MenuItem> menuItem_; // certain memory leak and index out of bound bug ...
};




// specialized menu class ....
class VerticalMenu : public Menu {

public:
    VerticalMenu() : Menu() {}

    VerticalMenu(MenuItem items[], InputKeyEvent key, Coordinate coord)
        : Menu() {
        setOptionItems(items);
        setInputEvent(key);
        setPosition(coord);
    }


    // places menu items in a verical way....
    void render() override {
        const int& SCROLL_TEXTURE_VALUE = 219;
        const int& SCROLL_NONE = 0;
        
        int tempPosY = getCoordinate().y_;

        try {
            if (!menuItem_.empty()) {
                for (MenuItem& i : menuItem_) {
                    Paint(i.getColor());
                    SetPosition(getCoordinate().x_, tempPosY++);

                    char texture = (isScrollActive()) ? SCROLL_TEXTURE_VALUE : SCROLL_NONE;
                    std::cout << texture << i.getData() ;
                }
            } else {
                throw "\nVector container is empty. Initialize item objects.";
            }
        } catch (const char* e) {
            std::cerr << e;
            exit(0);
        }

        waitForSelectionInputEvent();
        reInitializeOptionItemColors();
        waitForEnterInput();
    }
};




// specialized horizontal menu class....
class HorizontalMenu : public Menu {

public:
    HorizontalMenu() : Menu() {}

    HorizontalMenu(MenuItem items[], InputKeyEvent key, Coordinate coord)
        : Menu() {
        setOptionItems(items);
        setInputEvent(key);
        setPosition(coord);
    }


    // places menu items in a horizontal way....
    void render() override {
        const int& SCROLL_TEXTURE_VALUE = 219;
        const int& SCROLL_NONE = 0;
        
        int itemWidth = getOptionItemWidthSize();
        int tempPosX = getCoordinate().x_;

        try {
            if (!menuItem_.empty()) {
                for (MenuItem& i : menuItem_) {
                    Paint(i.getColor());
                    SetPosition(tempPosX += itemWidth, getCoordinate().y_);

                    char texture = (isScrollActive()) ? SCROLL_TEXTURE_VALUE : SCROLL_NONE;
                    std::cout << texture << i.getData();
                }
            } else {
                throw "\nVector container is empty. Initialize item objects.";
            }
        } catch (const char* e) {
            std::cerr << e;
            std::cin.get();
            exit(0);
        }

        waitForSelectionInputEvent();
        reInitializeOptionItemColors();
        waitForEnterInput();
    }


private:
    // returns menu item width size to increment the positional
    // coordinate for x-axis...
    //
    // EXAMPLE: " Option " Item class object....
    // The above item width is 6 char long without whitespaces.
    // We calculate these item widths in order 
    // to position the next item in x-plane to avoid the
    // overlapping of multiple rendered items....
    int getOptionItemWidthSize() {
        return (menuItem_.at(0)).getData().length() + 1;
    }
};





class Window : public Entity{
public:
    Window() : Entity() {
        dimension_.length_ = 10;
        dimension_.width_ = 10;
    }
    
    void setDimension(Dimension dim){
        dimension_.length_ = dim.length_;
        dimension_.width_ = dim.width_;
    }
    
    Dimension getDimension(){
        return dimension_;
    }
    
    virtual void setShadow(bool active) {}
    virtual bool isShadowEnabled() {}
    
    virtual void setBorder(bool active) {}
    virtual bool isBorderEnabled() {}
    
private:
    Dimension dimension_;
};



class Frame : public Window{
public:
    Frame() : Window() {
        shadow_ = true;
        border_ = true;
    }
    
    Frame(Dimension dim, Coordinate coord) : Window() {
        setPosition(coord);
        setDimension(dim);
    }
    
    void setShadow(bool active){
        shadow_ = active;
    }
    
    void setBorder(bool active) {
        border_ = active;
    }
    
    bool isBorderEnabled() {
        return border_;
    }
    
    bool isShadowEnabled() {
        return shadow_;
    }
    
    void render() override {
        
        if (isShadowEnabled()) {
            Box backFrameBox = Box (
                                    getDimension().length_,
                                    getDimension().width_,
                                    getCoordinate().x_ + 2,
                                    getCoordinate().y_ + 1,
                                    Texture.SOLID,
                                    Texture.SOLID,
                                    Color.BLACK_BLACK
                                );
            backFrameBox.Render();
        }
        
        
        const int BORDER = (isBorderEnabled()) ? Texture.GRAIN : Texture.SOLID;
        
        Box frontFrameBox = Box (
                         getDimension().length_,
                         getDimension().width_,
                         getCoordinate().x_,
                         getCoordinate().y_,
                         BORDER,
                         Texture.SOLID,
                         getColor()
                     );
        frontFrameBox.Render();
    } 
    
private:
    Box frontFrameBox;
    Box backFrameBox;
    bool shadow_;
    bool border_;
};





class Label : public Entity{
public:
    virtual void setMessage(const std::string& message) {}
    virtual std::string getMessage () {}
};



class Text : public Label{
public:
    Text() {
        message_ = "nil";
    }
    
    Text(const std::string& message, Coordinate coord, int color){
        setPosition(coord);
        setColor(color);
        message_ = message;
        render();
    }
    
    void setMessage(const std::string& message){
        message_ = message;
    }
    
    std::string getMessage() {
        return message_;
    }
    
    void render(){
        SetPosition(getCoordinate().x_, getCoordinate().y_);
        Paint(getColor());
        std::cout << message_;
    }
    
private:
    std::string message_;
};
#endif
