/*

    == Explanation and rationale of testing ==

    Explain and justify how you approached testing, the degree
     to which you're certain you have covered all possibilities,
     and why you think your tests are that thorough.

   Explanation and rationale:
   I started off with basic tests i.e. if there is no path out of the source to the destination and
   if there is no path to the destination because no words are at Euclidean distance 1 to it.
   Then moving onto a simple single path test. There is a path from source to destination, please find
   it. Then, a slight challenge to see if it behaves properly. There are two paths from source to
   destination, one is shorter than the other. Please give out only the shorter one. Ensures that DFS
   and BFS are working as intended. Next challenge, two paths of the same length. To see if the
   program is capable of returning multiple paths. Next challenge, multiple paths, but one longer than
   the others. To see if both of the above cases can be combined. Final challenge, multiple paths, all
   of the same length, print them out lexicographically sorted.

   The tests in essence have been made to check milestones in terms of development of the program.
   From simple challenges moving onto harder ones.

   Basic:
) Source un-leaveable - works.
) Destination unreachable - works.

   Intermediate:
) Find a singular path - works
) Find the shorter path among two - works.
) Find two paths - works.

   Advanced:
) Find two shortest paths among three - works.
) Find multiple shortest paths and sort them - works.

  */

#include "assignments/wl/word_ladder.h"
#include "catch.h"

SCENARIO("Source has no words with Euclidean distance 1, also implying no word ladders")
{
    GIVEN("A lexicon with a source word, a destination word, and random words in between but none of "
          "which are at   Euclidean distance 1 to the source")
    {
        // I actually don't know what goes in given, didn't quite get it. All I know is that
        // things declared here are not accessible in WHEN and THEN
    }

    WHEN("FindLadder is called")
    {
        std::unordered_set<std::string> lexicon{"hey", "why", "who", "are", "cat"};
        std::string source = "hey";
        std::string destination = "cat";

        THEN("No path is returned") { REQUIRE(FindLadder(lexicon, source, destination).empty()); }
    }
}

SCENARIO("No path to destination")
{
    GIVEN("A lexicon with a source word, a destination word, and random words in between but none of "
          "which are at   Euclidean distance 1 to the destination")
    {
    }

    WHEN("FindLadder is called")
    {
        std::unordered_set<std::string> lexicon{"ham", "hat", "hum", "hun", "haw", "cap"};
        std::string source = "ham";
        std::string destination = "cap";

        THEN("No path is returned") { REQUIRE(FindLadder(lexicon, source, destination).empty()); }
    }
}

SCENARIO("Normal input with a single word ladder output")
{
    GIVEN("A lexicon with a source word, a destination word, and random words in between") {}

    WHEN("FindLadder is called")
    {
        std::unordered_set<std::string> lexicon{"cat", "pat", "put", "tut", "tum", "tom"};
        std::string source = "cat";
        std::string destination = "tom";
        std::vector<std::vector<std::string>> expected_solution = {
            {"cat", "pat", "put", "tut", "tum", "tom"}};

        THEN("We'll get a single path")
        {
            REQUIRE(FindLadder(lexicon, source, destination) == expected_solution);
        }
    }
}

SCENARIO("Normal input with two ladders, one shorter and one longer")
{
    GIVEN("A lexicon with a source word, a destination word, and random words in between") {}

    WHEN("FindLadder is called")
    {
        std::unordered_set<std::string> lexicon{
            "dawn", "down", "gown", "goon", "moon", "dawt",
            "dart", "mart", "mort", "moot"}; // Some words may or may not be real. Artistic license
                                             // folks
        std::string source = "dawn";
        std::string destination = "moon";
        std::vector<std::vector<std::string>> expected_solution = {
            {"dawn", "down", "gown", "goon", "moon"}};

        THEN("We'll get the shortest path which excludes the path dawn-dawt-dart-mart-mort-moot-moon")
        {
            REQUIRE(FindLadder(lexicon, source, destination) == expected_solution);
        }
    }
}

SCENARIO("Normal input with two ladders, both same length")
{
    GIVEN("A lexicon with a source word, a destination word, and random words in between") {}

    WHEN("FindLadder is called")
    {
        std::unordered_set<std::string> lexicon{"dawn", "down", "gown", "goon", "moon",
                                                "dawt", "dart", "mart", "mort", "moot"};
        std::string source = "dawn";
        std::string destination = "moot";
        std::vector<std::vector<std::string>> expected_solution = {
            {"dawn", "dawt", "dart", "mart", "mort", "moot"},
            {"dawn", "down", "gown", "goon", "moon", "moot"}};

        THEN("We'll get both paths as the shortest paths")
        {
            REQUIRE(FindLadder(lexicon, source, destination) == expected_solution);
        }
    }
}

