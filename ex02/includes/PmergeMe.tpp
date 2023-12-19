#include "PmergeMe.hpp"
#include "utils.tpp"

template <typename T>
T   Merge(T& container)
{
    T   ret;
    T   container1;
    T   container2;

    splitContainer(container, container1, container2);
    if (!(container1.size() < 2 && container2.size() < 2)) {
        container1 = Merge(container1);
        container2 = Merge(container2);
    }
    std::merge(container1.begin(), container1.end(), container2.begin(), container2.end(), std::back_inserter(ret));
    return (ret);
}

template <typename T>
T   Insert(T& max, T min, unsigned int size)
{
    int                         nbInserted = 0;
    std::vector<int>            insertSeq = generateJacobsthalSequence(size);
    std::vector<int>::iterator	itSeq = insertSeq.begin();

    while (itSeq != insertSeq.end())
    {
        int upperBound = nbInserted + *itSeq - 1;
        int lowerBound = 0;
        int middle;
        typename T::iterator    ith = max.begin();

        while (lowerBound + 1 - upperBound < 0)
        {
            middle = (upperBound + lowerBound) / 2;
            if (min[*itSeq - 1] < max[middle])
                upperBound = middle;
            else
                lowerBound = middle;
        }
        if (min[*itSeq - 1] > max[0])
            std::advance(ith, upperBound);
        nbInserted++;
        ith = max.insert(ith, min[*itSeq - 1]);
        ++itSeq;
    }
    if (max[0] < 0)
        max.erase(max.begin());
    return (max);
}

template <typename T, typename U>
T   Sort(char **args)
{
    U   contPair;
    T   contMax;
    T   contMin;

    if (!args[2]) {
        T   ret;

        checkArg(args[1]);
        ret.push_back(std::atoi(args[1]));
        return (ret);
    }

    contPair = fillContainerPairs<U>(args);
    contPair = Merge(contPair);
    splitPairs(contPair, contMax, contMin);
    return (Insert(contMax, contMin, contPair.size()));
}
