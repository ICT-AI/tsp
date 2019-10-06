#include "../header/FileHelper.h"

const char* FileHelper::convertToAbsolutePath(const char *file_name) {
	string filePath = __FILE__;
	string find = "/src/helper/FileHelper.cpp";
	size_t findPos = filePath.rfind(find);
	string replace("/resource/");
	replace.append(file_name);

	return filePath.replace(findPos, find.length(), replace).c_str();
}

vector<vector<int>> FileHelper::readDataFile(const char *file_name) {

	//ifstream in(this->convertToAbsolutePath(file_name));  // open data file
	string path = "./resource/";
	path += file_name;
	ifstream in(path);


	// if file open failed, throw an exception.
	if (in.fail()) {
		in.exceptions(ifstream::failbit);
	}

	vector<vector<int>> node_data;
	string line_buffer;
	int node_num, x, y;

	// ignore first 8 line
	for (int i = 0; i < 8; i++) {
		getline(in, line_buffer);
	}

	// read line by line
	while (getline(in, line_buffer)) {
		istringstream iss(line_buffer);
		iss >> node_num;
		iss >> x;
		iss >> y;

		if (node_num != 0) {  // ignore EOF string
			node_data.push_back({ node_num, x, y }); // add to node data set
		}
	}

	in.close(); // close data file

	return node_data;
}
