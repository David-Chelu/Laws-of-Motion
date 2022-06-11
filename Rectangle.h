#ifndef RECTANGLE_H
#define RECTANGLE_H



// this class will be used to track and plot a rectangle at whichever coordinates it has set, in the console.
class Rectangle
{
public:
    Rectangle(int bufferWidth = Default::bufferWidth, int bufferHeight = Default::bufferHeight);

    // whenever this method is called, the rectangle's vectors are updated, to simulate motion (position vector, velocity vector, acceleration vector)
    bool
        UpdateVectors(int xMinimum, int yMinimum, int xMaximum, int yMaximum);

    void
        DisplayValues();

    std::vector<int>
        &position(),
        &velocity(),
        &maximumVelocity(),
        &acceleration();

    int
        &width(),
        &height();

private:
    std::vector<int>
        _position,
        _velocity,
        _maximumVelocity,
        _acceleration;

    int
        _width,
        _height;
};

Rectangle::Rectangle(int bufferWidth, int bufferHeight)
{
    // arbitrary size
    this->_width = 8;
    this->_height = 5;

    // the object is positioned in the center of the console
    this->_position.push_back((bufferWidth  - this->_width)  / 2);
    this->_position.push_back((bufferHeight - this->_height) / 2);

    // at first, the object is stationary
    this->_velocity.push_back(0);
    this->_velocity.push_back(0);

    this->_acceleration.push_back(0);
    this->_acceleration.push_back(0);

    this->_maximumVelocity.push_back(1);
    this->_maximumVelocity.push_back(1);
}

bool Rectangle::UpdateVectors(int xMinimum, int yMinimum, int xMaximum, int yMaximum)
{
    static int
        initialX,
        initialY,
        compoundAcceleration;

    initialX = this->_position[0],
    initialY = this->_position[1];



    // first, handling the horizontal (x) vectors
    this->_position[0] = std::min(std::max(this->_position[0] + this->_velocity[0], xMinimum), xMaximum - this->_width);

    // if acceleration is 0, then natural decay will occur
    if (this->_acceleration[0] == 0)
    {
        if (this->_velocity[0] < 0)
        {
            this->_velocity[0] = std::min(this->_velocity[0] + Default::naturalAcceleration, 0);
        }
        if (this->_velocity[0] > 0)
        {
            this->_velocity[0] = std::max(this->_velocity[0] - Default::naturalAcceleration, 0);
        }
    }
    // if acceleration is not 0, then standard acceleration applies
    else
    {
        // if both the velocity and acceleration are in the same direction, there's no decay from changing direction
        if (this->_velocity[0] * this->_acceleration[0] >= 0)
        {
            compoundAcceleration = this->_acceleration[0];
        }
        // on the other hand, if the two vectors are opposing, then the natural decay will contribute to the object's acted acceleration
        else
        {
            compoundAcceleration = this->_acceleration[0] + (this->_acceleration[0] < 0? -Default::naturalAcceleration : Default::naturalAcceleration);
        }

        this->_velocity[0] = std::min(std::max(this->_velocity[0] + compoundAcceleration, -this->_maximumVelocity[0]), this->_maximumVelocity[0]);
    }



    // handling the vertical (y) vectors
    this->_position[1] = std::min(std::max(this->_position[1] + this->_velocity[1], yMinimum), yMaximum - this->_height);

    // if acceleration is 0, then natural decay will occur
    if (this->_acceleration[1] == 0)
    {
        if (this->_velocity[1] < 0)
        {
            this->_velocity[1] = std::min(this->_velocity[1] + Default::naturalAcceleration, 0);
        }
        if (this->_velocity[1] > 0)
        {
            this->_velocity[1] = std::max(this->_velocity[1] - Default::naturalAcceleration, 0);
        }
    }
    // if acceleration is not 0, then standard acceleration applies
    else
    {
        // if both the velocity and acceleration are in the same direction, there's no decay from changing direction
        if (this->_velocity[1] * this->_acceleration[1] >= 0)
        {
            compoundAcceleration = this->_acceleration[1];
        }
        // on the other hand, if the two vectors are opposing, then the natural decay will contribute to the object's acted acceleration
        else
        {
            compoundAcceleration = this->_acceleration[1] + (this->_acceleration[1] < 0? -Default::naturalAcceleration : Default::naturalAcceleration);
        }

        this->_velocity[1] = std::min(std::max(this->_velocity[1] + compoundAcceleration, -this->_maximumVelocity[1]), this->_maximumVelocity[1]);
    }

    // if both coordinates stay unchanged, it returns false to mean there was no update in the object's position
    return !(initialX == this->_position[0] &&
             initialY == this->_position[1]);
}

void Rectangle::DisplayValues()
{
    std::cout << '\n' << "width = " << this->_width << ", height = " << this->_height
              << '\n' << "xPosition = " << this->_position[0] << ", yPosition = " << this->_position[1]
              << '\n' << "xVelocity = " << this->_velocity[0] << ", yVelocity = " << this->_velocity[1]
              << '\n' << "xMaximumVelocity = " << this->_maximumVelocity[0] << ", yMaximumVelocity = " << this->_maximumVelocity[1]
              << '\n' << "xAcceleration = " << this->_acceleration[0] << ", yAcceleration = " << this->_acceleration[1];
}

std::vector<int> &Rectangle::position()
{
    return this->_position;
}

std::vector<int> &Rectangle::velocity()
{
    return this->_velocity;
}

std::vector<int> &Rectangle::maximumVelocity()
{
    return this->_maximumVelocity;
}

std::vector<int> &Rectangle::acceleration()
{
    return this->_acceleration;
}

int &Rectangle::width()
{
    return this->_width;
}

int &Rectangle::height()
{
    return this->_height;
}



#endif // RECTANGLE_H
