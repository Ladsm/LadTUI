# The Switch Class

## Info

### The switch class is an on and off switch that uses the arrow keys

## How to call and Use

To use it, create a object with data type Switch, not switch Switch. In this case: OnOff.

```cpp
ladtui::Switch OnOff
```

Then set Switches variables via the Switch constructer.
The values are: name of switch(the thing that will be displayed over the switch), a list of two functions(if you want more see The Menu Class) and if it should be on or off by default.

```cpp
ladtui::Switch(
"test",
[]() { std::cout << "Switch off\n" },
[]() { std::cout << "Switch on\n" },
1
);
```

After all this, call switchSwitch, the parameters are; Switch(usualy the switch you call from).

```cpp
OnOff.switchSwitch(OnOff);
```
