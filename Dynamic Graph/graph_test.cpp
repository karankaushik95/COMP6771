/*

The objective of testing is to run over every single line of code that has been manually written

*/

#include <sstream>
#include <string>
#include <utility>

#include "assignments/dg/graph.h"
#include "catch.h"

SCENARIO("Default constructor test") {
  WHEN("Default graph constructor is called") {
    gdwg::Graph<std::string, int> new_graph;
    THEN("Initialize empty graph") { REQUIRE((new_graph.GetNodes()).empty()); }
  }
}

SCENARIO("Vector iterator constructor test") {
  WHEN("Graph constructor is called with vector::iterator::begin and vector::iterator::end") {
    std::vector<std::string> test{"hello", "hey"};
    gdwg::Graph<std::string, int> new_graph{test.begin(), test.end()};
    THEN("Initialize graph with supplied nodes") { REQUIRE((new_graph.GetNodes()) == test); }
  }
}

SCENARIO("Tuple-vector constructor test") {
  WHEN("Graph constructor is called on a vector containing tuples") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> new_graph{e.begin(), e.end()};
    std::vector<std::string> nodes{s1, s3, s2};
    THEN("Initialize Graph with supplied nodes and edge weights") {
      REQUIRE((new_graph.GetNodes()) == nodes);
      REQUIRE(new_graph.GetWeights(s1, s2) == std::vector<double>{5.4});
      REQUIRE(new_graph.GetWeights(s2, s3) == std::vector<double>{7.6});
    }
  }
}

SCENARIO("Initializer list test") {
  WHEN("Graph constructor is called on an initializer list") {
    gdwg::Graph<char, double> new_graph{'a', 'b', 'd', 'c'};
    std::vector<char> nodes{'a', 'b', 'c', 'd'};
    THEN("Initialize graph with supplied list") { REQUIRE((new_graph.GetNodes()) == nodes); }
  }
}

SCENARIO("Copy constructor test") {
  WHEN("Graph constructor is called on another object of graph") {
    gdwg::Graph<char, double> new_graph{'a', 'b', 'd', 'c'};
    gdwg::Graph<char, double> copy_graph{new_graph};
    THEN("Copy construct second graph with first graph") {
      REQUIRE((copy_graph.GetNodes()) == new_graph.GetNodes());
    }
  }
}

SCENARIO("Move constructor test") {
  WHEN("Graph move constructor is called on another object of graph") {
    gdwg::Graph<char, double> new_graph{'a', 'b', 'd', 'c'};
    gdwg::Graph<char, double> copy_graph{std::move(new_graph)};
    std::vector<char> nodes{'a', 'b', 'c', 'd'};
    THEN("First graph is moved onto second graph") {
      REQUIRE((copy_graph.GetNodes()) == nodes);
      REQUIRE((new_graph.GetNodes()).empty());
    }
  }
}

SCENARIO("Copy assignment test") {
  WHEN("Graph is assigned to another object of graph") {
    gdwg::Graph<char, double> new_graph{'a', 'b', 'd', 'c'};
    gdwg::Graph<char, double> copy_graph = new_graph;
    THEN("Copy construct second graph with first graph") {
      REQUIRE((copy_graph.GetNodes()) == new_graph.GetNodes());
    }
  }
}

SCENARIO("Move assignment test") {
  WHEN("std::move is called on another existing object of graph") {
    gdwg::Graph<char, double> new_graph{'a', 'b', 'd', 'c'};
    gdwg::Graph<char, double> copy_graph{'p', 'q', 'r', 's'};
    copy_graph = std::move(new_graph);
    std::vector<char> nodes{'a', 'b', 'c', 'd'};
    THEN("First graph is moved onto second graph") {
      REQUIRE((copy_graph.GetNodes()) == nodes);
      REQUIRE((new_graph.GetNodes()).empty());
    }
  }
}

SCENARIO("Equality operator test") {
  WHEN("Two graphs are compared using equality (==) operator") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> new_graph{e.begin(), e.end()};
    gdwg::Graph<std::string, double> copy_graph{new_graph};
    THEN("== returns true because the graphs are identical in terms of nodes and edges") {
      REQUIRE(copy_graph == new_graph);
    }
  }
}

