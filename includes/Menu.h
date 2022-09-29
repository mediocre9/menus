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


    MenuItem(const std::string& data, const int& color) : data_(data), color_(color) {
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
        color_ = Color.BLACK_WHITE;
    }
    
    void setPosition(Coordinate coord){
        coord_ = coord;
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

    Menu() : itemIndex_(0), isItemSelected_(false), isScrollActive_(false) {
        key_.key_one_ = UP;
        key_.key_two_ = DOWN;
        theme_.background_ = Color.WHITE_BLACK;
        theme_.marker_ = Color.BLUE_WHITE;
    }

    Menu(const std::vector<MenuItem>& items, const InputKeyEvent& key, const Coordinate& coord) 
    : Menu() {
        setItems(items);
        setInputEvent(key);
        setPosition(coord);
    }


    void setItems(const std::vector<MenuItem>& items) {
        menuItem_ = items;
    }


    void setItem(const MenuItem& item){
        menuItem_.push_back(item);
    }

    MenuItem getOptionItem(int index){
        return menuItem_.at(index);
    }
    
   void clearItemContainer(){
        menuItem_.clear();
    }

    void setInputEvent(const InputKeyEvent key) {
        key_.key_one_ = key.key_one_;
        key_.key_two_ = key.key_two_;
    }
    

    void setTheme(const Theme theme){
        theme_.background_ = theme.background_;
        theme_.marker_ = theme.marker_;
    }


    void setItemSelectionState(bool itemSelected) {
        isItemSelected_ = itemSelected;
    }


    void scroll(bool active) {
        isScrollActive_ = active;
    }


    bool isScrollActive() {
        return isScrollActive_;
    }


    bool isItemSelected() {
        return isItemSelected_;
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
        isItemSelected_ = false;
        menuItem_.clear();
    }


    virtual void render() {}

protected:
    
    // Input Key is the worst mechanism
    // that i have created...
    // uneccessary setInputEvent() method....
    // VIOLATION of single resposibility rule....
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
                isItemSelected_ = true;
            }
        }
    }

protected:
    char inputKey_;
    int itemIndex_; 
    bool isItemSelected_, isScrollActive_;
    InputKeyEvent key_;
    Theme theme_;
    std::vector<MenuItem> menuItem_; 
};




// specialized menu class ....
class VerticalMenu : public Menu {

public:
    VerticalMenu() : Menu() {}

    VerticalMenu(const std::vector<MenuItem>& items, const Coordinate coord)
        : Menu(items, InputKeyEvent(UP, DOWN), Coordinate(coord)) {}

