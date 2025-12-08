# ConsoleFPS
This is a project diary

***COMMIT #1***

I would like to preface this README by saying that this project has driven me CRAZY to the point that i was gonna cry and pull out my hair.

ALL BECAUSE:
```
 fPlayerX = 0.0f // UM HELLO?
 fPlayerY = 8.0f
```

and i was losing my mind because APPARENTLY I WAS STUCK IN THE WALL and i was wondering why i couldnt move. 

but i fixed it as follows

```
fPlayerX = 8.0f // phew im not stuck in the wall anymore
fPlayerY = 8.0f
```

SECONDLY, i tried a few things to fix the error in 
```cannot convert 'wchar_t*' to 'LPCSTR' {aka 'const char*'}```

i tried a few fixes including 
1. adding the ```#define UNICODE```
2. using the ```-municode``` flag during compilation which needed me to change ```main()``` to ```wmain()```, i reverted this back to ```main()``` later and still compile without that flag
3. i just put the windows header at the top and even though the goddamn red squiggle shows up it compiles FINE, this is what i use to compile it to an .exe
    ``` g++ source.cpp -o source.exe```

    then i just click on the exe file in the explorer

*I ALSO HAD A PROBLEM WITH THE EXE OPENING IN THE CMD INSTEAD OF THE CONSOLE,*
this was a pretty easy fix though, i had to change settings for running command line apps :/

SO before i commit this, i need to say that this has been quite frustrating so far but we good.

i will attach a screenrecording of what we have so far below:

https://github.com/user-attachments/assets/a6dc1f5b-4a49-4b6e-9f88-7ca7a41b55f5

_i'm spinning like a ballerinaaaaa_
_________________________________________________________________________________________________
***COMMIT 2***

Well hello there, we have quite a bit to unload today. Let's look at it progression-wise

1. Updated walls to shade brighter/darker based on distance from player, used unicode for this, pretty easy to do

https://github.com/user-attachments/assets/88bc6f9a-2d76-491b-9742-0d02ac496890

2. Added W and S key functionalities (for forward and backward movements respectively), made turning faster. This makes it easier to explore and understand the shading on the walls, although it is still quite confusing out of context

https://github.com/user-attachments/assets/60a152f6-e793-470a-b376-3a5d0718a34d

3. Added a few obstacles on the map (additional walls) just to see how it would feel to navigate through

https://github.com/user-attachments/assets/b2196817-7cc2-4a7e-8d0e-31915302d8e9

here is the map at the time of this recording
```
map += L"################"; // top wall
map += L"#..............#"; // open space with side walls
map += L"#..............#";
map += L"#..............#";
map += L"#..............#";
map += L"#####.....#....#";
map += L"#..............#";
map += L"#..............#";
map += L"#.......#......#";
map += L"#.......#......#";
map += L"#.......#......#";
map += L"#.......#......#";
map += L"#......#####...#";

map += L"#..............#";
map += L"#..............#";
map += L"################"; // bottom wall
```

3. I added shading to the floor to make perspective easier to recognize, again calculated on basis of distance from wall

https://github.com/user-attachments/assets/3149c766-1325-4de3-9d56-3bcca066002a

4. THe walls just seemed solid without any difference between a straight wall and a corner, so added boundary shading (it was shaded with an 'I' at the time of the recording, now it is changed to ' ' i.e., a space)

https://github.com/user-attachments/assets/d6d383c8-ca53-48d7-9201-141f7412726f


5. THE NEXT UPDATE WAS QUITE PAINFUL.

  i had written strafe mechanics as:

  ```
  // strafe right
  if(GetAsyncKeyState((unsigned short) 'D') & 0x8000){
        fPlayerX -= sinf(fPlayerA-90.0f) *5.0f * fElapsedTime;
        fPlayerY -= cosf(fPlayerA-90.0f) *5.0f * fElapsedTime;
        if(map[(int)fPlayerY*nMapWidth + (int)fPlayerX] == '#'){
        fPlayerX += sinf(fPlayerA-90.0f) *5.0f * fElapsedTime;
        fPlayerY += cosf(fPlayerA-90.0f) *5.0f * fElapsedTime;
        }
    }
    // strafe left
    if(GetAsyncKeyState((unsigned short) 'A') & 0x8000){
        fPlayerX += sinf(fPlayerA-90.0f) *5.0f * fElapsedTime;
        fPlayerY += cosf(fPlayerA-90.0f) *5.0f * fElapsedTime;
        if(map[(int)fPlayerY*nMapWidth + (int)fPlayerX] == '#'){
            fPlayerX -= sinf(fPlayerA-90.0f) *5.0f * fElapsedTime;
            fPlayerY -= cosf(fPlayerA-90.0f) *5.0f * fElapsedTime;
        }
    }
```

which basically boils down to:

```
X, Y -= (sin(A-90), cos(A-90) //strafe right
X, Y += (sin(A+90), cos(+-90) //strafe left
```
WHICH IS WRONG.

i needed to be to swapping the sin and cos, not changing the Angle inside.

so when i was strafing, i was either clipping out, or moving diagonally instead of left ot right. AS A SEASONED VALORANT PLAYER, this annoyed me because strafing is a very important gaming mechanic (very close to my heart).

after a lot of head-breaking, i looked at the equations i had found for strafing on stack overflow for a long time, and finally figured out that this is what i had to do:

```
X, Y += (cos(A), -sin(A)) // strafe right
X, Y += (-cos(A), sin(A)) // strafe left
```

so i changed it to that, and updated collsion detection***, and we were good to go!

THEN, 

I added a map on the top-left of the screen, which was just taking the map and replicating it on the top-left of the screen buffer. and i added stats too, -> player position(x, y, a), FPS 

i noticed that the angle was in radians and not degrees, so i fixed that, and this was the final result:

https://github.com/user-attachments/assets/a660739f-71f6-4098-a392-53579c1a73e3

It is not the most perfect fps, but i'm proud of it.


***Fun Fact:

Today i discovered that collision detection in games is just, negating your motion. WHICH IS SOOOO GENIUS. 

so basically if i were to run into a wall moving forward, the way to keep me from clipping out is to just push me back at the same rate i am pushing forward (netwon's third law, same thing that happens to you when you push against a wall)

CRAZY!

i might update this soon with more stuff.

but this is it for commit 2