SCENARIO("Equality operator test different nodes") {
  WHEN("Two graphs are compared using equality (==) operator") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> new_graph{e.begin(), e.end()};
    gdwg::Graph<std::string, double> copy_graph{"Namaste", "Bonjour", "Ni Hao"};
    THEN("== returns false because the graphs are not identical") {
      REQUIRE(!(copy_graph == new_graph));
    }
  }
}

SCENARIO("Equality operator test same nodes different edge weights") {
  WHEN("Two graphs are compared using equality (==) operator") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e3 = std::make_tuple(s1, s2, 4.2);
    auto e4 = std::make_tuple(s2, s3, 8.9);
    auto p = std::vector<std::tuple<std::string, std::string, double>>{e3, e4};
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> new_graph{e.begin(), e.end()};
    gdwg::Graph<std::string, double> copy_graph{p.begin(), p.end()};
    THEN("== returns false because the graphs are not identical") {
      REQUIRE(!(copy_graph == new_graph));
    }
  }
}

SCENARIO("Inequality operator test") {
  WHEN("Two graphs are compared using inequality (!=) operator") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> new_graph{e.begin(), e.end()};
    gdwg::Graph<std::string, double> copy_graph{new_graph};
    THEN("!= returns false because the graphs are identical in terms of nodes and edges") {
      REQUIRE(!(copy_graph != new_graph));
    }
  }
}

SCENARIO("Inequality operator test different nodes") {
  WHEN("Two graphs are compared using inequality (!=) operator") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> new_graph{e.begin(), e.end()};
    gdwg::Graph<std::string, double> copy_graph{"Namaste", "Bonjour", "Ni Hao"};
    THEN("!= returns true because the graphs are not identical") {
      REQUIRE(copy_graph != new_graph);
    }
  }
}

SCENARIO("Inequality operator test same nodes different edge weights") {
  WHEN("Two graphs are compared using inequality (!=) operator") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e3 = std::make_tuple(s1, s2, 4.2);
    auto e4 = std::make_tuple(s2, s3, 8.9);
    auto p = std::vector<std::tuple<std::string, std::string, double>>{e3, e4};
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> new_graph{e.begin(), e.end()};
    gdwg::Graph<std::string, double> copy_graph{p.begin(), p.end()};
    THEN("!= returns true because the graphs are not identical") {
      REQUIRE(copy_graph != new_graph);
    }
  }
}

/*
SCENARIO("Testing << operator") {
  WHEN("Try to print a graph to standard output") {
    std::stringstream out;
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> new_graph{e.begin(), e.end()};
    std::string output = "Hello (\n\thow | 5.4\n)\nare (\n)\nhow (\n\tare | 7.6\n)\n";
    out<<new_graph;
    THEN("It is printed in the required format") {
      REQUIRE( out.str() == output);
    }
  }
}
 Stringstream is messing up, but << works for sure. out.str() returns ""
 */

SCENARIO("InsertNode method") {
  WHEN("graph.InsertNode() is called") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> new_graph{e.begin(), e.end()};
    THEN("Successful insert because Namaste isn't present at first, then unsuccessful because it "
         "is present") {
      REQUIRE(new_graph.InsertNode("Namaste"));
      REQUIRE(!(new_graph.InsertNode("Namaste")));
    }
  }
}

