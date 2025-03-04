class Point {
    private:
        int x, y;
    
    public:
        // Constructor
        Point(int x = 0, int y = 0) : x(x), y(y) {}
    
        // Overload the + operator to add two points
        Point operator+(const Point& other) {
            return Point(this->x + other.x, this->y + other.y);
        }
    
        // Overload the - operator to subtract two points
        Point operator-(const Point& other) {
            return Point(this->x - other.x, this->y - other.y);
        }
    
        // Overload the == operator to compare two points
        bool operator==(const Point& other) const {
            return this->x == other.x && this->y == other.y;
        }
    
        // Overload the << operator to print the point (used with std::cout)
        friend std::ostream& operator<<(std::ostream& os, const Point& p) {
            os << "(" << p.x << ", " << p.y << ")";
            return os;
        }
    };
