/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_info.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:12:09 by aqadil            #+#    #+#             */
/*   Updated: 2023/02/21 00:43:27 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_INFO
#define GENERAL_INFO

#include <exception>
#include <stdexcept>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <arpa/inet.h>
#include <cstdio>
#include <dirent.h>
#include <cstdlib>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/poll.h>
#include <fcntl.h>
#include <fstream>
#include <limits.h>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <cstring>

#include "./server/requestData.hpp"
#include "./parser/parser.hpp"
#include "./request_response/request_response.hpp"
#include "./server/socket.hpp"
#include "./server/server.hpp"

#define BUFFSIZE 3000
#endif