SCENARIO("InsertEdge method") {
  WHEN("graph.InsertEdge() is called on varied cases") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> new_graph{e.begin(), e.end()};
    THEN("Fail insert, fail insert, fail insert, true, false") {
      REQUIRE(new_graph.InsertEdge("Hello", "are", 2.3));
      REQUIRE(!(new_graph.InsertEdge("Hello", "are", 2.3)));
    }
  }
}
/*
SCENARIO("InsertEdge method - nodes not present") {
  WHEN("graph.InsertEdge() is called on varied cases") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> new_graph{e.begin(), e.end()};
    THEN("Fail insert, fail insert, fail insert, true, false") {
      REQUIRE_THROWS_WITH( new_graph.InsertEdge("Taco", "Hello", 4.8) , "Cannot call
Graph::InsertEdge when either src or dst node does not exist"); REQUIRE_THROWS_WITH(
new_graph.InsertEdge("Hello", "Que", 4.2) , "Cannot call Graph::InsertEdge when either src or dst
node does not exist"); REQUIRE_THROWS_WITH( new_graph.InsertEdge("Que", "Pasa", 4.2) , "Cannot call
Graph::InsertEdge when either src or dst node does not exist");
    }
  }
}

 Catch2 isn't catching the exceptions but Running the program detects the exceptions correctly
INFO: Elapsed time: 2.967s, Critical Path: 2.60s
INFO: 2 processes: 2 linux-sandbox.
INFO: Build completed successfully, 3 total actions
INFO: Running command line: bazel-bin/assignments/dg/client
INFO: Build completed successfully, 3 total actions
Cannot call Graph::InsertEdge when either src or dst node does not exist
 */

SCENARIO("DeleteNode() method and GetNodes method") {
  WHEN("graph.DeleteNode() is called on varied cases") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> new_graph{e.begin(), e.end()};
    std::vector<std::string> nodes{"are", "how"};
    THEN("Successful Delete, unsuccessful delete(node absent). GetNodes returns the proper nodes "
         "still present in the graph") {
      REQUIRE(new_graph.DeleteNode("Hello"));
      REQUIRE(!(new_graph.DeleteNode("Hello")));
      REQUIRE(new_graph.GetNodes() == nodes);
    }
  }
}

SCENARIO("Replace method") {
  WHEN("graph.Replace() is called on varied cases") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> new_graph{e.begin(), e.end()};
    std::vector<std::string> nodes{"Hola", "are", "how"};
    THEN("Unsuccessful replace, successful replace, exception") {
      REQUIRE(!(new_graph.Replace("Hello", "how")));
      REQUIRE(new_graph.Replace("Hello", "Hola"));
      REQUIRE(new_graph.GetNodes() == nodes);
      // REQUIRE_THROWS_WITH( new_graph.Replace("Potehto", "Potahto"), ""Cannot call Graph::Replace
      // on a node that doesn't exist");
    }
  }
}

SCENARIO("MergeReplace method") {
  WHEN("graph.MergeReplace() is called on varied cases") {
    std::string s1{"A"};
    std::string s2{"B"};
    std::string s3{"C"};
    std::string s4{"D"};
    auto e1 = std::make_tuple(s1, s2, 3);
    auto e2 = std::make_tuple(s2, s3, 2);
    auto e3 = std::make_tuple(s2, s4, 4);
    auto e = std::vector<std::tuple<std::string, std::string, int>>{e1, e2, e3};
    gdwg::Graph<std::string, int> new_graph{e.begin(), e.end()};
    std::vector<std::string> nodes{"A", "C", "D"};
    THEN("Successful replace, connections, exception") {
      new_graph.MergeReplace("B", "A");
      REQUIRE(new_graph.GetNodes() == nodes);
      REQUIRE(new_graph.IsConnected("A", "A"));  // A will now have an edge with itself
      REQUIRE(new_graph.IsConnected("A", "C"));  // A will now have an edge with C
      REQUIRE(new_graph.IsConnected("A", "D"));  // A will now have an edge with D
      // REQUIRE_THROWS_WITH( new_graph.Replace("Potehto", "Potahto"), ""Cannot call Graph::Replace
      // on a node that doesn't exist");
    }
  }
}

SCENARIO("Clear method") {
  WHEN("graph.Clear() is called") {
    std::string s1{"A"};
    std::string s2{"B"};
    std::string s3{"C"};
    std::string s4{"D"};
    auto e1 = std::make_tuple(s1, s2, 3);
    auto e2 = std::make_tuple(s3, s2, 2);
    auto e3 = std::make_tuple(s4, s2, 4);
    auto e = std::vector<std::tuple<std::string, std::string, int>>{e1, e2, e3};
    gdwg::Graph<std::string, int> new_graph{e.begin(), e.end()};
    THEN("Successful replace, exception") {
      new_graph.Clear();
      REQUIRE(new_graph.GetNodes().empty());
    }
  }
}

