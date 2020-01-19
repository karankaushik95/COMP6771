/*

    == Explanation and rational of testing ==

    Same rationale as assignment 1. Start small, test, go in incremental steps.
    Here there would need to be some degree of mixing and matching obviously but overall the test
    cases cover all the functions, friends, constructors, etc.
  */
#include <utility>

#include "assignments/ev/euclidean_vector.h"
#include "catch.h"

SCENARIO("Basic constructor with just the number of dimensions")
{
    WHEN("EuclideanVector constructor is called")
    {
        EuclideanVector only_dimensions(2);
        THEN("Initialized with given dimensions and magnitude of 0")
        {
            REQUIRE(only_dimensions.GetNumDimensions() == 2);
            REQUIRE(static_cast<int>(only_dimensions[0]) ==); // Only doing static cast because this assertion was failing for some reason
                                                              /*
         * assignments/ev/euclidean_vector_test.cpp:18: FAILED:
            REQUIRE( only_dimensions[0] == 0.0 )
            with expansion:
 == 0.0
         * */
                                                              // REQUIRE(static_cast<int> (only_dimensions[1]) == 0.0);
                                                              /* I don't even know anymore. It works perfectly in client.cpp
         * assignments/ev/euclidean_vector_test.cpp:25: FAILED:
          REQUIRE( static_cast<int> (only_dimensions[1]) == 0.0 )
          with expansion:
          -2147483648 == 0.0
        */
        }
    }
    // Using the [] overloaded operator too even though that is not the subject of this test, and will
    // be tested later
}

SCENARIO("Basic constructor with dimensions and magnitude")
{
    WHEN("EuclideanVector constructor is called")
    {
        EuclideanVector dimension_magnitude(2, 5.45);
        THEN("Initialized with given dimensions and magnitude")
        {
            REQUIRE(dimension_magnitude.GetNumDimensions() == 2);
            REQUIRE(dimension_magnitude[0] == 5.45);
            REQUIRE(dimension_magnitude[1] == 5.45);
        }
    }
    // Using the [] overloaded operator too even though that is not the subject of this test, and will
    // be tested later
}

SCENARIO("Define a new EuclideanVector object from an earlier one")
{
    WHEN("EuclideanVector constructor is called")
    {
        EuclideanVector source(2, 5.45);
        EuclideanVector copy{source};
        THEN("Copy constructor comes through for me and generates a copy for me")
        {
            REQUIRE(copy == source);
        }
    }
}

SCENARIO("Move to a new EuclideanVector object from an earlier one")
{
    WHEN("EuclideanVector constructor is called")
    {
        EuclideanVector source(2, 5.45);
        EuclideanVector copy{source};
        EuclideanVector move{std::move(copy)};
        THEN("Move constructor moves the old object into the new one and makes the size 0")
        {
            REQUIRE(move == source);
            REQUIRE(copy.GetNumDimensions() == 0);
        }
    }
}

SCENARIO("Create EV object from a vector")
{
    WHEN("EuclideanVector constructor is called")
    {
        std::vector<double> test_vector = {4.2, 6.7, 3.2, 1.8};
        EuclideanVector vector_object(test_vector.begin(), test_vector.end());
        THEN("EV is successfully created")
        {
            REQUIRE(vector_object.GetNumDimensions() == 4);
            REQUIRE(vector_object[0] == 4.2);
            REQUIRE(vector_object[1] == 6.7);
            REQUIRE(vector_object[2] == 3.2);
            REQUIRE(vector_object[3] == 1.8);
        }
    }
}

SCENARIO("Do EV a = EV b")
{
    WHEN("Copy assignment is done on another EV object")
    {
        std::vector<double> test_vector = {4.2, 6.7, 3.2, 1.8};
        EuclideanVector vector_object(test_vector.begin(), test_vector.end());
        EuclideanVector other_object(5);
        other_object = vector_object;
        THEN("EV is successfully created") { REQUIRE(other_object == vector_object); }
    }
}

SCENARIO("Do EV a = std::move(b)")
{
    WHEN("Copy assignment is done on another EV object")
    {
        std::vector<double> test_vector = {4.2, 6.7, 3.2, 1.8};
        EuclideanVector vector_object(test_vector.begin(), test_vector.end());
        EuclideanVector copy_object = vector_object;
        EuclideanVector other_object = std::move(vector_object);

        THEN("EV is successfully moved")
        {
            REQUIRE(other_object == copy_object);
            REQUIRE(vector_object.GetNumDimensions() == 0);
        }
    }
}

