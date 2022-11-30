#include <iostream>
#include <vector>
#include "../location/location.class.hpp"

class Config {
	private:
		Location location;
		std::vector<int> port;
		std::vector<std::string> server_name;
		std::string host;
		int	client_max_body_size;
		std::string root;
	public:
		// Config(); // default constructor
		// ~Config(); // destructor
};