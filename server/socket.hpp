/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:13:17 by aqadil            #+#    #+#             */
/*   Updated: 2023/02/21 00:43:27 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "../general_info.hpp"


class DIY_socket
{
private:
    int socket_FD;
    struct sockaddr_in address_sk;
    int address_sk_len;

public:
    DIY_socket();
    ~DIY_socket();
    int Launch_sk(int port, std::string host);
    void Bind_sk(int port, std::string interface);
    int listen_sk();
    void test_cnx_sk(int test);
    int get_sk() const;
    struct sockaddr_in get_adr_sk() const;
};

#endif