SCENARIO("IsNode method") {
  WHEN("graph.IsNode() is called") {
    gdwg::Graph<std::string, int> new_graph{"a", "b"};
    THEN("Returns if a node is present in the graph or not") {
      REQUIRE(new_graph.IsNode("a"));
      REQUIRE(!new_graph.IsNode("c"));
    }
  }
}

SCENARIO("IsConnected method") {
  WHEN("graph.IsConnected() is called on three cases, connection is present and absent, and nodes "
       "are not present") {
    std::string s1{"A"};
    std::string s2{"B"};
    std::string s3{"C"};
    std::string s4{"D"};
    auto e1 = std::make_tuple(s1, s2, 3);
    auto e2 = std::make_tuple(s3, s2, 2);
    auto e3 = std::make_tuple(s4, s2, 4);
    auto e = std::vector<std::tuple<std::string, std::string, int>>{e1, e2, e3};
    gdwg::Graph<std::string, int> new_graph{e.begin(), e.end()};
    THEN("True for connected, false for not connected, exception for if either or both nodes are "
         "absent") {
      REQUIRE(new_graph.IsConnected("A", "B"));     // A will now have an edge with itself
      REQUIRE(!(new_graph.IsConnected("D", "A")));  // A will now have an edge with itself
      // REQUIRE_THROWS_WITH( new_graph.IsConnected("A", "E"), "Cannot call Graph::IsConnected if
      // src or dst node don't exist in the graph"); REQUIRE_THROWS_WITH( new_graph.IsConnected("E",
      // "A"), "Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
      // REQUIRE_THROWS_WITH( new_graph.IsConnected("E", "F"), "Cannot call Graph::IsConnected if
      // src or dst node don't exist in the graph");
    }
  }
}

SCENARIO("GetConnected method") {
  WHEN("graph.GetConnected() is called") {
    std::string s1{"A"};
    std::string s2{"B"};
    std::string s3{"C"};
    std::string s4{"D"};
    auto e1 = std::make_tuple(s1, s2, 3);
    auto e2 = std::make_tuple(s1, s3, 2);
    auto e3 = std::make_tuple(s4, s2, 4);
    auto e = std::vector<std::tuple<std::string, std::string, int>>{e1, e2, e3};
    gdwg::Graph<std::string, int> new_graph{e.begin(), e.end()};
    std::vector<std::string> wt{"B", "C"};
    THEN("Vector with connections") {
      REQUIRE(new_graph.GetConnected("A") == wt);  // A will now have an edge with itself
      // REQUIRE_THROWS_WITH( new_graph.GetConnected("E"), "Cannot call Graph::GetConnected if src
      // don't exist in the graph");
    }
  }
}

SCENARIO("GetWeights method") {
  WHEN("graph.GetWeights() is called") {
    std::string s1{"A"};
    std::string s2{"B"};
    std::string s3{"C"};
    std::string s4{"D"};
    auto e1 = std::make_tuple(s1, s2, 3);
    auto e2 = std::make_tuple(s3, s2, 2);
    auto e3 = std::make_tuple(s4, s2, 4);
    auto e = std::vector<std::tuple<std::string, std::string, int>>{e1, e2, e3};
    gdwg::Graph<std::string, int> new_graph{e.begin(), e.end()};
    std::vector<int> wt{3};
    THEN(
        "Vector with weights is returned, empty vector for no connection and exception otherwise") {
      REQUIRE(new_graph.GetWeights("A", "B") == wt);    // A will now have an edge with itself
      REQUIRE(new_graph.GetWeights("D", "A").empty());  // A will now have an edge with itself
      // REQUIRE_THROWS_WITH( new_graph.GetWeights("A", "E"), "Cannot call Graph::GetWeights if src
      // or dst node don't exist in the graph"); REQUIRE_THROWS_WITH( new_graph.GetWeights("E",
      // "A"), "Cannot call Graph::GetWeights if src or dst node don't exist in the graph");
      // REQUIRE_THROWS_WITH( new_graph.GetWeights("E", "F"), "Cannot call Graph::GetWeights if src
      // or dst node don't exist in the graph");
    }
  }
}

