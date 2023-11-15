/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbert <humbert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:24:27 by humbert           #+#    #+#             */
/*   Updated: 2023/11/15 16:19:02 by humbert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv)
{
    RPN math_solver;
    int solution;

    if (argc != 2)
    {
        std::cerr << "Error: Arguments" << std::endl;
        return (EXIT_FAILURE);
    }
    if (!math_solver.solve(argv[1], solution))
        return (EXIT_FAILURE);
    std::cout << solution << std::endl;
    return (0);
}
