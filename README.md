# Data-analysis

This is a set of programs useful in general data analysis

# Histogram
There are two versions of this program:

* Version 1. It acts assuming that the cv's are correct and do not need reweighting. In this case the program calculates the histogram. Once the histogram is calculated it also calculates different statistical measures.

* Version 2. It acts over the result of a reweighting. I does not calculate the histogram as it is given. The main function of this program version is to deal with the graphical representation of the reweighted data. tipicaly the data comes as:

CV1 CV2 Probability

Program to preform histogram analysis over a set of continuous real data. It detects the minimum and maximum values of the data set. The number of bins must be provided. Fast run:
g++ code.cpp -o histogram
./histogram [FileToAnalize] -bins [N]

# Draw frames
