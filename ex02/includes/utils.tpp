#include "PmergeMe.hpp"

template <typename T>
void    printContainer(T& container, std::string type)
{
    typename T::iterator    it;

    std::cout << type << ": ";
    for (it = container.begin(); it != container.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

template <typename T>
void    splitContainer(T& container1, T& container2, T& container3)
{
    typename    T::iterator it;
    int                     i = 0;
    int                     lenght = container1.size();

    for (it = container1.begin(); it != container1.end(); ++it)
    {
        if (i < lenght / 2)
            container2.push_back(*it);
        else
            container3.push_back(*it);
        i++;
    }
}

template <typename T, typename U>
void    splitPairs(T& container, U& max, U& min)
{
    typename T::iterator    it;

    for (it = container.begin(); it != container.end(); ++it) {
        max.push_back(it->first);
        min.push_back(it->second);
    }
}

template <typename T>
void    isSort(T& container)
{
    int i = 1;

    while (i < static_cast<int>(container.size()))
    {
        if (container[i] < container[i - 1]) {
            std::cout << "Sort Error ici" << std::endl;
            throw std::exception();
        }
        i++;
    }
}

template <typename T>
T   fillContainerPairs(char **args)
{
    T   container;
    int i = 1;

    while (args[i])
    {
        checkArg(args[i]);
        if (args[++i])
        {
            checkArg(args[i]);
            if (std::atoi(args[i]) > std::atoi(args[i - 1]))
                container.push_back(std::make_pair(std::atoi(args[i]), std::atoi(args[i - 1])));
            else
                container.push_back(std::make_pair(std::atoi(args[i - 1]), std::atoi(args[i])));
        }
        else {
            container.push_back(std::make_pair(std::atoi(args[i - 1]), -1));
            break ;
        }
        i++;
    }
    return (container);
}
