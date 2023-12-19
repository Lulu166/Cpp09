#include "../includes/PmergeMe.hpp"

int main(int argc, char **argv)
{
    std::vector<int>    vec;
    std::deque<int>     deq;

    if (argc < 2) {
        std::cerr << "Not enought parameters" << std::endl;
        return (-1);
    }


    struct timeval  startTime;
    int             endTime;

    if (gettimeofday(&startTime, NULL) < 0)
        return (-1);
    try {
        vec = Sort<std::vector <int>, std::vector<std::pair<int, int> > >(argv);
    }
    catch (std::exception& e) {
        std::cerr << "Error: only positive figures" << std::endl;
        return (-1);
    }
    endTime = getTime(startTime);
    if (endTime < 0)
        return (-1);
    try {
        isSort(vec);
    }
    catch (std::exception& e) {
        std::cout << "Error: vector is not sorted" << std::endl;
        return (-1);
    }
    printContainer(vec, "Vector");
    std::cout << "Time to sort vector: " << endTime << std::endl;



    if (gettimeofday(&startTime, NULL) < 0)
        return (-1);
    try {
        deq = Sort<std::deque<int>, std::deque<std::pair<int, int> > >(argv);
    }
    catch (std::exception& e) {
        std::cerr << "Error: only positive figures" << std::endl;
        return (-1);
    }
    endTime = getTime(startTime);
    if (endTime < 0)
        return (-1);
    try {
        isSort(deq);
    }
    catch (std::exception& e) {
        std::cout << "Error: deque is not sorted" << std::endl;
        return (-1);
    }
    printContainer(deq, "Deque");
    std::cout << "Time to sort deque: " << endTime << std::endl;
}