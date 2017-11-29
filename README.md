# [CISC 4080: Algorithms](http://www.dsm.fordham.edu/~eschomburg/algorithms/)

## Homework 5
**Due Tuesday, November 7**

These files contains C++ code and two text files
specifying graphs, one for testing purposes, the other to
answer the actual question:

*   The [`hw5_skel.h`](hw5_skel.h) header file defines several classes and
    functions to be used in the [`hw5_skel.cpp`](hw5_skel.cpp) file. You
    should use these in your implementations in a `hw5.cpp` file.
    Complete the marked code blocks (interfaces are, for the most
    part, already defined in the skeleton code for you). You can
    test your code by running the compiled executable with no
    arguments. If you provide one argument, it will run the same
    code on the file specified by the argument. If you provide two
    arguments, the `verbose` graph information and path distance
    matrix will not be printed to the command line, with the matrix
    instead being written to a file at the location specified by
    the second argument.

*   Once you have completed and tested your implementation, use it
    to label and count the components in the (undirected) egonet
    graph. This is one of the data files from [a kaggle competition
    focusing on the analysis and modeling of
    social networks](https://www.kaggle.com/c/learning-social-circles).
    Answer/complete the following questions/tasks:

    1.  How many components are in the egonet graph?

    1.  What are the minimum, maximum, mean, and median number
        of connections for each user (vertex) in the graph?

    1.  What are the minimum, maximum, mean, and median path
        distances between user pairs in the graph (not counting
        "infinite" distances, i.e., users in different graph
        components).


# 

If you are running Windows and do not already know how to compile and execute
C++, the following might be helpful:
https://cs.calvin.edu/courses/cs/112/resources/installingEclipse/cygwin/.

You should utilize resources online, such as http://www.cplusplus.com/reference/,
if you aren't familiar with some of the C++ classes and data structures
used here.

Email your code, answers, and the path distance matrix output file to
me (![eschomburg STRUDEL fordham.edu](email.png)) by midnight on the due date,
and please email me for questions and clarifications before then.