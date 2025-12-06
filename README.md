# ConsoleFPS

First commit:

I would like to preface this README by saying that this project drove me CRAZY to the point that i was gonna cry and pull out my hair.

ALL BECAUSE:

fPlayerX = 0.0f // UM HELLO?
fPlayerY = 8.0f

and i was losing my mind because APPARENTLY I WAS STUCK IN THE WALL and i was wondering why i couldnt move. 

but i fixed it as follows

fPlayerX = 8.0f // phew im not stuck in the wall anymore
fPlayerY = 8.0f

SECONDLY, i tried a few things to fix the error in 
>cannot convert 'wchar_t*' to 'LPCSTR' {aka 'const char*'}

i tried a few fixes including 
1. #define UNICODE
2. using the -municode flag during compilation which needed me to change main() to wmain(), i reverted this back to main() later and still compile without that flag
3. i just put the windows header at the top and even though the goddamn red squiggle shows up it compiles FINE, this is what i use to compile it to a .exe
    > g++ source.cpp -o source.exe

    then i just click on the exe file in the explorer

*I ALSO HAD A PROBLEM WITH THE EXE OPENING IN THE CMD INSTEAD OF THE CONSOLE,*
this was a pretty easy fix though, i had to change settings for running command line apps :/

SO before i commit this, i need to say that this has been quite frustrating so far but we good.

i will attach a screenrecording of what we have so far below:

https://github.com/user-attachments/assets/a6dc1f5b-4a49-4b6e-9f88-7ca7a41b55f5

_i'm spinning like a ballerinaaaaa_

