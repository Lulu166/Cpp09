/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbert <humbert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:16:52 by humbert           #+#    #+#             */
/*   Updated: 2023/11/15 10:53:54 by humbert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int clean_exit(const std::string &msg, std::fstream &file, int status) {
    if (!msg.empty())
        std::cerr << msg << std::endl;
    if (file.is_open())
        file.close();
    return (status);
}

int main(int argc, char **argv)
{
    BitcoinExchange btc;
    std::fstream    file;
    std::string     query, init_data, ex_date, value;
    float           ex_rate, total_value;

    if (argc < 2)
        return (clean_exit("Error: Missing file", file, EXIT_FAILURE));
    file.open(argv[1], std::ios::in);
    if (!file.is_open())
        return (clean_exit("Error: Failed to open file", file, EXIT_FAILURE));
    
    while (!std::getline(file, query, '\n').fail())
    {
        if (query == "date | value")
            continue ;
        if (!btc.get_value(query, init_data, ex_date, value, ex_rate, total_value))
            continue ;
        std::cout << init_data << " => " << value << " = " << total_value << std::endl;
    }
    file.close();
    return (0);
}
