/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_response.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:37:12 by aqadil            #+#    #+#             */
/*   Updated: 2023/02/21 00:43:27 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "request_response.hpp"

std::string	substr_s(std::string str, size_t f, size_t l) {
	try {
		return str.substr(f, l);
	}
	catch (std::exception &e) {
		std::cout << "error in substr" << std::endl;
		return ("");
	}
	return "";
}

void	free_2(char **str) {
	for (size_t i = 0; str[i]; i++)
		free (str[i]);
	delete [] str;
}

std::string	get(std::string &client_content, size_t index, size_t len, size_t er) {
	std::string tmp;

	tmp = substr_s(client_content, index, len);
	client_content.erase(0, len + er);
	return tmp;
}

size_t	get_header_end(std::string Header__) {
	for (size_t i = -1; i < Header__.length();) {
		i = Header__.find('\n', i + 1);
		if (i == 0)
			return 0;
		else if (i == Header__.npos)
			return i;
		else if (i != Header__.npos && Header__[i - 1] != '\r')
			return i;
	}
	return 0;
}

void	erase_from_beg_end(std::string &str, char c, int case_) {
	if (case_ == 1) {
		if (str.empty())
			return ;
		if (str[0] == c)
			str.erase(0, 1);
		if (str.empty())
			return ;
		if (str[str.length() - 1] == c)
			str.erase(str.length() - 1, 1);
	}
}

std::string	manage_RR::get_respond_statue_line() {
	std::string	statue_line;

	statue_line = "HTTP/1.1 " + STATUE__ + " " + STATUE__DESCRIPTION__ + CRLF;	
	return statue_line;
}

std::string get_response_type(std::string URI__) {

	std::string	types[54] = {"jpg", "EDI-X12", "EDIFACT", "javascript", "octet-stream", "ogg", "pdf", "xhtml+xml", "x-shockwave-flash", "json", "ld+json", "xml", "zip", "x-www-form-urlencoded", "mpeg", "x-ms-wma", "vnd.rn-realaudio", "x-wav", "gif", "jpeg", "png", "tiff", "vnd.microsoft.icon", "x-icon", "vnd.djvu", "svg+xml", "mixed", "alternative", "related", "form-data", "css", "csv", "html", "javascript", "plain", "xml", "mpeg", "mp4", "quicktime", "x-ms-wmv", "x-msvideo", "x-flv", "webm", "vnd.oasis.opendocument.text", "vnd.oasis.opendocument.spreadsheet", "vnd.oasis.opendocument.presentation", "vnd.oasis.opendocument.graphics", "vnd.ms-excel", "vnd.openxmlformats-officedocument.spreadsheetml.sheet", "vnd.ms-powerpoint", "vnd.openxmlformats-officedocument.presentationml.presentation", "msword", "vnd.openxmlformats-officedocument.wordprocessingml.document", "vnd.mozilla.xul+xml"};
	std::string	fill_type[54] = {"image/jpeg", "application/EDI-X12", "application/EDIFACT", "application/javascript", "application/octet-stream", "application/ogg", "application/pdf", "application/xhtml+xml", "application/x-shockwave-flash", "application/json", "application/ld+json", "application/xml", "application/zip", "application/x-www-form-urlencoded", "audio/mpeg", "audio/x-ms-wma", "audio/vnd.rn-realaudio", "audio/x-wav", "image/gif", "image/jpeg", "image/png", "image/tiff", "image/vnd.microsoft.icon", "image/x-icon", "image/vnd.djvu", "image/svg+xml", "multipart/mixed", "multipart/alternative", "multipart/related (using by MHTML (HTML mail).)", "multipart/form-data", "text/css", "text/csv", "text/html", "text/javascript (obsolete)", "text/plain", "text/xml", "video/mpeg", "video/mp4", "video/quicktime", "video/x-ms-wmv", "video/x-msvideo", "video/x-flv", "video/webm", "application/vnd.oasis.opendocument.text", "application/vnd.oasis.opendocument.spreadsheet", "application/vnd.oasis.opendocument.presentation", "application/vnd.oasis.opendocument.graphics", "application/vnd.ms-excel", "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet", "application/vnd.ms-powerpoint", "application/vnd.openxmlformats-officedocument.presentationml.presentation", "application/msword", "application/vnd.openxmlformats-officedocument.wordprocessingml.document", "application/vnd.mozilla.xul+xml"};
	for (size_t i = 0; i != 54; i++) {
		if (URI__.find(types[i], URI__.length() - strlen(types[i].c_str() - 1)) != URI__.npos)
			return "Content-Type: " + fill_type[i]; 
	}
	return "Content-Type: text/html";
}

std::string get_respond_headers(std::string URI__, bool ERROR__, std::string Method__) {
	std::string Headers;

	Headers = "Content-Length: ";
	if (ERROR__)
		Headers.append(std::string() + CRLF + "Content-Type: " + "text/html");
	else if (Method__ != "DELETE")
		Headers.append(CRLF + get_response_type(URI__));
	Headers.append(CRLF2);
 	return Headers;
}

std::vector<std::string>	separate_body(std::string &body__, std::string &boundary) {
	std::vector<std::string> sep_body;

	size_t index = body__.find("--" + boundary);
	for (size_t i = 0; true; i++) {
		sep_body.push_back(substr_s(body__, index, body__.find("--" + boundary, index + 1) - index));
		if (sep_body[i].find(boundary + "--") != body__.npos) {
			sep_body.pop_back();
			break ;
		}
		index = body__.find("--" + boundary, index + 1);
	}
	return sep_body;
}

std::string	get_random_name(std::string add) {
	static int tmp;
	
	srand((unsigned) time(NULL));
	if (!tmp)
		tmp = rand();
	return std::to_string(tmp++) + "." + add;
}

char **add_query_string(char **CGI_env, char **env__, std::string query__) {
	size_t		len = 1;
	size_t		tmp;
	size_t		index = 0;

	while (env__[index])
		index++;
	for (size_t i = 0; i != query__.length(); i++) {
		if (query__[i] == '&')
			index++;
	}
	CGI_env = new char *[index + 2 + 13]; //1 for NULL 1 for the first query and 13 for the headers
	for (index = 0; env__[index]; index++) {
		CGI_env[index] = strdup(env__[index]);
	}
	for (len = 0, tmp = 0; query__.length(); len++) {
		tmp = query__.find("&", tmp + 1);
		if (tmp > query__.length()) {
			CGI_env[index++] = strdup(get(query__, 0, query__.length(), 0).c_str());
			break ;
		}
		else if (tmp)
			CGI_env[index++] = strdup(get(query__, 0, tmp, 1).c_str());
		else
			query__.erase(0, 1);
	}
	CGI_env[index] = NULL;
	return CGI_env;
}

void	manage_RR::add_CGI_headers(char **CGI_env) {
	size_t	index;
	for (index = 0; CGI_env[index]; index++)
		;
	CGI_env[index++] = strdup(("CONTENT_TYPE=" + content["Content-Type"]).c_str());
	CGI_env[index++] = strdup(("CONTENT_LENGTH=" + substr_s(content["Content-Length"], 0, content["Content-Length"].find("\r"))).c_str());
	CGI_env[index++] = strdup(("HTTP_COOKIE=" + content["Cookie"]).c_str());
	CGI_env[index++] = strdup(("HTTP_USER_AGENT=" + content["User-Agent"]).c_str());
	CGI_env[index++] = strdup(("QUERY_STRING=" + content["Query"]).c_str());
	CGI_env[index++] = strdup(("REQUEST_METHOD=" + content["Method"]).c_str());
	CGI_env[index++] = strdup("REDIRECT_STATUS=200");
	CGI_env[index++] = strdup(("PATH_TRANSLATED=" + content["FULL_PATH"]).c_str());
    CGI_env[index++] = strdup(("PATH_TRANSLATED=" + content["FULL_PATH"]).c_str());
	CGI_env[index] = NULL;
}

char	**manage_RR::get_CGI_informations(std::string Method__, char **env__, std::string query__) {
	char	**CGI_env = NULL;

	if (Method__ == "GET" || Method__ == "POST") // remove post from here
		CGI_env = add_query_string(CGI_env, env__, query__);
	add_CGI_headers(CGI_env);
	return CGI_env;
}

bool	manage_RR::Setup_CGI_STDIN_STDOUT(std::string &Method__, std::string &Body__) {
	IN_FILE = tmpfile();
	OUT_FILE = tmpfile();

	if (!IN_FILE || !OUT_FILE) {
		std::cout << "COULDNT OPEN TMP FILE IN \"Setup_CGI_STDIN_STDOUT\"!!\n";
		return 1;
	}
	IN_FD = fileno(IN_FILE);
	OUT_FD = fileno(OUT_FILE);
	if (Method__ == "POST")
		write (IN_FD, (char *)Body__.c_str(), Body__.length());
	rewind(IN_FILE);
	rewind(OUT_FILE);
	return 0;
}

std::string manage_RR::CGI_request(std::string Method__, std::string Body__, char **env__, std::string query__) {
	char		*ARGS[3];
	char		**CGI_env;
	char		tmp[1024];
	std::string res;

	if (ERROR__)
		return res;
	CGI = 1;
	CGI_env = get_CGI_informations(Method__, env__, query__);
	ARGS[0] = strdup(CGI_BIN.c_str());
	ARGS[1] = strdup(content["FULL_PATH"].c_str());
	ARGS[2] = NULL;

	if (Setup_CGI_STDIN_STDOUT(Method__, Body__)) {
		//error;
	}
	if (!fork()) {
		dup2 (IN_FD, 0);
		dup2 (OUT_FD, 1);
		if (execve(ARGS[0], ARGS, CGI_env)) {
			std::cerr << "EXECVE ERROR!!\n";
			STATUE__DESCRIPTION__ = "Accepted";
			STATUE__ = "202";
		}
		exit (0);
	}
	waitpid(-1, NULL, 0);
	rewind(OUT_FILE);
	memset(tmp, '\0', 1024);
	while (std::fgets(tmp, 1024, OUT_FILE)) {
		res += tmp;
		memset(tmp, '\0', 1024);
	}
	close (IN_FD);
	close (OUT_FD);
	fclose(IN_FILE);
	fclose(OUT_FILE);
	free (ARGS[0]);
	free (ARGS[1]);
	free_2(CGI_env);
	return (res);
}

char	*manage_RR::get_file_name(std::string URI__, int case_) {
	std::string	PATH;
	std::map<std::string, Location> tmp = info[server_num__].getLocation();
	if (tmp[URI__].getRoot().length()) {
		PATH.append(tmp[URI__].getRoot());
		if (case_ == 1)
			PATH.append(tmp[URI__].getIndex());
	}
	else {
		PATH.append(info[server_num__].getRoot());
		if (case_ == 1)
			PATH.append(URI__);
	}
	if (!case_)
		PATH.append(tmp[URI__].getIndex());
	PATH.insert(0, "./");
	content["FULL_PATH"] = PATH;
	return (char*)PATH.c_str();
}

int	manage_RR::get_the_server() {
	size_t	index = 0;

	for (index = 0; index != info.size(); index++) {
		if (std::to_string(info[index].getPort()[0]) == content["Port"])
			break;
	}
	if (!info.size() || index == info.size())
		return -1;
	return index;
}

int	check_access(std::string PATH, int case_) {
	switch (case_)
	{
	case 1:
		if (!access(PATH.c_str(), F_OK))
			return 1;
		return 0;
		break;
	case 2:
		if (!access(PATH.c_str(), R_OK)) {
				return 1;
			return -1;
		}
		return 0;
	default:
		break;
	}
	return 0;
}

bool	manage_RR::check_cgi(std::string URI__) {
	std::string Root;
	std::string Index;

	if (URI__.find(".php") == URI__.length() - 4 && info[server_num__].getLocation().count("/*.php")) {
		CGI_BIN = info[server_num__].getLocation()["/*.php"].get_CGI_BIN();
		Root = info[server_num__].getLocation()["/*.php"].getRoot();
		Index = info[server_num__].getLocation()["/*.php"].getIndex();
		if (Root.length() && Index.length())
			content["FULL_PATH"] = Root + Index;
		else if (Root.length())
			content["FULL_PATH"] = Root + URI__;
		else if (Index.length())
			content["FULL_PATH"] = info[server_num__].getRoot() + Index;
		else
			content["FULL_PATH"] = info[server_num__].getRoot() + URI__;
		if (check_access(content["FULL_PATH"], 2) == -1) {
			std::cout << "CGI FILE PERMISSIONS !!\n";
			ERROR__ = 1;
			STATUE__ = "403";
			STATUE__DESCRIPTION__ = "Forbidden";
		}
		else if (!check_access(content["FULL_PATH"], 2)) {
			std::cout << "CGI FILE NOT FOUND !!\n";
			ERROR__ = 1;
			STATUE__ = "404";
			STATUE__DESCRIPTION__ = "Not Found";
		}
		return 1;
	}
	else if (URI__.find(".py") == URI__.length() - 3 && info[server_num__].getLocation().count("/*.py")) {
		CGI_BIN = info[server_num__].getLocation()["/*.py"].get_CGI_BIN();
		Root = info[server_num__].getLocation()["/*.py"].getRoot();
		Index = info[server_num__].getLocation()["/*.py"].getIndex();
		if (Root.length() && Index.length())
			content["FULL_PATH"] = Root + Index;
		else if (Root.length())
			content["FULL_PATH"] = Root + URI__;
		else if (Index.length())
			content["FULL_PATH"] = info[server_num__].getRoot() + Index;
		else
			content["FULL_PATH"] = info[server_num__].getRoot() + URI__;
		if (check_access(content["FULL_PATH"], 2) == -1) {
			std::cout << "CGI FILE PERMISSIONS !!\n";
			ERROR__ = 1;
			STATUE__ = "403";
			STATUE__DESCRIPTION__ = "Forbidden";
		}
		else if (!check_access(content["FULL_PATH"], 2)) {
			std::cout << "CGI FILE NOT FOUND !!\n";
			ERROR__ = 1;
			STATUE__ = "404";
			STATUE__DESCRIPTION__ = "Not Found";
		}
		return 1;
	}
	return 0;
}

void	read_the_file(std::ifstream &file, std::string &body) {
	char	*tmp2;
	size_t size = file.tellg();
	tmp2 = new char[size];
	memset(tmp2, '\0', size);
	file.seekg(0, std::ios::beg);
	file.read(tmp2, size);
	body.append(tmp2, size);
	delete [] tmp2;
	file.close();
}

std::string	manage_RR::get_new_URI(std::string URI__, bool &chck) {
	std::map<std::string, Location> locations = info[server_num__].getLocation();
	std::string	tmp;
	size_t	find__ = 1;

	chck = 0;
	if (locations[URI__].getRoot().length() && !access(locations[URI__].getRoot().c_str(), F_OK)) {
		if (locations[URI__].getAutoindex() == "on") {
			chck = 1;
			content["FULL_PATH"] = locations[URI__].getRoot();
			return locations[URI__].getRoot();
		}
		content["FULL_PATH"] = locations[URI__].getRoot() + locations[URI__].getIndex();
		return content["FULL_PATH"];
	}
	else if (locations[substr_s(URI__, 0, URI__.find("/", find__))].getRoot().length()
				&& !access(locations[substr_s(URI__, 0, URI__.find("/", find__))].getRoot().c_str(), F_OK)) {
		if (locations[URI__.substr(0, URI__.find("/", find__))].getAutoindex() == "on") {
			chck = 1;
		}
		content["FULL_PATH"] = locations[substr_s(URI__, 0, URI__.find("/", find__))].getRoot() + substr_s(URI__, URI__.find("/", find__), URI__.length() - URI__.find("/", find__));
		return	content["FULL_PATH"];
	}
	else if (locations["/"].getRoot().length() && !access((locations["/"].getRoot() + URI__).c_str(), F_OK)) {
		if (locations["/"].getAutoindex() == "on") {
			chck = 1;
		}
		content["FULL_PATH"] = locations["/"].getRoot() + URI__;
		return content["FULL_PATH"];
	}
	return std::string();
}

std::string manage_RR::getAutoIndexBody(std::string root) {
	DIR *dir;
	dirent *dent = NULL;

	dir = opendir(root.c_str());// this part
	std::string body = AUTO_INDEX_FORM;
	if (dir != NULL)
	{
		while ((dent = readdir(dir)) != NULL) {
	        std::string url;
	        std::string icon;
	        std::string fname = dent->d_name;
	        if (content["URI"][0] == '/' && content["URI"].length() == 1)
	            url =  fname;
	        else 
	            url = content["URI"] + "/" + fname;
	        if (fname != "." && fname != "..") {
	            std::string url1 = root + "/" + fname;
	            DIR *d2 = opendir(url1.c_str());
	            if (d2){
	                icon = "<img src=\"https://cdn-icons-png.flaticon.com/512/3767/3767084.png\" />";
	            	closedir(d2); 
	            }
	            else
	                icon = "<img src=\"https://cdn-icons-png.flaticon.com/512/2965/2965335.png\" />";
	            std::string str = "\n<li>" + icon + "<a href=\"" + url + "\">" + fname + "</a></li>\n";
	            body.append(str);
	        }
		}
		closedir(dir);
	}
	body.append("	</ul>\n\
	                </body>\n\
	                </html>");
	return body;
}

void	manage_RR::get_the_body(int case_, std::string &body, std::string &URI__) {
	DIR				*dir;
	std::ifstream	file;
	bool			chck = 0;
	std::string		name;

	if (case_ == 1) {
		dir = opendir(get_new_URI(URI__, chck).c_str());
		if (dir) {
			if (chck)
				body.append (getAutoIndexBody(get_new_URI(URI__, chck)));
			closedir (dir);
		}
		else {
			file.open(get_file_name(URI__, 1) , std::ios::in|std::ios::binary|std::ios::ate);
			if (file.is_open())
				read_the_file(file, body);
			else {
				file.open(get_file_name(URI__, 0) , std::ios::in|std::ios::binary|std::ios::ate);
				if (file.is_open())
					read_the_file(file, body);
				else {
					file.open(get_new_URI(URI__, chck) , std::ios::in|std::ios::binary|std::ios::ate);
					if (file.is_open())
						read_the_file(file, body);
					else {
						ERROR__ = 1;
						STATUE__ = "404";
						STATUE__DESCRIPTION__ = "Not Found";
					}
				}
			}
		}
	}
}

std::string	manage_RR::get_delete_URI(std::string URI__) {
	std::string ret;
	std::string	name = URI__.substr(URI__.find("/", 1) + 1);
	std::string	location_name = URI__.substr(0, URI__.find("/", 1));
	std::map<std::string, Location> locations = info[server_num__].getLocation();

	if (locations.count(location_name)) {
		if (locations[location_name].getRoot().length()) {
			content["FULL_PATH"] = "./" + locations[location_name].getRoot() + name;
			return content["FULL_PATH"];
		}
		else {
			content["FULL_PATH"] = "./" + info[server_num__].getRoot() + name;
			return content["FULL_PATH"];
		}
	}
	else
		return "";
}

std::string manage_RR::get_respond_body() {
	// creating variales;
	std::string	coding__ = content["Transfer-Encoding"];
	std::string	body__ = content["Body"];
	std::string	Method__ = content["Method"];
	std::string	URI__ = content["URI"];
	std::string	query__ = content["Query"];
	std::string	Type__ = content["Content-Type"];
	std::string	file_name;
	// end of creating variables;
	std::string body;
	size_t	index;

	if (coding__ == "chunked\r")
		body__ = chunked_decoder(body__);
	if (check_cgi(URI__))
		return CGI_request(Method__, body__, env, query__);
	else if (Method__ == "GET") {
		get_the_body(1, body, URI__);
	}
	else if (Method__ == "POST") {
		if (Type__.find("; boundary=") != Type__.npos) {
			std::string boundary;
			std::vector<std::string> sep_body;

			index = Type__.find("; boundary=");
			boundary = substr_s(Type__, index + 11, Type__.length() - index - 11);
			sep_body = separate_body(body__, boundary);
			for (size_t i = 0; i != sep_body.size(); i++) {
				index = sep_body[i].find("; filename=");
				if (index != sep_body[i].npos)
					file_name = substr_s(sep_body[i], index + 12, sep_body[i].find(34, index + 12) - index - 12);
				std::ofstream file;
				if (!file_name.empty())
					file.open("./content/" + file_name);
				else
					file.open("./content/" + get_random_name(substr_s(Type__, Type__.find("/") + 1, Type__.find(";") - 1 - Type__.find("/"))));
				index = sep_body[i].find(CRLF2);
				if (!file.is_open()) {
					STATUE__ = "202";
					STATUE__DESCRIPTION__ = "Accepted";
					ERROR__ = 1;
					break ;
				}
				else {
					STATUE__ = "201";
					STATUE__DESCRIPTION__ = "Created";
				}
				if (index == body.npos)
					file << substr_s(sep_body[i], 0, sep_body[i].find(CRLF));
				else
					file << substr_s(sep_body[i], index + 4, sep_body[i].find(CRLF, index + 2) - index - 4);
				file_name.clear();
			}
		}
		else {
			index = Type__.find("/");
			std::string file_name = get_random_name(substr_s(Type__, index + 1, Type__.length() - index - 1));
			std::ofstream file("./content/" + file_name);
			if (!file.is_open()) {
				STATUE__ = "202";
				STATUE__DESCRIPTION__ = "Accepted";
				ERROR__ = 1;
			}
			else {
				STATUE__ = "201";
				STATUE__DESCRIPTION__ = "Created";
				file << body__;
			}
		}
	}
	else if (Method__ == "DELETE") {
		file_name = "";
		file_name = get_delete_URI(URI__);
		DIR *dir = opendir(file_name.c_str());
		if (dir) {
			ERROR__ = 1;
			STATUE__ = "401";
			STATUE__DESCRIPTION__ = "Unauthorized";
			closedir(dir);
		}
		else if (file_name.find("/", file_name.find("/content/") + 10) != file_name.npos) {
			ERROR__ = 1;
			STATUE__ = "409";
			STATUE__DESCRIPTION__ = "Conflict";
		}
		else if (!remove(file_name.c_str())) {
				STATUE__ = "204";
				STATUE__DESCRIPTION__ = "No Content";
		}
		else {
			file_name = get_file_name(URI__, 0);
			if (file_name.find("/content/") == file_name.npos) {
				ERROR__ = 1;
				STATUE__  = "401";
				STATUE__DESCRIPTION__ = "Conflict";
			}
			else if (!remove(file_name.c_str())) {
				STATUE__ = "204";
				STATUE__DESCRIPTION__ = "No Content";
			}
			else {
				ERROR__ = 1;
				STATUE__ = "401";
				STATUE__DESCRIPTION__ = "Unauthorized";
			}
		}
	}
	return body;
}

void	edit_content_length(std::string &respond, std::string &body) {
	if (respond.find("Content-Length: ") != body.npos)
		respond.insert(respond.find("Content-Length: ") + 16, std::to_string(body.length()));
	else
		respond.insert(respond.find(CRLF) + 2, "Content-Length: " + std::to_string(body.length()) + CRLF);
}

std::string	check_query(std::string &URI) {
	std::string Query;

	if (URI.find("?") != std::string().npos) {
		size_t	index = URI.find("?");
		Query = substr_s(URI, index + 1, URI.length() - 1 - index);
		URI.erase(index, URI.length() - 1);
	}
	return Query;
}

void	manage_RR::request_line() {
	{
		size_t index;
		
		index = content["Request_Line"].find(' ');
		content["Method"] = substr_s(content["Request_Line"], 0, index);
		content["URI"] = substr_s(content["Request_Line"], index + 1, content["Request_Line"].find(' ', index + 1) - index - 1);
		content["Query"] = check_query(content["URI"]); 																																	// if the query part exist in the uri this function will remove it from the uri and will return its value;
		index = content["Request_Line"].find(' ', index + 1);
		content["Protocol"] = substr_s(content["Request_Line"], index + 1, content["Request_Line"].length());
	}
}

int	manage_RR::headers() {
	std::string Headers__ = content["Headers"];

	for (std::string key; Headers__.length();) {
		if (Headers__.find(":") == Headers__.npos)
			break ;
		key = get(Headers__, 0, Headers__.find(':'), 1);
		if (key.find_first_of(WHITESPACE) != key.npos) {
			STATUE__ = "400";
			STATUE__DESCRIPTION__ = "Bad request";
			std::cout << "Bad request\n";
			return 1;
		}
		if (Headers__.find("\r\n") != Headers__.find("\r\n "))
			content[key] = get(Headers__, 0, Headers__.find("\r\n"), 2);
		else if (Headers__.find("\n") != Headers__.npos)
			content[key] = get(Headers__, 0, Headers__.find("\n"), 1);
		else if (Headers__.find("\r\n") == Headers__.npos)
			content[key] = get(Headers__, 0, Headers__.length(), 0);
		else
			content[key] = get(Headers__, 0, get_header_end(Headers__), 1);
		erase_from_beg_end(content[key], ' ', 1);
	}
	if (content["Body"].length() && !content["Content-Length"].length() && content["Transfer-Encoding"] != "chunked") {
		STATUE__ = "411";
		STATUE__DESCRIPTION__ = "Length required";
		std::cout << "Length required\n";
		return 1;
	}
	if (content["Host"].length()) {
		if (content["Host"].find(":") != Headers__.npos && content["Host"].find(":") != content["Host"].length())
			content["Port"] = substr_s(content["Host"], content["Host"].find(":") + 1, content["Host"].length() - content["Host"].find(":") - 1);
		else {
			STATUE__ = "400";
			STATUE__DESCRIPTION__ = "Bad request";
			std::cout << "UNVALIABLE PORT";
			return 1;
		}
	}
	else {
		STATUE__ = "400";
		STATUE__DESCRIPTION__ = "Bad request";
		std::cout << "UNVALIABLE PORT\n";
		return 1;
	}
	if (content["Content-Length"].length()) {
		if ((content["Content-Length"] != std::to_string(content["Body"].length()) && content["Transfer-Encoding"] != "chunked")) {
			std::cout << "CONTENT-LENGTH : " << content["Content-Length"] << std::endl;
			std::cout << "CONTENT-LENGTH : " << std::to_string(content["Body"].length()) << std::endl;
			STATUE__ = "400";
			STATUE__DESCRIPTION__ = "Bad request";
			std::cout << "Length-error\n";
			return 1;
		}
	}
	else if (content["Body"].length()) {
		STATUE__ = "400";
		STATUE__DESCRIPTION__ = "Bad request";
		std::cout << "Length-error\n";
		return 1;
	}
	return 0;
}

bool	check_method(std::string Method, std::vector<std::string> server_methods) {
	for (size_t i = 0; i != server_methods.size(); i++) {
		if (Method == server_methods[i])
			return 0;
	}
	return 1;
}

int	manage_RR::request_line_checker() {
	std::string tmp;

	tmp = content["Method"];
	if (content["Protocol"] != "HTTP/1.1") {
		STATUE__DESCRIPTION__ = "HTTP Version Not Supported";
		STATUE__ = "505";
		std::cout << "505 HTTP Version Not Supported";
		return 1;
	}
	if (check_method(tmp, info[server_num__].get_Methods())) { // checking if the method is known to the server
		STATUE__DESCRIPTION__ = "Not implimented";
		STATUE__ = "501";
		std::cout  << "501 Not implimented\n";
		return 1;
	}
	else if (info[server_num__].getLocation().count(substr_s(content["URI"],0 ,content["URI"].find("/") + 1))) {
		std::vector<std::string> tmp_vec = info[server_num__].getLocation()[content["URI"]].getAllowMethods();
		for (size_t index = 0; index != tmp_vec.size(); index++) {
			if (tmp_vec[index] == tmp)
				break ;
			else if (index + 1 == tmp_vec.size()) {
				STATUE__DESCRIPTION__ = "Method not allowed";
				STATUE__ = "405";
				std::cout  << "405 Method not allowed\n";
				return 1;
			}
		}
	}
	if (content["URI"].find_first_of(WHITESPACE) != tmp.npos) { //the URI should never have a whitespace
		std::cout << "400 Bad request\n";
		STATUE__ = "400";
		STATUE__DESCRIPTION__ = "Bad request";
		return 1;
	}
	if (content["Body"].length() > info[server_num__].getClientMaxBodySize()) {
		STATUE__ = "400";
		STATUE__DESCRIPTION__ = "Bad request";
		std::cout << "Length-error\n";
		return 1;
	}
	return 0;
}

bool manage_RR::check_redirection() {
	std::map<std::string, Location> locations = info[server_num__].getLocation();
	if (locations.count(content["URI"]) && locations[content["URI"]].getReturnPath().length() && locations[content["URI"]].getReturnCode() == 301)
		return 1;
	return 0;
}

std::string	manage_RR::get_cgi_response(std::string &body) {
	std::string ret;
	size_t tmp;
	
	ret = body;
	tmp = body.find("Status: ");
	if (tmp != body.npos) {
		STATUE__ = substr_s(body, tmp + 8, body.find(" ", tmp + 9) - tmp -8);
		STATUE__DESCRIPTION__ = substr_s(body, body.find(" ", tmp + 9) + 1, body.find(" ", body.find(" ", tmp + 9) + 1));
	}
	ret.insert(0, std::string() + "HTTP/1.1 " + STATUE__ + STATUE__DESCRIPTION__ + CRLF);
	tmp = body.find("Set-Cookie: ");
	return ret;
}

std::string	manage_RR::redirection() {
	return "HTTP/1.1 301TEST\nLocation: " + info[server_num__].getLocation()[content["URI"]].getReturnPath() + CRLF2;
}

std::string	manage_RR::get_error_file() {
	std::ifstream	file;
	std::string		tmp;
	std::string		tmp2;

	if (server_num__ != -1) {
		file.open(info[server_num__].getErrorPage()[STATUE__].c_str());
		if (file.is_open()) {
			while (file.good()) {
				file >> tmp2;
				tmp.append(tmp2);
				tmp.append("\n");
			}
			tmp.erase(tmp.length() - 1, 1);
		}	
		else {
			file.open(("./links/error_page/" + STATUE__ + ".html"));
			if (file.is_open()) {
				while (file.good()) {
					file >> tmp2;
					tmp.append(tmp2);
					tmp.append("\n");
				}
				tmp.erase(tmp.length() - 1, 1);
			}
			else
				tmp = STATUE__ + STATUE__DESCRIPTION__;
		}
	}
	else {
		file.open(("./links/error_page/" + STATUE__ + ".html"));
		if (file.is_open()) {
			while (file.good()) {
				file >> tmp2;
				tmp.append(tmp2);
			}
		}
		else
			tmp = STATUE__ + STATUE__DESCRIPTION__;
	}
	return tmp;
}

std::string	manage_RR::respond_generator() {
	std::string 	respond;
	std::string		tmp;
	std::ifstream	file;

	if (content["URI"].find("favicon") != tmp.npos)
		return respond;
	if (ERROR__) {
		tmp = get_error_file();
	}
	else if (check_redirection())
		return redirection();
	else
		tmp = get_respond_body();
	if (ERROR__) {
		tmp = get_error_file();
	}
	if (!CGI) {
		respond = get_respond_statue_line();
		respond.append(get_respond_headers(content["FULL_PATH"], ERROR__, content["Mehtod"]));
		edit_content_length(respond, tmp);
		respond.append(tmp);
	}
	else
		respond = get_cgi_response(tmp);
	return respond;
}

std::string manage_RR::get_res() {
	return respond_generator();
}

manage_RR::manage_RR(std::string client_content, std::vector<Config> info__, char **env__) : server_num__(-1), info(info__), STATUE__("200"), STATUE__DESCRIPTION__("OK"), ERROR__(0), CGI(0) {
	this->env = env__;
	content["Request_Line"] = get(client_content, 0, client_content.find(CRLF), 2);
	content["Headers"] = get(client_content, 0, client_content.find(CRLF2), 4);
	if (!content["Headers"].empty())
		content["Headers"].append("\n");
	content["Body"] = get(client_content, 0, client_content.length(), 0);
	request_line();
	if (content["URI"].find("favicon") != client_content.npos)
		return ;
	if (headers()) {
		ERROR__ = 1;
		return ;
	}
	server_num__ = get_the_server();
	if (server_num__ == -1) {
		ERROR__ = 1;
		STATUE__ = "400";
		STATUE__DESCRIPTION__ = "Bad Request";
		return ;
	}
	if (request_line_checker()) {
		ERROR__ = 1;
		return ;
	}
 }