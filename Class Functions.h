#ifndef CLASS_FUNCTIONS_H
#define CLASS_FUNCTIONS_H



// this function plots the given rectangle onto the console, with 2 modes: DRAW and ERASE
// DRAW mode draws the 219 character (a filled rectangle), in all string indexes that are on the rectangle's surface.
// ERASE mode draws the 32 character (a space, or ' '), in all string locations that are on the rectangle's surface.
int PlotRectangle(ConsoleDisplay &targetConsole,
                  class Rectangle &targetRectangle,
                  bool mode = DRAW)
{
    // declaring variables to store the start and end points, in terms of string coordinates, where drawing can occur
    // to make sure drawing doesn't occur out of the string's scope, min and max are used to restrain the drawing limits to the console buffer
    // the combination makes sure that the values are at least 0, and at most the width/height of the buffer
    // these 2 points mark the region only around the rectangle, where characters could exist, to be checked (for increased performance)
    int
        xStart = std::min(std::max(targetRectangle.position()[0],                            0), targetConsole.bufferWidth()),
        xStop  = std::min(std::max(targetRectangle.position()[0] + targetRectangle.width(),  0), targetConsole.bufferWidth()),
        xParse,
        yStart = std::min(std::max(targetRectangle.position()[1],                            0), targetConsole.bufferHeight()),
        yStop  = std::min(std::max(targetRectangle.position()[1] + targetRectangle.height(), 0), targetConsole.bufferHeight()),
        yParse,
        // and a counter for the amount of characters drawn or erased
        drawnCharacters = 0;

    // parsing the string on height
    for (yParse = yStart; yParse < yStop; yParse++)
    {
        // using the operator, only once every loop iteration the address will be marked.
        // this reduces the number of executions for each string element.
        targetConsole(yParse);

        // parsing the string on width
        for (xParse = xStart; xParse < xStop; xParse++)
        {
            // using a ternary operator, the string elements are assigned either a filled rectangle or a space, depending on the mode
            targetConsole[xParse] = (mode == DRAW? 219 : 32);

            //if the point belongs to the rectangle, then it is counted
            drawnCharacters++;
        }
    }

    // returns the number of characters drawn
    return drawnCharacters;
}

// an overload for the printf function, with its only usage being less main code whenever a ConsoleDisplay object's image is to be displayed
int printf(ConsoleDisplay &targetConsole)
{
    return printf(targetConsole.characterArray());
}

// an operator overload, which returns the vector, but with all its elements opposite the original
std::vector<int> operator -(std::vector<int> targetVector)
{
    // parsing is done via vector iterators
    for (std::vector<int>::iterator address = targetVector.begin(); address != targetVector.end(); ++address)
    {
        (*address) = -(*address);
    }

    return targetVector;
}



#endif // CLASS_FUNCTIONS_H
