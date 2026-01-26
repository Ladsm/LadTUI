# The consoleUtils Class

## Info

### The consoleUtils class is a group of usfull functions for the console

## How to call and Use

To use it, create an object with data type consoleUtils, in this case; tils.

```cpp
ladtui::consoleUtils tils;
```

Then, use one of its meny functions. Heres a list:  

### BackgroundDraw(int)

Makes a background for the console, paramaters are : int color.  
Heres a list of all the colors:  

Format is [background-color]-[text-color]  
- Black-White, 1
- White-Black, 2
- Blue Dark-White, 3
- Cyan-White, 4
- Yellow-Red / HOYTDAWG, 5
- Blue Bright-White, 6
- Pink-White, 7

### drawLineRight()

Draws a line horazontaly.

### CursorUp/CursorDown(int amountToGoUp/Down)

Moves the Cursor up or down.

### getConsoleHeight/width()

Returns an int of the size of the console window.  
It was mainly made for the libary itself so you wont use it that much.
