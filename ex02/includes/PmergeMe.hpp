#ifndef PMERGEME_HPP
#define PMERGEME_HPP

# include <iostream>
# include <sstream>
# include <string>
# include <deque>
# include <vector>
# include <cstdlib>
# include <ctime>
# include <sys/time.h>
# include <utility>
# include <iterator>
# include <algorithm>

void                checkArg(const std::string& arg);
int                 getTime(struct timeval startTime);
std::vector<int>    generateJacobsthalSequence(int n);
std::vector<int>	TestSort(char **args);

#include "PmergeMe.tpp"
//#include "utils.tpp"

#endif