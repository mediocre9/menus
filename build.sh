rm -r *.o

# change app name here...
APP_NAME="Menus"
CURRENT_PATH=$(pwd)
LIB_PATH="$CURRENT_PATH/lib"


# building project here
g++ -c *.cpp -std=c++11
g++ -s *.o -L"$LIB_PATH" -"lVain Engine" -o "$APP_NAME"
start "$APP_NAME".exe
echo "exiting . . ."
sleep 2