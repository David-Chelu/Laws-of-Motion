#define _WIN32_WINNT 0x0500

// these two macros are used for the PlotRectangle function, to make it more explicit for the programmer
#define ERASE false
#define DRAW  true

// defining a namespace to keep default values & other, to avoid having them in the global scope
namespace Default
{
    // these values assume the console is on a 1920x1080 monitor, windows 8, with Raster Fonts, 8x8 font size, with 238x126 console buffer and window sizes.
    // The number 125 is chosen instead of 126, because that leaves a trailing line for the cursor to rest, without the image being scrolled down.
    // By default, these values are 80 and 25, respectively, and can be changed in the layout tab in the console properties.
    int
        bufferWidth  = 238,
        bufferHeight = 125,

        // the "decay" of velocity, if you will
        // the amount by which, after the object stops accelerating, it will decelerate on its own
        naturalAcceleration = 1,

        // program in this variable to only accelerate and decelerate after this amount of ms / frames
        // ticksPerAcceleration

        //the absolute value of the acceleration the object will have while moving
        verticalAccelerationValue = 1,
        horizontalAccelerationValue = 1;
}

// directions used for acceleration
#define MOVE_NONE 0
#define MOVE_UP   (-Default::verticalAccelerationValue)
#define MOVE_DOWN  (Default::verticalAccelerationValue)
#define MOVE_LEFT (-Default::horizontalAccelerationValue)
#define MOVE_RIGHT (Default::horizontalAccelerationValue)

#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <string.h>

#include "Classes.h"



int main()
{
    // a timer to determine whether the frame should be updated
    time_t
        startTime = clock();

    // the number of milliseconds to wait between frame updates and vector updates
    // 1000ms / 33ms = 30ups
    int
        frameDuration = 33;

    class Rectangle
        targetRectangle;

    // telling the object to load values from the file "data.txt", and, if the file cannot be read, the default values will be used instead
    ConsoleDisplay
        targetConsole(ReadBufferSizeFromFile("data.txt"));

    targetRectangle.maximumVelocity()[0] = 4;
    targetRectangle.maximumVelocity()[1] = 3;

    bool
        updated = true;

    while (1)
    {
        // checks whether the escape key is pressed, to end the program
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }

        //checking for user input, to determine the movement
        if (GetAsyncKeyState(VK_UP))
        {
            targetRectangle.acceleration()[1] = MOVE_UP;
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
            targetRectangle.acceleration()[1] = MOVE_DOWN;
        }
        else
        {
            targetRectangle.acceleration()[1] = MOVE_NONE;
        }

        if (GetAsyncKeyState(VK_LEFT))
        {
            targetRectangle.acceleration()[0] = MOVE_LEFT;
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            targetRectangle.acceleration()[0] = MOVE_RIGHT;
        }
        else
        {
            targetRectangle.acceleration()[0] = MOVE_NONE;
        }

        /*
        the updates will take place as follows:
        -vector updates will take place every frameDuration milliseconds, so as to not accidentally have absurd position and/or velocity the moment the user starts pressing an arrow key
        -frame updates will take place every frameDuration milliseconds, and only when the UpdateVectors method returns true (which implies a change in position)

        To avoid unnecessarily updating vectors, the keystroke will be checked against the current timer. If frameDuration milliseconds passed, the UpdateVectors method will be called.
        Within the same if statement, there'll be an if statement that checks the result of the update, to draw the image as well.
        */

        if (clock() - startTime >= frameDuration)
        {
            if (updated)
            {
                // function call to draw the rectangle on the string, ready to be displayed in the console
                PlotRectangle(targetConsole,
                              targetRectangle);

                // resets the console cursor at 0 (default arguments are (0, 0)).
                // this method of replacing the old output with new output, is faster than clearing the console for every frame (and avoids the flickers that clearing the console may cause)
                SetCursor();
                std::cout<<targetConsole.characterArray();

                // function call to erase the rectangle from the string, where it stands, so that no rectangle remnants stay in the image next time around
                PlotRectangle(targetConsole,
                              targetRectangle,
                              ERASE);

                startTime = clock();

                // the cursor rests on the 126th line, as all previous lines are filled.
                std::cout << "position: "
                          << targetRectangle.position()[0] << ", "
                          << targetRectangle.position()[1] << "; "
                          << "velocity: "
                          << targetRectangle.velocity()[0] << ", "
                          << targetRectangle.velocity()[1] << "; "
                          << "acceleration: "
                          << targetRectangle.acceleration()[0] << ", "
                          << targetRectangle.acceleration()[1] << "; ";
            }

            // this method will automatically update the position & velocity, according to the object's relation to the console borders
            updated = targetRectangle.UpdateVectors(0, 0, Default::bufferWidth, Default::bufferHeight);
        }

        // 1 ms wait between each iteration, so as to barely use processor power, but still have a high frame rate.
        Sleep(1);
    }



    getch();

    return 0;
}
