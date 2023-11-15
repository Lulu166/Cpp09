/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humbert <humbert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:24:37 by humbert           #+#    #+#             */
/*   Updated: 2023/11/15 15:34:47 by humbert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

# include <stack>
# include <iostream>
# include <string>

class RPN {
    private:
        bool    add(std::stack<int> &operands);
        bool    sub(std::stack<int> &operands);
        bool    mul(std::stack<int> &operands);
        bool    div(std::stack<int> &operands);

        bool    exec_operator(char opr, std::stack <int> &solv_stack);

    public:
        RPN(void);
        ~RPN(void);
        RPN(const RPN &);
        RPN &operator=(const RPN &);

        bool    solve(const std::string &ops, int &solution);
};

#endif