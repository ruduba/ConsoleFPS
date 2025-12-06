#include <windows.h>
#include <iostream>
using namespace std;
#define _UNICODE

#include <cmath>

int nScreenWidth = 120;
int nScreenHeight = 40;

float fPlayerX = 8.0f; // x coord
float fPlayerY = 8.0f; // y coord
float fPlayerA = 0.0f; // angle

int nMapHeight = 16;
int nMapWidth = 16;
float fFOV = 3.1415/4;
float fDepth = 16.0f;

int main()
{
// Create Screen buffer
wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight];
HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
SetConsoleActiveScreenBuffer(hConsole);
DWORD dwBytesWritten =0;

wstring map;
map += L"################"; // top wall
map += L"#..............#"; // open space with side walls
map += L"#..............#";
map += L"#..............#";
map += L"#..............#";
map += L"#..............#";
map += L"#..............#";
map += L"#..............#";
map += L"#..............#";
map += L"#..............#";
map += L"#..............#";
map += L"#..............#";
map += L"#..............#";
map += L"#..............#";
map += L"#..............#";
map += L"################"; // bottom wall

//game loop
while(1){

    //controls
    //handle CCW Rotation
    if(GetAsyncKeyState((unsigned short)'A')& 0x8000)
        fPlayerA -= (0.1f);

    if(GetAsyncKeyState((unsigned short)'D')& 0x8000)
        fPlayerA += (0.1f);




    for(int x=0; x<nScreenWidth; x++){

        // calculate the projected angle into world space for each column
        float fRayAngle = (fPlayerA - fFOV/2.0f) + ((float)x/(float)nScreenWidth)*fFOV;

        float fDistanceToWall = 0.0f;
        bool bHitWall = false;

        float fEyeX = sinf(fRayAngle);
        float fEyeY = cosf(fRayAngle);

        while(!bHitWall && fDistanceToWall < fDepth){
            fDistanceToWall += 0.1f;

            int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
            int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);

            //test if ray is out of bounds
            if(nTestX <0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight){
                bHitWall = true; // set dist to max depth
                fDistanceToWall = fDepth;
            }else{
                //ray is inbounds so test if the ray cell is a wall block
                if(map[nTestY * nMapWidth + nTestX] == '#'){
                    bHitWall = true;
                }
            }

        }
        //Calculate distance to ceiling and floor
			int nCeiling = (float)(nScreenHeight/2.0) - (float)nScreenHeight / ((float)fDistanceToWall);
            int nFloor = nScreenHeight - nCeiling;
            if(nCeiling < 0) nCeiling = 0;
            if(nFloor >= nScreenHeight) nFloor = nScreenHeight - 1;

        for(int y = 0; y< nScreenHeight; y++)
            if(y <= nCeiling)
                screen[y*nScreenWidth + x] = ' ';
            else if(y > nCeiling && y <= nFloor)
                screen[y*nScreenWidth + x] = '#';
            else
                screen[y*nScreenWidth + x] = ' ';
    }
screen[nScreenWidth * nScreenHeight - 1] = '\0';
WriteConsoleOutputCharacterW(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);

}
return 0;
}