    // places menu items in a vertical way....
    void render() override {
        const int SCROLL_TEXTURE_VALUE = 219;
        const int SCROLL_NONE = 0;
        
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
    
    HorizontalMenu(const std::vector<MenuItem>& items, const Coordinate coord)
        : Menu(items, InputKeyEvent(LEFT, RIGHT), Coordinate(coord)) {}

    // places menu items in a horizontal way....
    void render() override {
        const int SCROLL_TEXTURE_VALUE = 219;
        const int SCROLL_NONE = 0;
        
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
    // returns [MenuItem] string width size to 
    // increment the positional coordinate on x-plane...
    //
    // EXAMPLE: " Option " Item class object....
    //
    // The above item width is 6 char long without whitespaces.
    // We are calculating the item width 
    // to position the next item on x-axis to avoid 
    // the overlapping of multiple rendered objects....
    // InshAllah i'll try to implement [MenuItem] string padding 
    // to equalize the object placement....
    int getOptionItemWidthSize() {
        return (menuItem_.at(0)).getData().length() + 1;
    }
};





/*
*  ugly code ahead... 
*/
class Window : public Entity{
public:
    enum Border{
        NONE,
        PIPE,
        LINE,
    };
    
    Window() : Entity() {
        dimension_.length_ = 10;
        dimension_.width_ = 10;
        setColor(Color.WHITE_BLACK);
    }
    
    void setDimension(Dimension dim){
        dimension_.length_ = dim.length_;
        dimension_.width_ = dim.width_;
    }
    
    Dimension getDimension(){
        return dimension_;
    }
    
    virtual void shadow(bool active) {}
    virtual bool isShadowEnabled() {}
    
    virtual void setBorderType(Border border) {}
    virtual bool isBorderEnabled() {}
    
private:
    Dimension dimension_;
};


class Frame : public Window{
public:
    Frame() : Window() {
        shadow_ = false;
    }
    
    Frame(Dimension dim, Coordinate coord, Border border, int color) : Window() {
        setPosition(coord);
        setDimension(dim);
        setBorderType(border);
        setColor(color);
    }
    
    void shadow(bool active){
        shadow_ = active;
    }
    
    void setBorderType(Border border) {
        border_ = border;
    }
    
    bool isShadowEnabled() {
        return shadow_;
    }  
    
    void render() override{

        if (isShadowEnabled()) {
            // Box method from vain engine api call...
            Box backFrameBox = Box (
                                    getDimension().length_,
                                    getDimension().width_,
                                    getCoordinate().x_ + 3,
                                    getCoordinate().y_,
                                    Texture.SOLID,
                                    Texture.SOLID,
                                    Color.BLACK_BLACK
                                );
            backFrameBox.Render();
        }

        switch(border_){
            case NONE:
                noneBorderFrameRender();
            break;
            
            case PIPE:
                pipeBorderFrame();
            break;
            
            case LINE:
                lineBorderFrame();
            break;
        }
    }

private:
    void noneBorderFrameRender(){
        Box frontFrameBox = Box (
                        getDimension().length_,
                        getDimension().width_,
                        getCoordinate().x_,
                        getCoordinate().y_,
                        Texture.SOLID,
                        Texture.SOLID,
                        getColor()
                     );
        frontFrameBox.Render();
    }
    
    
    void lineBorderFrame(){
        const int TOP_LEFT_LINE = 218;
        const int BOTTOM_LEFT_LINE = 192;
    
        const int TOP_RIGHT_LINE = 191;
        const int BOTTOM_RIGHT_LINE = 217;
    
        const int HORIZONTAL_LINE = 196;
        const int VERTICAL_LINE = 179;
        
        int tempY = getCoordinate().y_;
        
        for (int i = 0 ; i < getDimension().length_ ; i++){
            SetPosition(getCoordinate().x_, tempY + i);
            Paint(getColor());
            if (i == 0){
                std::cout << (char)TOP_LEFT_LINE;
            } 
            else if (i == getDimension().length_ - 1){
                std::cout << (char)BOTTOM_LEFT_LINE;
            }else{
                std::cout << (char)VERTICAL_LINE;
            }
        
            for (int j = 0 ; j < getDimension().width_ ; j++){
            
                if ((j >= 0 && j <= getDimension().width_ - 2) && (i == 0 || i == getDimension().length_ - 1))
                    std::cout << (char)HORIZONTAL_LINE;
            
                else if (j == getDimension().width_ - 1 && i == 0)
                    std::cout << (char)TOP_RIGHT_LINE;
                
                else if (j == getDimension().width_ - 1 && i == getDimension().length_ - 1 )
                    std::cout << (char)BOTTOM_RIGHT_LINE;
                
                else if (j == getDimension().width_ - 1)
                    std::cout << (char)VERTICAL_LINE;
                else if (j <= getDimension().width_ - 1){
                    Paint(getColor());
                    std::cout << " ";
                }
            }
            std::cout << "\n";
        }
    }
    
    void pipeBorderFrame(){
        const int TOP_LEFT_PIPE = 201;
        const int BOTTOM_LEFT_PIPE = 200;
    
        const int TOP_RIGHT_PIPE = 187;
        const int BOTTOM_RIGHT_PIPE = 188;
    
        const int HORIZONTAL_PIPE = 205;
        const int VERTICAL_PIPE = 186;
        
        int tempY = getCoordinate().y_;
        
        for (int i = 0 ; i < getDimension().length_ ; i++){
            SetPosition(getCoordinate().x_, tempY + i);
            Paint(getColor());
            if (i == 0){
                std::cout << (char)TOP_LEFT_PIPE;
            } 
            else if (i == getDimension().length_ - 1){
                std::cout << (char)BOTTOM_LEFT_PIPE;
            }else{
                std::cout << (char)VERTICAL_PIPE;
            }
        
            for (int j = 0 ; j < getDimension().width_ ; j++){
            
                if ((j >= 0 && j <= getDimension().width_ - 2) && (i == 0 || i == getDimension().length_ - 1))
                    std::cout << (char)HORIZONTAL_PIPE;
            
                else if (j == getDimension().width_ - 1 && i == 0)
                    std::cout << (char)TOP_RIGHT_PIPE;
                
                else if (j == getDimension().width_ - 1 && i == getDimension().length_- 1)
                    std::cout << (char)BOTTOM_RIGHT_PIPE;
                
                else if (j == getDimension().width_ - 1)
                    std::cout << (char)VERTICAL_PIPE;
                else if (j <= getDimension().width_ - 1){
                    Paint(getColor());
                    std::cout << " ";
                }
            }
            std::cout << "\n";
        }
    }

private:
    Box frontFrameBox;
    Box backFrameBox;
    bool shadow_;
    Border border_;
};
#endif
