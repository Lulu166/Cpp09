/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbert <humbert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:17:14 by humbert           #+#    #+#             */
/*   Updated: 2023/11/15 12:46:47 by humbert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) {
    if (parse_rate(CSV_PATH) < 0)
        throw std::invalid_argument("Failed to load database");
    return ;
}

BitcoinExchange::~BitcoinExchange(void) {
    return ;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy): _exchange_rates(copy._exchange_rates) {
    return ;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &copy) {
    if (this != &copy)
	{
		_exchange_rates.clear();
		_exchange_rates = copy._exchange_rates;
	}
	return (*this);
}

void    time_date_str(const struct tm &time, std::string &date_str) {
    std::ostringstream  os;
    std::string         valid_date;

    os << std::put_time(&time, "%Y-%m-%d");
    date_str = os.str();
}

bool    valid_date_str(const std::string &date_str, struct tm &ref_date) {
    std::ostringstream  os;
    std::string         valid_date;
    time_t              time = mktime(&ref_date);
    struct tm           *tmp_time;

    tmp_time = std::localtime(&time);
    time_date_str(*tmp_time, valid_date);
    if (date_str != valid_date)
        return (false);
    ref_date = *tmp_time;
    return (true);
}

bool    valid_amount_float(float value) {
    if (value < 0.0f) {
        std::cerr << "Error: not a positive number" << std::endl;
        return (false);
    }
    else if (value > 1000.0f) {
        std::cerr << "Error: too large number" << std::endl;
        return (false);
    }
    return (true);
}

int BitcoinExchange::parse_rate(const std::string &path) {
    std::ifstream   csv_file;
    std::string     line;
    std::string     date_str;
    std::string     amount_str;
    size_t          pos;
    struct tm       date;
    time_t          time;
    float           ex_rate;

    csv_file.open(path, std::ios::in);
    if (!csv_file.is_open())
        return (-1);
    if (!std::getline(csv_file, line, '\n').good()) {
        std::cerr << "Failed to read history" << std::endl;
        return (-1);
    }

    while (!std::getline(csv_file, line, '\n').fail()) {
        pos = line.find(',');
        date_str = line.substr(0, pos);
        amount_str = line.substr(pos + 1, line.length() - pos);

        // Initialiser structure de temps avec date et strptime pour convertir la date de chaîne en struct tm
        std::memset(&date, 0, sizeof(date));
        if (strptime(date_str.c_str(), "%Y-%m-%d", &date) == NULL
            || !valid_date_str(date_str, date))
        {
                std::cerr << "Error: Invalid date" << date_str << std::endl;
                continue ;
        }
        // Convertir structure temps en time_t et Convertir chaîne de taux en float
        time = mktime(&date);
        try {
            ex_rate = std::stof(amount_str);
        }
        catch (std::exception &e) {
            std::cerr << "Error: Failed to convert exchange rate to float" << std::endl;
            continue ;
        }
        // Stocker taux dans le conteneur
        _exchange_rates[time] = ex_rate;
    }
    csv_file.close();
    return (0);
}

bool    BitcoinExchange::find_rate(struct tm &date, float &rate_found) const {
    std::map<time_t, float>::const_iterator it;
    time_t  q_time;
    time_t  time;

    // Obtenir première date supérieure ou égale à q_time
    q_time = mktime(&date);
    it = _exchange_rates.lower_bound(q_time);
    time = it->first;
    
    // Si date exacte pas trouvée, revenir date précédente
    if (time != q_time && it != _exchange_rates.begin())
        time = (--it)->first;
    
    // Mettre à jour structure temps avec date trouvée
    date = *std::localtime(&time);
    rate_found = it->second;
    return (true);
}

bool    BitcoinExchange::get_value(const std::string &query,
    std::string &init_date, std::string &ex_date, std::string &value,
    float &ex_rate, float &total_value) const
{
    size_t      pos;
    std::string amount_str;
    struct tm   date_tm;
    float       amount;

    std::memset(&date_tm, 0, sizeof(date_tm));
    ex_date = "";
    value = "";
    ex_rate = 0;
    total_value = 0;

    // Extraction de la date initiale depuis la requête
    pos = query.find_first_of(' ');
    if (pos == query.npos)
        pos = query.length();
    init_date = query.substr(0, pos);
    
    // Conversion de la date initiale en struct tm
    if (strptime(init_date.c_str(), "%Y-%m-%d", &date_tm) == NULL
        || !valid_date_str(init_date, date_tm))
    {
        std::cerr << "Error: bad input => " << init_date << std::endl;
        return (false);
    }

    // Extraction de la partie de la requête après la date
    pos = query.find_first_not_of(" |", pos);
    amount_str = query.substr(pos);
    // Conversion chaîne du montant en un nombre à virgule flottante
    try {
        amount = std::stof(amount_str);
    }
    catch (std::exception &e) {
        std::cerr << "Error: Failed to convert exchange rate to float" << std::endl;
        return (false);
    }
    if (!valid_amount_float(amount) || !find_rate(date_tm, ex_rate))
        return (false);
    time_date_str(date_tm, ex_date);
    value = amount_str;
    total_value = amount * ex_rate;
    return (true);
}
