# COMP6771
List of my C++ projects worked on during COMP6771 - Advanced C++ Programming

Dynamic Graph
Implementation for a Generic Directed Weighted graph (GDWG) with value-like semantics in C++. Both the data stored at a node and the weight stored at an edge will be of generic types. Both generic types may be different. For example, here is a graph with nodes storing std::string and edges weighted by int:

gdwg::Graph<std::string,int> g;

Formally, this directed weighted graph G=(N,E) will consist of a set of nodes N and a set of weighted edges E. All nodes in the graph are unique. Between any two nodes (or a node and itself), all edges must be unique.

The implementation includes constructors, destructors, operator overloads, methods as well as a custom iterator for iterating over the graph.

Euclidean Vector
Implementation for a Euclidean Vector Class Library in C++. Includes constructors, operator overloads and friend functions.

Word Ladder
Implementation for a program that builds word ladders.

A word ladder is a connection from one word to another word formed by changing one letter at a time with the constraint that at each step the sequence of letters still forms a valid word. For example, here is a word ladder connecting "code" to "data":

code -> cade -> cate -> date -> data

The user enters a start and a destination word after which the program finds the shortest word ladder(s) between them if they exist.

Here is some sample output of the word ladder program:

Enter start word (RETURN to quit): work
Enter destination word: play
Found ladder: work fork form foam flam flay play
work pork perk peak pean plan play
work pork perk peak peat plat play
work pork perk pert peat plat play
work pork porn pirn pian plan play
work pork port pert peat plat play
work word wood pood plod ploy play
work worm form foam flam flay play
work worn porn pirn pian plan play
work wort bort boat blat plat play
work wort port pert peat plat play
work wort wert pert peat plat play

Finding a word ladder is a specific instance of the shortest path problem, where the challenge is to find the shortest path from a starting position to a goal. Shortest path problems come up in a variety of situations such as packet routing, robot motion planning, social networks, studying gene mutations, and more. One approach for finding a shortest path is the classic algorithm known as breadth-first search. A breadth-first search searches outward from the start in a radial fashion until it hits the goal. For word ladder, this means first examining those ladders that represent “one hop” (i.e. one changed letter) from the start. If any of these reaches the destination, we’re done. If not, the search now examines all ladders that add one more hop (i.e. two changed letters). By expanding the search at each step, all one-hop ladders are examined before two-hops, and three-hop ladders only considered if none of the one-hop nor two-hop ladders worked out, thus the algorithm is guaranteed to find the shortest successful ladder.

Breadth-first is typically implemented using a queue. The queue is used to store partial ladders that represent possibilities to explore. The ladders are enqueued in order of increasing length. The first elements enqueued are all the one-hop ladders, followed by the two-hop ladders, and so on. Due to FIFO handling, ladders will be dequeued in order of increasing length. The algorithm operates by dequeueing the front ladder from the queue and determining if it reaches the goal. If it does, you have a complete ladder, and it is the shortest. If not, you take that partial ladder and extend it to reach words that are one more hop away, and enqueue those extended ladders onto the queue to be examined later. If you exhaust the queue of possibilities without having found a completed ladder, you can conclude that no ladder exists.

Another subtle issue is the restriction that you may not re-use words that have been included in a previous (and shorter) ladder. This is an optimization that avoids exploring redundant paths. For example, if you have previously tried the ladder cat -> cot -> cog and are now processing cat -> cot -> con, you would find the word cog one letter away from con, so cog looks like a potential candidate to extend this ladder. However, cog has already been reached in an earlier and shorter ladder, and there is no point in re-considering it in a longer ladder.
