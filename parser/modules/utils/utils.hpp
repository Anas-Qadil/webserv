/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 10:18:53 by aqadil            #+#    #+#             */
/*   Updated: 2023/01/08 10:18:54 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#pragma once

#include <iostream>
#include <vector>
#include <fstream>

const std::string readFile(std::string path);
void analyze(std::string &content);
void formatLine(std::string &line);
int checkBrackets(std::string content);
void generaleCheck(std::string countent);
void generaleFormat(std::string &content);