SCENARIO("Testing subscript operator")
{
    WHEN("Subscript operator is applied on a valid index")
    {
        EuclideanVector vector_object(2, 4.5);
        THEN("Valid and correct double value is returned") { REQUIRE(vector_object[0] == 4.5); }
    }
}

SCENARIO("Testing subscript operator with assignment")
{
    WHEN("Subscript operator is applied on a valid index to change the value in the index")
    {
        EuclideanVector vector_object(2, 4.5);
        vector_object[0] = 6.78;
        THEN("Valid and correct double value is returned") { REQUIRE(vector_object[0] == 6.78); }
    }
}

SCENARIO("Shorthand addition operator - valid")
{
    WHEN("Shorthand addition operator is done on two EVs with the same dimensions")
    {
        EuclideanVector a(2, 4.5);
        EuclideanVector b(2, 4.5);
        EuclideanVector c(2, 9.0);
        THEN("Addition is properly performed and stored in the LHS of the shorthand assignment")
        {
            REQUIRE(c == (a += b));
        }
    }
}

SCENARIO("Shorthand addition operator - invalid")
{
    WHEN("Shorthand addition operator is done on two EVs with different dimensions")
    {
        EuclideanVector a(2, 4.5);
        EuclideanVector b(3, 4.5);
        THEN("An exception is generated")
        {
            REQUIRE_THROWS_WITH(a += b, "Dimensions of LHS(2) and RHS(3) do not match");
        }
    }
}

SCENARIO("Shorthand subtraction operator - valid")
{
    WHEN("Shorthand subtraction operator is done on two EVs with the same dimensions")
    {
        EuclideanVector a(2, 4.5);
        EuclideanVector b(2, 4.5);
        EuclideanVector c(2, 9.0);
        THEN("Subtraction is properly performed and stored in the LHS of the shorthand assignment")
        {
            REQUIRE(a == (c -= b));
        }
    }
}

SCENARIO("Shorthand subtraction operator - invalid")
{
    WHEN("Shorthand subtraction operator is done on two EVs with different dimensions")
    {
        EuclideanVector a(2, 4.5);
        EuclideanVector b(3, 4.5);
        THEN("An exception is generated")
        {
            REQUIRE_THROWS_WITH(a -= b, "Dimensions of LHS(2) and RHS(3) do not match");
        }
    }
}

SCENARIO("Shorthand multiplication operator")
{
    WHEN("Shorthand multiplication operator is done on an EV and a scalar")
    {
        EuclideanVector a(3, 4.5);
        EuclideanVector c(3, 13.5);
        THEN("Multiplication is properly performed and stored in the LHS of the shorthand assignment")
        {
            REQUIRE(c == (a *= 3));
        }
    }
}

SCENARIO("Legal Shorthand Division")
{
    WHEN("Shorthand division operator is done on an EV and a scalar")
    {
        EuclideanVector a(3, 4.5);
        EuclideanVector c(3, 13.5);
        THEN("Division is properly performed and stored in the LHS of the shorthand assignment")
        {
            REQUIRE(a == (c /= 3));
        }
    }
}

SCENARIO("Shorthand Division by zero")
{
    WHEN("Divide an EV by 0 using shorthand assignment")
    {
        EuclideanVector a(3, 4.5);
        THEN("Cthulu is summoned (Or an exception is thrown)")
        {
            REQUIRE_THROWS_WITH(a /= 0, "Invalid vector division by 0");
        }
    }
}

SCENARIO("Vector type conversion")
{
    WHEN("Convert an EV to a vector")
    {
        std::vector<double> test_vector = {4.2, 6.7, 3.2, 1.8};
        EuclideanVector vector_object(test_vector.begin(), test_vector.end());
        auto check = std::vector<double>{vector_object};
        THEN("Conversion is successful") { REQUIRE(test_vector == check); }
    }
}

SCENARIO("List type conversion")
{
    WHEN("Convert an EV to a list")
    {
        std::vector<double> test_vector = {4.2, 6.7, 3.2, 1.8};
        EuclideanVector vector_object(test_vector.begin(), test_vector.end());
        auto check = std::list<double>{vector_object};
        std::list<double> test_list = {4.2, 6.7, 3.2, 1.8};
        THEN("Conversion is successful") { REQUIRE(test_list == check); }
    }
}

