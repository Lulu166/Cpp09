/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbert <humbert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:26:12 by humbert           #+#    #+#             */
/*   Updated: 2023/11/20 00:19:51 by humbert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

//PRINT 5 ELEMENTS DU VECTEUR
void    print_vector(std::vector<int> vec) {
    std::vector<int>::iterator  it;
    int                         i = 0;

    for (it = vec.begin(); it != vec.end(); it++) {
        if (i++ > 4)
            break ;
        std::cout << *it << " ";
    }
    if (it != vec.end())
        std::cout << "[...]";
    std::cout << std::endl;
}

//TRIE VECTEUR PAR INSERTION
std::vector<int>    insertionSort_vector(std::vector<int> vec) {
    int key;
    int j;
    for (size_t i = 1; i < vec.size(); i++) {
        key = vec[i];
        j = i - 1;
        while (j >= 0 && vec[j] > key) {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = key;
    }
    return (vec);
}

//TRIE DEQEU PAR INSERTION
std::deque<int>     insertionSort_deque(std::deque<int> deq) {
    int key;
    int j;
    for (size_t i = 1; i < deq.size(); i++) {
        key = deq[i];
        j = i - 1;
        while (j >= 0 && deq[j] > key) {
            deq[j + 1] = deq[j];
            j--;
        }
        deq[j + 1] = key;
    }
    return (deq);
}

//PRINT 5 ELEMENTS DU DEQUE
void    print_deque(std::deque<int> deq) {
    std::deque<int>::iterator   it;
    int                         i = 0;

    for (it = deq.begin(); it != deq.end(); it++) {
        if (i++ > 4)
            break ;
        std::cout << *it << " ";
    }
    if (it != deq.end())
        std::cout << "[...]";
    std::cout << std::endl;
}

//ALGO
bool    PmergeMe(char **argv) {
    std::vector<int>    vec;
    std::vector<int>    sorted_vec;
    std::deque<int>     deq;
    std::deque<int>     sorted_deq;
    std::string         str;
    long                number;
    clock_t             start_vec, end_vec;
    clock_t             start_deq, end_deq;

    //Parcours args et verifie int
    for (int j = 1; argv[j]; j++) {
        for (int i = 0; argv[j][i]; i++) {
            if (!std::isdigit(argv[j][i])) {
                if (argv[j][i] == '-')
                    return (std::cout << "Error: negative integer" << std::endl, false);
                return (std::cout << "Error: non digit character" << std::endl, true);
            }
        }
        //Conversion char to int
        number = std::strtol(argv[j], NULL, 10);
        str = argv[j];
        if (number > 2147483647 || str.size() > 10)
            return (std::cout << "Error: overflow" << std::endl, false);
        //Ajout au vec et deque
        vec.push_back(number);
        deq.push_back(number);
    }
    //Affiche contenu initial vec
    std::cout << "Before: ";
    print_vector(vec);

    //Mesure temps de tri vec 
    start_vec = clock();
    sorted_vec = insertionSort_vector(vec);
    end_vec = clock();
    long micro_vec = ((double)end_vec - (double)start_vec) / CLOCKS_PER_SEC * 1000000;
    std::cout << "After: ";
    print_vector(sorted_vec);

    //Mesure temps de tri deque
    start_deq = clock();
    sorted_deq = insertionSort_deque(deq);
    end_deq = clock();
    long micro_deq = ((double)end_deq - (double)start_deq) / CLOCKS_PER_SEC * 1000000;

    //Affiche temps traitement vec et deque
    std::cout << "Time to process a range of " << vec.size() \
    << " elements with std::vector : " << micro_vec << "µs" << std::endl;
    std::cout << "Time to process a range of " << deq.size() \
    << " elements with std::deque : " << micro_deq << "µs" << std::endl;
    return (true);
}
