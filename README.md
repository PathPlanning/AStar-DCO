# AStar-DCO

The basic implementation of A* algorithm with the possibility of using different containers for the Open set

## Description

The project contains implementations of following sructures:

1. List - container that represents a countable number of ordered elements. Implemented using `std::list`
2. Array of lists - array that containes a number of lists. Implemented using `std::vector<std::list>`
3. Set - container that represents a countable number of unordered elements without repeating the equivalent elements. Implemented using `std::set`
4. Array of sets - the same as array of lists, but with sets. Implemented using `std::vector<std::set>`
5. Priority queue - container that represents regular queue, but every element has a "priority" that makes it quicker to choose the most suitable element. Implemented using `std::priority_queue`
6. Array of priority queues - the same as array of lists, but with priority queue. Implemented using `std::vector<std::priority_queue>`.

There is also a possibility to keep duplicates in structures 1 - 4.

## Build and Launch

To build the project you can use CMake, CMakeLists file is available in the repo. For more details about building, see Build and Launch section of [AStar-JPS-ThetaStar repository](https://github.com/PathPlanning/AStar-JPS-ThetaStar). To run the compiled file and get a result you need to pass a correct input XML-file as the first (command line) argument. To run test on empty map you need to pass word `fakemap` as second (command line) argument. In this case `<grid>` statement of XML-file will be ignored.

## Input and Output files

Both files are an XML file with a specific structure. 
Input file should contain:

* Mandatory tag `<map>`. It describes the environment.
    * `<height>` and `<width>` - mandatory tags that define size of the map. Origin is in the upper left corner. (0,0) - is upper left, (*width*-1, *height*-1) is lower right.
    * `<startx>` and `<starty>` - mandatory tags that define horizontal (X) and vertical (Y) offset of the start location from the upper left corner. Legal values for *startx* are [0, .., *width*-1], for *starty* - [0, .., *height*-1].
    * `<finishx>` and `<finishy>` - mandatory tags that horizontal (X) and vertical (Y) offset of the goal location.
    * `<grid>` - mandatory tag that describes the square grid constituting the map. It consists of `<row>` tags. Each `<row>` contains a sequence of "0" and "1" separated by blanks. "0" stands for traversable cell, "1" - for untraversable (actually any other figure but "0" can be used instead of "1").
    * `<cellsize>` - optional tag that defines the size of one cell. One might add it to calculate scaled length of the path.
    * `<title>`, `<URL>`, `<coordinates>`, etc - optional tags containing additional information on the map.

* Mandatory tag `<algorithm>`. It describes the parameters of the algorithm.

    * `<metrictype>` - defines the type of metric for heuristic function. Possible values - "euclidean", "diagonal", "manhattan", "chebyshev". Default value is "euclidean".
    * `<hweight>` - defines the weight of heuristic function. Default value is "1".
    * `<allowdiagonal>` - boolean tag that defines the possibility to make diagonal moves. Setting it to "false" restricts agent to make cardinal (horizonal, vertical) moves only. Default value is "true".
    * `<cutcorners>` - boolean tag that defines the possibilty to make diagonal moves when one adjacent cell is untraversable. The tag is ignored if diagonal moves are not allowed. Default value is "false".
    * `<allowsqueeze>` - boolean tag that defines the possibility to make diagonal moves when both adjacent cells are untraversable. The tag is ignored if cutting corners is not allowed. Default value is "false".
* Optional tag `<openstructure>`. It describe the container of Open set.
    * `<type>` -  defines the type of container. Possible values - "list", "vectoroflists", "set",  "vectorofsets", "priorityqueue", "vectorofpriorityqueues". Default value is "vectoroflists".
    * `<duplicate>` - boolean tag that defines the availability of duplicates in Open. Defult value is "true".
* Optional tag `<options>`. Options that are not related to search.

    * `<loglevel>` - defines the level of detalization of log-file. Default value is "1". Possible values:
        - "0" or "none" - log-file is not created.
        - "0.5" or "tiny" - All the input data is copied to the log-file plus short `<summary>` is appended. `<summary>` contains info of the path length, number of steps, elapsed time, etc.
        - "1" or "short" - *0.5*-log plus `<path>` is appended. It looks like `<grid>` but cells forming the path are marked by "\*" instead of "0". The following tags are also appended: `<hplevel>` and `<lplevel>`. `<lplevel>` is the sequence of coordinates of cells forming the path. `<hplevel>` is the sequence of sections forming the path.
    * `<logpath>` - defines the directory where the log-file should be written. If not specified directory of the input file is used. 
    * `<logname>` - defines the name of log-file. If not specified the name of the log file is: "input file name"+"_log"+input file extension.

The main tag in Output file, which containes path length, memory and time:

```xml
<summary numberofsteps="107" nodescreated="127" length="15.414213" length_scaled="41.618375587463383" time="0.000512" astar_length="15.414213" astar_correct="1"/>
```

* _"numberofsteps"_ stands for the number of iterations (number of expanded vertices)
* _"nodescreated"_  stands for the number of nodes that were examined in general (= memory)
* _"length"_ stands for length of the final path
* _"length_scaled"_ stands for actual length counting the size of cell in map
* _"time"_ stands for elapsed time
