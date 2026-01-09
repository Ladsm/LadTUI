# The Menu Class

## Info

### The menu class is a simple and easy menu that uses the arrow keys

## How to call and Use

To use it, create a string array.

``` cpp
std::string items[5] = { "One", "Two", "Three", "Four" , "Five"};
```

Then make a object with data type Menu, in this case; menu

``` cpp
ladtui::Menu menu;
```

Then, make a list of functions. It needs to be the same langth as the string array.
It can have diffrent return values, in this case void.
The name of the list of functions can be anything but in this case MenuTest.

``` cpp
std::vector<std::function<void()>> MenuTest = {
[]() { std::cout << "Selected 1\n"; },
[]() { std::cout << "Selected 2\n"; },
[]() { std::cout << "Selected 3\n"; },
[]() { std::cout << "Selected 4\n"; },
[]() { std::cout << "Selected 5\n"; }
};
```

After all this, call menu.MenuMenu. The peramiters are : Sting array, list of functions, langth of the string array and type  
There are two types of menus; 1, adds an arrow to the side of the item thats picked. 2 highlights items in white and 3 is a mix of the two.

```cpp
menu.MenuMenu(items, MenuTest, 5, 1);
```

This is how the menu looks:

```cpp
->One
   Two
   Three
   Four
   Five
```
