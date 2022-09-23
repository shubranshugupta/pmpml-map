# Pune PMPML Bus APP

This is a simple C++ program that will the source bus stop and the destination bus stop, of Pune PMPML, from the user and display the time, distance and shortest route to reach the destination. All the information about but stops are read from pmpml.csv file. We can also add or delete bus stops to the file.

It is implemented using [Graph](https://en.wikipedia.org/wiki/Graph_(abstract_data_type)) data structures. The graph has nodes and edges. Nodes represent a bus stops that will be containing the name. Edges (the connection between two nodes) represent the distance between the two bus stops and the average time to reach other end.

It uses [Dijkstra's algorithm](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm), to find the shortest path between the source bus stop and the destination bus stop. Finally, route between the two stations, total distance and time are displayed.

## Sample Image

![Sample Image]()

## How to use it?

### Direct Compilation

```bash
git clone https://github.com/shubranshugupta/pmpml-map.git

cd pmpml-map

g++ -o pmpml.exe pmpml.cpp

./pmpml.exe
```

### Using Make

**Note:** Make sure you have [Make](https://www.gnu.org/software/make/) installed.

```bash
git clone https://github.com/shubranshugupta/pmpml-map.git

cd pmpml-map

make
```
