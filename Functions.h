#ifndef FUNCTIONS_H
#define FUNCTIONS_H



// this function sets the console cursor (used by printf and cout) at the given coordinates
void SetCursor(SHORT xCursor = 0, SHORT yCursor = 0)
{
    static HANDLE
        consoleOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(consoleOutputHandle, {xCursor, yCursor});
}

// this function reads the file from the directory parameter, which is supposed to contain the console buffer width and height
std::vector<int> ReadBufferSizeFromFile(const char *directory)
{
    std::ifstream
        fileReader;

    std::vector<int>
        bufferSize;

    // resizing the vector to 2 elements, so that bufferSize[0] is the width, and bufferSize[1] is the height
    bufferSize.resize(2);

    fileReader.open(directory);

    if (!fileReader.is_open())
    {
        // using the default assumed values, if the file can't be read from
        bufferSize[0] = Default::bufferWidth;
        bufferSize[1] = Default::bufferHeight;
    }
    else
    {
        // fileLine reads all lines inside the file, one by one
        std::string
            fileLine,
            fileLineFirstHalf,
            fileLineSecondHalf;

        char
            _fileLine[256];

        while (fileReader.getline(_fileLine, 256))
        {
            fileLine = _fileLine;

            // fileLineFirstHalf will receive all characters from the beginning of the line, and until the '=' character is found (which is a separator in this case)
            // fileLineSecondHalf will receive all characters from just after the '=' character, and until the end of the line
            fileLineFirstHalf  = fileLine.substr(0, fileLine.find('='));
            fileLineSecondHalf = fileLine.substr(fileLine.find('=') + 1);

            if (fileLineFirstHalf.find("bufferWidth") != std::string::npos)
            {
                bufferSize[0] = std::stoi(fileLineSecondHalf);
            }

            if (fileLineFirstHalf.find("bufferHeight") != std::string::npos)
            {
                bufferSize[1] = std::stoi(fileLineSecondHalf);
            }
        }

        fileReader.close();
    }

    return bufferSize;
}

// this function makes use of windows functions to directly check the buffer size of the console
std::vector<int> ReadBufferSizeFromWindow()
{
    PCONSOLE_SCREEN_BUFFER_INFO
        consoleBufferInfo = new CONSOLE_SCREEN_BUFFER_INFO;

    std::vector<int>
        bufferSize;

    BOOL
        result = GetConsoleScreenBufferInfo(Default::consoleOutputHandle,
                                            consoleBufferInfo);

    if (!result)
    {
        return ReadBufferSizeFromFile("data.txt");
    }

    bufferSize.push_back(consoleBufferInfo->dwSize.X);
    bufferSize.push_back(consoleBufferInfo->srWindow.Bottom - consoleBufferInfo->srWindow.Top);

    delete consoleBufferInfo;

    std::cout << bufferSize[0] << ", "
              << bufferSize[1];

    return bufferSize;
}



#endif // FUNCTIONS_H
