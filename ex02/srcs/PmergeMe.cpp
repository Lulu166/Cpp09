#include "../includes/PmergeMe.hpp"

void checkArg(const std::string& arg)
{
    for (std::size_t i = 0; i < arg.size(); ++i) {
        if (!isdigit(arg[i]))
            throw std::exception();
    }

    char* endptr;
    long i = strtol(arg.c_str(), &endptr, 10);

    if (*endptr != '\0' || i < 0)
        throw std::exception();
}

int getTime(struct timeval startTime)
{
    int             time;
    struct timeval  tv;

    // Stocke l'heure actuelle dans struct tv
    if (gettimeofday(&tv, NULL) < 0)
        return (-1);

    // Calcule temps écoulé (ms) depuis startTime
    time = (tv.tv_sec - startTime.tv_sec) * 1000000 + (tv.tv_usec - startTime.tv_usec);

    return (time);
}

std::vector<int> generateJacobsthalSequence(int n)
{
    std::vector<int> vec;

    // Génère suite jusqu'à n
    for (int i = 1, prev = 0, next = 1; next < n; ++i)
    {
        vec.push_back(prev + 2 * next);

        int temp = next;
        next = prev + 2 * next;
        prev = temp;
    }

    return (vec);
}