SCENARIO("Input with three ladders, two of the same length and one longer")
{
    GIVEN("A lexicon with a source word, a destination word, and random words in between") {}

    WHEN("FindLadder is called")
    {
        std::unordered_set<std::string> lexicon{"cat", "cap", "cop", "con", "can", "cot"};
        std::string source = "cat";
        std::string destination = "con";
        std::vector<std::vector<std::string>> expected_solution = {{"cat", "can", "con"},
                                                                   {"cat", "cot", "con"}};

        THEN("Third path is ignored")
        {
            REQUIRE(FindLadder(lexicon, source, destination) == expected_solution);
        }
    }
}

SCENARIO("Input with more than two ladders, sorted lexicographically ")
{
    GIVEN("A lexicon with a source word, a destination word, and random words in between") {}

    WHEN("FindLadder is called")
    {
        std::unordered_set<std::string> lexicon{
            "dawn", "suss", "saws", "sawn", "sass", "puss", "paws", "pawn", "pass", "muss",
            "maws", "mawn", "mass", "dusk", "durn", "dups", "dunk", "duds", "dubs", "dows",
            "down", "doss", "daws", "dawk", "darn", "dark", "daps", "dank", "curs", "curn",
            "cups", "cuds", "cubs", "cows", "coss", "caws", "cats", "cask", "dads", "dabs",
            "cuts", "cuss", "cusp", "cusk", "cars", "carn", "cark", "caps", "cads", "cabs"};
        std::string source = "dawn";
        std::string destination = "cusp";
        std::vector<std::vector<std::string>> expected_solution = {
            {"dawn", "darn", "carn", "cark", "cask", "cusk", "cusp"},
            {"dawn", "darn", "carn", "cars", "curs", "cuss", "cusp"},
            {"dawn", "darn", "carn", "curn", "curs", "cuss", "cusp"},
            {"dawn", "darn", "dark", "cark", "cask", "cusk", "cusp"},
            {"dawn", "darn", "durn", "curn", "curs", "cuss", "cusp"},
            {"dawn", "dawk", "dank", "dunk", "dusk", "cusk", "cusp"},
            {"dawn", "dawk", "dark", "cark", "cask", "cusk", "cusp"},
            {"dawn", "daws", "caws", "cabs", "cubs", "cuss", "cusp"},
            {"dawn", "daws", "caws", "cads", "cuds", "cuss", "cusp"},
            {"dawn", "daws", "caws", "caps", "cups", "cuss", "cusp"},
            {"dawn", "daws", "caws", "cars", "curs", "cuss", "cusp"},
            {"dawn", "daws", "caws", "cats", "cuts", "cuss", "cusp"},
            {"dawn", "daws", "caws", "cows", "coss", "cuss", "cusp"},
            {"dawn", "daws", "dabs", "cabs", "cubs", "cuss", "cusp"},
            {"dawn", "daws", "dabs", "dubs", "cubs", "cuss", "cusp"},
            {"dawn", "daws", "dads", "cads", "cuds", "cuss", "cusp"},
            {"dawn", "daws", "dads", "duds", "cuds", "cuss", "cusp"},
            {"dawn", "daws", "daps", "caps", "cups", "cuss", "cusp"},
            {"dawn", "daws", "daps", "dups", "cups", "cuss", "cusp"},
            {"dawn", "daws", "dows", "cows", "coss", "cuss", "cusp"},
            {"dawn", "daws", "dows", "doss", "coss", "cuss", "cusp"},
            {"dawn", "daws", "maws", "mass", "muss", "cuss", "cusp"},
            {"dawn", "daws", "paws", "pass", "puss", "cuss", "cusp"},
            {"dawn", "daws", "saws", "sass", "suss", "cuss", "cusp"},
            {"dawn", "down", "dows", "cows", "coss", "cuss", "cusp"},
            {"dawn", "down", "dows", "doss", "coss", "cuss", "cusp"},
            {"dawn", "mawn", "maws", "mass", "muss", "cuss", "cusp"},
            {"dawn", "pawn", "paws", "pass", "puss", "cuss", "cusp"},
            {"dawn", "sawn", "saws", "sass", "suss", "cuss", "cusp"}};

        THEN("Lots of paths, sorted lexicographically")
        {
            REQUIRE(FindLadder(lexicon, source, destination) == expected_solution);
        }
    }
}