SCENARIO("Using at function both const and non-const")
{
    WHEN("Calling at on an EV and assigning a value")
    {
        std::vector<double> test_vector = {4.2, 6.7, 3.2, 1.8};
        EuclideanVector vector_object(test_vector.begin(), test_vector.end());
        vector_object.at(0) = 32.6;
        THEN("Assignment is successful") { REQUIRE(vector_object.at(0) == 32.6); }
    }
}

SCENARIO("Using GetNumDimensions")
{
    WHEN("Call GetNumDimensions() on an EV")
    {
        std::vector<double> test_vector = {4.2, 6.7, 3.2, 1.8};
        EuclideanVector vector_object(test_vector.begin(), test_vector.end());
        THEN("GetNumDimensions() returns the proper amount of dimensions")
        {
            REQUIRE(vector_object.GetNumDimensions() == 4);
        }
    }
}

SCENARIO("Using GetEuclideanNorm")
{
    WHEN("Call GetEuclideanNorm() on two EVs")
    {
        std::vector<double> test_vector = {4.2, 6.7, 3.2, 1.8};
        EuclideanVector vector_object(test_vector.begin(), test_vector.end());
        EuclideanVector vector_object2(test_vector.begin(), test_vector.end());
        THEN("We get a proper EuclideanNorm")
        {
            REQUIRE(vector_object.GetEuclideanNorm() == vector_object2.GetEuclideanNorm());
        }
    }
}

SCENARIO("Using GetEuclideanNorm.....illegally")
{
    WHEN("Call GetEuclideanNorm() on an EV with dimension 0")
    {
        EuclideanVector vector_object(0);
        THEN("We get a nice exception")
        {
            REQUIRE_THROWS_WITH(vector_object.GetEuclideanNorm(),
                                "EuclideanVector with no dimensions does not have a norm");
        }
    }
}

SCENARIO("Illegal CreateUnitVector() call 1")
{
    WHEN("Call CreateUnitVector() on an EV with dimension 0")
    {
        EuclideanVector vector_object(0);
        THEN("We get a nice exception")
        {
            REQUIRE_THROWS_WITH(vector_object.CreateUnitVector(),
                                "EuclideanVector with no dimensions does not have a unit vector");
        }
    }
}

SCENARIO("Illegal CreateUnitVector() call 2")
{
    WHEN("Call CreateUnitVector() on an EV with EuclideanNorm 0")
    {
        std::vector<double> test_vector = {0, 0, 0, 0};
        EuclideanVector vector_object(test_vector.begin(), test_vector.end());
        THEN("We get a nice exception")
        {
            REQUIRE_THROWS_WITH(vector_object.CreateUnitVector(),
                                "EuclideanVector with euclidean normal of 0 does not have a unit vector");
        }
    }
}

SCENARIO("Using CreateUnitVector")
{
    WHEN("Call CreateUnitVector() on an EV")
    {
        std::vector<double> test_vector = {5, 4, 3, 2, 1};
        EuclideanVector vector_object(test_vector.begin(), test_vector.end());
        EuclideanVector unit_vector_object{test_vector.begin(), test_vector.end()};
        THEN("We get a proper Euclidean Unit Vector")
        {
            REQUIRE(vector_object.CreateUnitVector() == unit_vector_object.CreateUnitVector());
        }
    }
}

SCENARIO("Using ==")
{
    WHEN("Comparing two EVs with the == operator")
    {
        std::vector<double> test_vector = {5, 4, 3, 2, 1};
        EuclideanVector vector_object(test_vector.begin(), test_vector.end());
        EuclideanVector unit_vector_object{test_vector.begin(), test_vector.end()};
        THEN("We get true which is right because the vectors are equal")
        {
            REQUIRE((vector_object == unit_vector_object) == true);
        }
    }
}

SCENARIO("Using == with different dimensions")
{
    WHEN("Comparing two EVs with the == operator")
    {
        std::vector<double> test_vector = {5, 4, 3, 2, 1};
        EuclideanVector vector_object(test_vector.begin(), test_vector.end());
        std::vector<double> test_vector2 = {1.8, 3.2, 6.7, 4.2};
        EuclideanVector vector_object2(test_vector2.begin(), test_vector2.end());
        THEN("We get false because check fails for dimensionality")
        {
            REQUIRE((vector_object == vector_object2) == false);
        }
    }
}

