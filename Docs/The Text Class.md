# The Text Class

## Info

### Text to display to the screen

## How to call and Use

to use it, create a object with data type Text, in this case text.

```cpp
ladtui::Text text;
```

set text's variables with the text constructer.
The only value you have to set is the string text;

```cpp
text = ladtui::Text("text");
```

After all this, call one of Text's functions, heres a list:

### out/outboxed(string textToPrintOut)

prints the passed string.
If outboxed is used it will print the text in a box like this:

```sh
╔═══════╗
║Example║
╚═══════╝
```

### GetString()

Wraper for std::getline, that returns a string. Example on how to use it:

```cpp
ladtui::Text text = (text.GetString());
```