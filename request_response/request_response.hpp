/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_response.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:30:08 by aqadil            #+#    #+#             */
/*   Updated: 2023/02/21 00:43:27 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <iostream>
# include <string>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <fstream>
# include <unistd.h>
# include <cstdlib>
# include <map>
# include <vector>
# include <dirent.h>

# define CRLF "\r\n"
# define CRLF2 "\r\n\r\n"
# define WHITESPACE " \f\n\r\t\v"
# define AUTO_INDEX_FORM "<!DOCTYPE html>\n<html lang=\"en\">\n<style> @import url('https://fonts.googleapis.com/css2?family=Inter:wght@400;600;700&family=Montserrat:wght@500&display=swap'); * {		font-size:20px; } ul { 	border-top: solid black 1px; 	border-bottom: solid black 1px; 	margin:50px; 	padding:150px;} li{ 	list-style:none; 	margin:30px; } li a{ 	text-decoration:none; 	color:black; } li { 	display: flex; } img {   width:25px;    height: 25px;   margin-right: 5px; }</style>\n<head>\n	<meta charset =\"UTF-8\">\n	<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n	<script src=\"https://kit.fontawesome.com/cb1896687a.js\" crossorigin=\"anonymous\"></script>\n	<title>Root</title>\n</head>\n<body>\n<ul> "

# include "../parser/parser.hpp"
std::string chunked_decoder(std::string content);
char	*ft_itoa(int n);

class manage_RR {
	public :
		int									server_num__;
	public :
		std::vector<Config>					info;
		char **env;
		std::map<std::string, std::string>	content;
		std::string							STATUE__;
		std::string							STATUE__DESCRIPTION__;
		int									Respond_body_length;
		std::map<std::string, std::string>	Server_data__;
		bool								ERROR__;
		std::string							CGI_BIN;
		std::FILE							*IN_FILE;
		std::FILE							*OUT_FILE;
		int									IN_FD;
		int									OUT_FD;
		bool								CGI;
		std::string							New_Headers;
		manage_RR() {};
		manage_RR(std::string, std::vector<Config>, char **env);
		// void		operator = (manage_RR);
		bool		check_cgi(std::string);
		void		request_line();
		int			headers();
		int			request_line_checker();
		std::string	respond_generator();
		std::string	get_res();
		std::string	get_respond_statue_line();
		int			get_the_server();
		std::string	get_respond_body();
		std::string	CGI_request(std::string, std::string, char **, std::string);
		char		**get_CGI_informations(std::string, char **, std::string);
		void		add_CGI_headers(char **);
		void		creat_input_file(std::string&);
		char		*get_file_name(std::string, int);
		bool		check_auto_index(std::string&, std::string&);
		std::string	get_new_URI(std::string, bool&);
		std::string	get_dir_name(std::string&);
		void		get_the_body(int , std::string&, std::string&);
		void		read_the_dir(DIR *, std::string &);
		std::string	getAutoIndexBody(std::string);
		bool		Setup_CGI_STDIN_STDOUT(std::string &, std::string &);
		bool		check_redirection();
		std::string	get_cgi_response(std::string &body);
		std::string	redirection();
		std::string	get_error_file();
		std::string	get_delete_URI(std::string URI__);
};