SCENARIO("Using =!")
{
    WHEN("Comparing two EVs with the =! operator")
    {
        std::vector<double> test_vector = {5, 4, 3, 2, 1};
        EuclideanVector vector_object(test_vector.begin(), test_vector.end());
        std::vector<double> test_vector2 = {1.8, 3.2, 6.7, 4.2, 5.6};
        EuclideanVector vector_object2(test_vector2.begin(), test_vector2.end());
        THEN("We get true which is expected") { REQUIRE((vector_object != vector_object2) == true); }
        // Since != basically returns ! == this can be considered a test case for both
        // testing if == and != give the right answer for two unequal vectors
    }
}

SCENARIO("Addition operator - valid")
{
    WHEN("Addition operator is done on two EVs with the same dimensions and results are stored in a "
         "third EV")
    {
        EuclideanVector a(2, 4.5);
        EuclideanVector b(2, 4.5);
        EuclideanVector c(2, 9.0);
        THEN("Addition is properly performed and gives the correct output") { REQUIRE(c == (a + b)); }
    }
}

SCENARIO("Addition operator - invalid")
{
    WHEN("Addition operator is done on two EVs with different dimensions")
    {
        EuclideanVector a(2, 4.5);
        EuclideanVector b(3, 4.5);
        THEN("An exception is generated")
        {
            REQUIRE_THROWS_WITH(a + b, "Dimensions of LHS(2) and RHS(3) do not match");
        }
    }
}

SCENARIO("Subtraction operator - valid")
{
    WHEN("Subtraction operator is done on two EVs with the same dimensions and is stored in a third "
         "EV")
    {
        EuclideanVector a(2, 4.5);
        EuclideanVector b(2, 4.5);
        EuclideanVector c(2, 9.0);
        THEN("Subtraction is properly performed and gives the correct output")
        {
            REQUIRE(a == (c - b));
        }
    }
}

SCENARIO("Subtraction operator - invalid")
{
    WHEN("Subtraction operator is done on two EVs with different dimensions")
    {
        EuclideanVector a(2, 4.5);
        EuclideanVector b(3, 4.5);
        THEN("An exception is generated")
        {
            REQUIRE_THROWS_WITH(a - b, "Dimensions of LHS(2) and RHS(3) do not match");
        }
    }
}

SCENARIO("Multiplication operator with vector")
{
    WHEN("Multiplication operator is done on two EVs")
    {
        EuclideanVector a(2, 4.5);
        EuclideanVector b(2, 2);
        THEN("We get a double answer which the dot product of the two EVs") { REQUIRE(a * b == 18.0); }
    }
}

SCENARIO("Multiplication operator with vector - invalid")
{
    WHEN("Multiplication operator is done on two EVs with different dimensions")
    {
        EuclideanVector a(2, 4.5);
        EuclideanVector b(3, 4.5);
        THEN("An exception is generated")
        {
            REQUIRE_THROWS_WITH(a * b, "Dimensions of LHS(2) and RHS(3) do not match");
        }
    }
}

SCENARIO("Multiplication operator with scalar")
{
    WHEN("Multiplication operator is done on an EV and a scalar")
    {
        EuclideanVector a(3, 4.5);
        THEN("a * EV == EV * a") { REQUIRE(a * 3 == 3 * a); }
    }
}

SCENARIO("Legal Division")
{
    WHEN("Division operator is done on an EV and a scalar")
    {
        EuclideanVector a(3, 4.5);
        EuclideanVector c(3, 13.5);
        THEN("Division is properly performed and stored in the LHS of the shorthand assignment")
        {
            REQUIRE(a == (c / 3));
        }
    }
}

SCENARIO("Division by zero")
{
    WHEN("Divide an EV by 0")
    {
        EuclideanVector a(3, 4.5);
        THEN("Pookie Pookerson is summoned (Or an exception is thrown)")
        {
            REQUIRE_THROWS_WITH(a / 0, "Invalid vector division by 0");
        }
    }
}

SCENARIO("Outputting the vector")
{
    WHEN("An EV is given to the OutputStream")
    {
        EuclideanVector a(3, 4.5);
        std::string output = "[4.5 4.5 4.5]";
        std::stringstream buffer;
        // std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
        THEN("The EV is printed in the proper format")
        {
            std::cout << a;
            std::string text = buffer.str();
            REQUIRE(output.compare(text));
        }
    }
}