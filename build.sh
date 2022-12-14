# change app name here...
APP_NAME="Menus"
CURRENT_PATH=$(pwd)
LIB_PATH="$CURRENT_PATH/lib"


if test -f *.o; then
    echo "Removing old obj files . . ."
    rm -r *.o
fi

# building project here
echo "Compiling $APP_NAME ! "
g++ -c *.cpp -std=c++11

echo "Linking $APP_NAME ! "
g++ -s *.o -L"$LIB_PATH" -"lVain Engine" -o "$APP_NAME"

echo "Launching $APP_NAME . . .  "
start "$APP_NAME".exe

echo "exiting . . ."
sleep 1


