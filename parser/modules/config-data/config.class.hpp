#include <iostream>
#include <vector>
#include "../location/location.class.hpp"
#include <map>


class Config {
	private:
		// Location location;
		std::map<std::string, Location> location;
		std::vector<int> port;
		std::vector<std::string> server_name;
		std::string host;
		int	client_max_body_size;
		std::string root;
	public:
		Config(); // default constructor
		~Config(); // destructor
		Config(const Config &config); // copy constructor

		// getters
		std::map<std::string, Location> getLocation() const;
		std::vector<int> getPort() const;
		std::vector<std::string> getServerName() const;
		std::string getHost() const;
		int getClientMaxBodySize() const;
		std::string getRoot() const;
		
		// setters
		void setLocation(std::string locationPath, Location location);
		void setPort(std::vector<int> port);
		void setServerName(std::vector<std::string> server_name);
		void setHost(std::string host);
		void setClientMaxBodySize(int client_max_body_size);
		void setRoot(std::string root);

		// other methods
		void print() const;
		void clear();
};