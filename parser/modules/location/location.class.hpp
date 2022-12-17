#include <iostream>
#include <vector>

class Location {
	private:
		std::string autoindex;
		std::string index;
		std::vector<std::string> allow_methods;
		std::string locationPath;
		std::string root;
		std::string upload_enable;
		std::string upload_path;
	
	public:
		Location(); // default constructor
		~Location(); // destructor

		// getters
		std::string getAutoindex() const;
		std::string getIndex() const;
		std::vector<std::string> getAllowMethods() const;
		std::string getRoot() const;
		std::string getUploadEnable() const;
		std::string getUploadStore() const;
		std::string getLocationPath() const;

		// setters
		void setAutoindex(std::string autoindex);
		void setIndex(std::string index);
		void setAllowMethods(std::vector<std::string> allow_methods);
		void setRoot(std::string root);
		void setUploadEnable(std::string upload_enable);
		void setUploadPath(std::string upload_path);
		void setLocationPath(std::string locationPath);

		// other methods
		void printLocation() const;
		void clearLocation();
};