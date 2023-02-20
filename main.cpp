/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 14:58:34 by aqadil            #+#    #+#             */
/*   Updated: 2023/02/21 00:42:16 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "general_info.hpp"

int main(int ac, char **av, char **env) {
    
    if (ac > 2) {
        
        std::cerr << "Too many arguments\n";
        return 1;
    }
    try
    {
        std::vector<Config> servers;
        if (ac == 2)
            servers = descentParser(av[1]);
        else
            servers = descentParser("./webserv.conf");
        DIY_server sv(servers);
        sv.env = env;
        sv.launch_serv();
    }
    catch(const std::exception& e)
    {  
        std::cerr << e.what() << '\n';   
    }
}