# LadTUI

## Info

### What is LadTUI?

Ladtui is a simple and **lightwaight framework** aimed at **small-medium** projects for Windows.

### Why should I use LadTUI?

Ladtui was made mainly for small projects who dont need large frameworks or dont want to write boilerplate and just want to get on with it.

## How to set up

For now, there are no precompiled binarys for Ladtui. Please clone the git repository and compile it in MSVC.  
Take LadTUI lib.lib and LadTUI.h and place it in a directory.  
Go to Project -> {projectname} Properties -> C/C++ -> General -> Additional Include Directories and set it to the directory where the LadTUI lib.lib and LadTUI.h files are.  
Then Linker -> General -> Additional Library Directories and specify the path, where LadTUI lib.lib file is located.  
Finally, go to Linker -> Input -> Additional Dependencies and add LadTUI lib.lib.  
After all that, in files where you want to use Ladtui ; "#include "LadTUI.h"".
