#ifndef CONSOLE_DISPLAY_H
#define CONSOLE_DISPLAY_H



// a class that handles the console output, acting like an image to be displayed on the terminal (using characters instead of individual pixels)
class ConsoleDisplay
{
public:
    // to simplify code, the constructor will be the only time the object takes buffer values, and allocates the display string
    ConsoleDisplay(const std::vector<int> &bufferSize);
    ~ConsoleDisplay();

    // operators used to mark string addresses to be assigned new values
    ConsoleDisplay
        &operator ()(unsigned int line),
        &operator [](unsigned int column);

    // after the () and [] operators are used to mark the address, the assign operator will straight away assign the given value at the marked address
    void
        operator =(char character);

    // getter access methods for string addresses
    const char
        *characterArray() const,
        *currentLine() const;

    // getter access methods for string properties
    const int
        bufferWidth() const,
        bufferHeight() const,
        characterCapacity() const;

    // getter access method for string address marker
    const unsigned int
        currentColumn() const;

private:
    // string addresses
    char
        *_characterArray,
        *_currentLine;

    // string properties
    int
        _bufferWidth,
        _bufferHeight;

    // string address marker
    unsigned int
        _currentColumn;
};



ConsoleDisplay::ConsoleDisplay(const std::vector<int> &bufferSize)
{
    // using a variable as handle, to avoid unnecessarily repeatedly calculating variable multiplication
    int
        arraySize;

    // the console buffer values are taken from the vector parameter, where its first element is the width, and the second element is the height
    this->_bufferWidth  = bufferSize[0];
    this->_bufferHeight = bufferSize[1];

    // allocating the string to be displayed, while simultaneously assigning its size to the purposed variable
    this->_characterArray = new char[(arraySize = this->_bufferWidth * this->_bufferHeight) + 1];

    // parsing the whole string and assigning it the ' ' character (which will result in a blank image)
    for (int index = 0; index < arraySize; index++)
    {
        this->_characterArray[index] = 32;
    }

    // and, of course, the null terminator character
    this->_characterArray[arraySize] = 0;
}

ConsoleDisplay::~ConsoleDisplay()
{
    delete []this->_characterArray;
}



// in a sequentially allocated array, which is imagined to be a rectangle of bufferWidth characters wide and bufferHeight characters tall, to access the imagined nth line, n must be multiplied by the width, and the resulting number is the start of the nth line.
// this operator only marks the address at which the nth line starts.
// returning a reference to the object itself, will assure that further methods and operators can be called right after this operator call.
ConsoleDisplay &ConsoleDisplay::operator ()(unsigned line)
{
    this->_currentLine = this->_characterArray + line * this->_bufferWidth;

    return *this;
}

// combined with the line marker operator, this column marker operator will help pinpoint the exact index to be assigned a value to, when using the assign operator on the object itself.
ConsoleDisplay &ConsoleDisplay::operator [](unsigned column)
{
    this->_currentColumn = column;

    return *this;
}

// finally, using the line and column marker operators, will make way for the assign operator to finally assign a character value, in the intended location within the string
void ConsoleDisplay::operator =(char character)
{
    this->_currentLine[this->_currentColumn] = character;
}



const char *ConsoleDisplay::characterArray() const
{
    return this->_characterArray;
}

const char *ConsoleDisplay::currentLine() const
{
    return this->_currentLine;
}

const int ConsoleDisplay::bufferWidth() const
{
    return this->_bufferWidth;
}

const int ConsoleDisplay::bufferHeight() const
{
    return this->_bufferHeight;
}

// this method returns the size of the string, and was mostly intended for debugging purposes.
const int ConsoleDisplay::characterCapacity() const
{
    return this->_bufferWidth *
           this->_bufferHeight +
           1;
}

const unsigned int ConsoleDisplay::currentColumn() const
{
    return this->_currentColumn;
}



#endif // CONSOLE_DISPLAY_H
