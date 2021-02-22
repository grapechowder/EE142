/*
 * Program to test the Vector2d class functions.
 */

#include <iostream>
#include <sstream>
#include <string>
#include "Vector2d.h"

class UnitTest
{
    public:
    static void testResult(std::string msg, bool result);
    static void displayResults();

    private:
    static int tests;
    static int passed;
};

int UnitTest::tests = 0;
int UnitTest::passed = 0;

// Display message about a test
void UnitTest::testResult(std::string msg, bool result)
{
    tests++;
    std::cout << msg << " -- ";
    if (result) {
        std::cout << "Passed\n";
        passed++;
    }   
    else {
        std::cout << "FAILED\n";
    }
}

void UnitTest::displayResults()
{
    std::cout << std::endl;
    std::cout << "Passed " << passed << " out of " << tests << " tests.\n";
}



int main(void)
{
    int tests = 0;
    int passed = 0;

    // Each test is enclosed in braces so that we can declare local variables
    {
        Vector2d v;

        UnitTest::testResult("Testing default constructor", 
            (v.getX() == 0) 
            && (v.getY() == 0));
    }

    {
        Vector2d v(3, 4);

        UnitTest::testResult("Testing parameterized constructor", 
            (v.getX() == 3.0) 
            && (v.getY() == 4.0));
    }

    {
        Vector2d v;
        v.setX(4);
        v.setY(-9);

        UnitTest::testResult("Testing setters and getters", 
            (v.getX() == 4.0) 
            && (v.getY() == -9.0));
    }

    {
        Vector2d v1(3, 4);
        Vector2d v2(-5, 8);

        UnitTest::testResult("Testing dot product", 
            (v1.dot(v2) == 17.0) 
            && (v1.dot(v2) == v2.dot(v1)));
    }

    {
        UnitTest::testResult("Testing magnitude", 
            (Vector2d().magnitude() == 0.0) 
                && (Vector2d(3, 4).magnitude() == 5.0)   
        );
    }

    {
        UnitTest::testResult("Testing normalize", 
            (Vector2d(8, 12).normalize().magnitude() == 1.0) 
                && (Vector2d().normalize().magnitude() == 0.0)   
        );
    }

    {
        Vector2d v1(4, 2);
        Vector2d v2(9, -5);
        v1 += v2;

        UnitTest::testResult("Testing += operator", 
            (v1.getX() == 13.0) && (v1.getY() == -3.0)
        );
    }

    {
        Vector2d v1(4, 2);
        Vector2d v2(9, -5);
        v1 -= v2;

        UnitTest::testResult("Testing -= operator", 
            (v1.getX() == -5.0) && (v1.getY() == 7.0)
        );
    }

    {
        Vector2d v1(4, 2);
        v1 *= 5;

        UnitTest::testResult("Testing *= operator", 
            (v1.getX() == 20.0) && (v1.getY() == 10.0)
        );
    }

    {
        Vector2d v1(4, 2);
        Vector2d v2(9, -5);
        Vector2d v3 = v1 + v2;

        UnitTest::testResult("Testing + operator", 
            (v3.getX() == 13.0) && (v3.getY() == -3.0)
            && (v1.getX() == 4) && (v1.getY() == 2)
        );
    }

    {
        Vector2d v1(4, 2);
        Vector2d v2(9, -5);
        Vector2d v3 = v1 - v2;

        UnitTest::testResult("Testing - operator", 
            (v3.getX() == -5.0) && (v3.getY() == 7.0)
            && (v1.getX() == 4) && (v1.getY() == 2)
        );
    }

    {
        Vector2d v1(4, 2);
        double c = 5.0;
        Vector2d v2 = v1 * c;;
        Vector2d v3 = c * v1;

        UnitTest::testResult("Testing * operator", 
            (v2.getX() == 20.0) && (v2.getY() == 10.0)
            && (v2.getX() == v3.getX()) && (v2.getY() == v3.getY())
            && (v1.getX() == 4) && (v1.getY() == 2)
        );
    }

    {
        Vector2d v1(4, -2);
        Vector2d v2 = -v1;

        UnitTest::testResult("Testing unary - operator", 
            (v2.getX() == -4.0) && (v2.getY() == 2.0)
            && (v1.getX() == 4.0) && (v1.getY() == -2.0)
        );
    }

    {
        Vector2d v1(4, 2);
        Vector2d v2(4, 2);
        Vector2d v3(-5, 2);

        UnitTest::testResult("Testing == operator", 
            (v1 == v2) && (v2 == v1) 
            && !(v1 == v3) && !(v3 == v1)
        );
    }

    {
        Vector2d v1(4, 2);
        Vector2d v2(4, 2);
        Vector2d v3(-5, 2);

        UnitTest::testResult("Testing != operator", 
            !(v1 != v2) && !(v2 != v1) 
            && (v1 != v3) && (v3 != v1)
        );
    }

    {
        std::ostringstream os;
        Vector2d v1(4, -3);

        os << v1;

        UnitTest::testResult("Testing << operator",
            (std::string("(4, -3)") == os.str())
        );
    }

    {
        std::istringstream is(std::string("12 31"));
        Vector2d v1;

        is >> v1;

        UnitTest::testResult("Testing >> operator",
            (v1.getX() == 12.0) && (v1.getY() == 31.0)
        );
    }

    UnitTest::displayResults();

    return 0;
}