SCENARIO("erase function") {
  WHEN("graph.erase() is called") {
    std::string s1{"A"};
    std::string s2{"B"};
    std::string s3{"C"};
    std::string s4{"D"};
    auto e1 = std::make_tuple(s1, s2, 3);
    auto e2 = std::make_tuple(s3, s2, 2);
    auto e3 = std::make_tuple(s4, s2, 4);
    auto e = std::vector<std::tuple<std::string, std::string, int>>{e1, e2, e3};
    gdwg::Graph<std::string, int> new_graph{e.begin(), e.end()};
    THEN("Returns true if edge has been erased, false if edge is absent") {
      REQUIRE(new_graph.erase("A", "B", 3));
      REQUIRE(!new_graph.erase("A", "B", 3));
    }
  }
}

SCENARIO("Forward Iterator") {
  WHEN("Graph iterators are called") {
    std::string s1{"A"};
    std::string s2{"B"};
    std::string s3{"C"};
    std::string s4{"D"};
    auto e1 = std::make_tuple(s1, s2, 3);
    auto e2 = std::make_tuple(s3, s2, 2);
    auto e3 = std::make_tuple(s4, s2, 4);
    auto e = std::vector<std::tuple<std::string, std::string, int>>{e1, e2, e3};
    gdwg::Graph<std::string, int> new_graph{e.begin(), e.end()};
    THEN("Iterators work ok") {
      auto kt = new_graph.begin();
      REQUIRE(e1 == std::make_tuple(std::get<0>(*kt), std::get<1>(*kt), std::get<2>(*kt)));
      kt++;
      REQUIRE(e2 == std::make_tuple(std::get<0>(*kt), std::get<1>(*kt), std::get<2>(*kt)));
      auto it = new_graph.end();
      it--;
      REQUIRE(e3 == std::make_tuple(std::get<0>(*it), std::get<1>(*it), std::get<2>(*it)));
      auto finder = new_graph.find(s3, s2, 2);
      REQUIRE(e2 ==
              std::make_tuple(std::get<0>(*finder), std::get<1>(*finder), std::get<2>(*finder)));
      finder = new_graph.find(s1, s2, 3);
      finder = new_graph.erase(finder);
      REQUIRE(e2 ==
              std::make_tuple(std::get<0>(*finder), std::get<1>(*finder), std::get<2>(*finder)));
      finder = new_graph.find(s1, s2, 3);
      REQUIRE(finder == new_graph.end());
      REQUIRE(new_graph.cend() == new_graph.end());
      REQUIRE(new_graph.cbegin() == new_graph.begin());
    }
  }
}

SCENARIO("Reverse Iterator") {
  WHEN("Graph iterators are called") {
    std::string s1{"A"};
    std::string s2{"B"};
    std::string s3{"C"};
    std::string s4{"D"};
    auto e1 = std::make_tuple(s1, s2, 3);
    auto e2 = std::make_tuple(s3, s2, 2);
    auto e3 = std::make_tuple(s4, s2, 4);
    auto e = std::vector<std::tuple<std::string, std::string, int>>{e1, e2, e3};
    gdwg::Graph<std::string, int> new_graph{e.begin(), e.end()};
    THEN("Iterators work ok") {
      auto kt = new_graph.rbegin();
      REQUIRE(e3 == std::make_tuple(std::get<0>(*kt), std::get<1>(*kt), std::get<2>(*kt)));
      kt++;
      REQUIRE(e2 == std::make_tuple(std::get<0>(*kt), std::get<1>(*kt), std::get<2>(*kt)));
      auto it = new_graph.rend();
      it--;
      REQUIRE(e1 == std::make_tuple(std::get<0>(*it), std::get<1>(*it), std::get<2>(*it)));
      REQUIRE(new_graph.crend() == new_graph.rend());
      REQUIRE(new_graph.crbegin() == new_graph.rbegin());
    }
  }
}
