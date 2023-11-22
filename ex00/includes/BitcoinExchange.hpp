/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:17:06 by humbert           #+#    #+#             */
/*   Updated: 2023/11/22 10:41:00 by luhumber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

# include <map>
# include <ctime>
# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <cstring>
# include <cstdlib>
# include <iomanip>

# define CSV_PATH "data.csv"

class BitcoinExchange {
    private:
        std::map<time_t, float> _exchange_rates;
        
        int     parse_rate(const std::string &path);
        bool    find_rate(struct tm &date_tm, float &rate_found) const;
    public:
        BitcoinExchange(void);
        BitcoinExchange(const BitcoinExchange &);
        BitcoinExchange &operator=(const BitcoinExchange &);
        ~BitcoinExchange(void);

        bool    get_value(const std::string &query, std::string &init_date, std::string &ex_date, std::string &value, float &ex_rate, float &total_value) const;
};

#endif