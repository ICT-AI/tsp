#include "FileHelper.h"

const char* FileHelper::convertToAbsolutePath(const char *file_name) {
  string filePath = __FILE__;
  string find = "/src/helper/FileHelper.cpp";
  size_t findPos = filePath.rfind(find);
  string replace("/resource/");
  replace.append(file_name);

  return filePath.replace(findPos, find.length(), replace).c_str();
}

vector<vector<int>> FileHelper::readDataFile(const char *file_name) {
  ifstream in(this->convertToAbsolutePath(file_name));  // open data file

  // if file open failed, throw an exception.
  if (in.fail()) {
    in.exceptions(ifstream::failbit);
  }

  vector<vector<int>> node_data;
  string line_buffer;
  int node_num, x, y;
  // read line by line
  while (getline(in, line_buffer)) {
    istringstream iss(line_buffer);
    iss >> node_num;
    iss >> x;
    iss >> y;

    node_data.push_back({node_num, x, y}); // add to node data set
  }

  in.close(); // close data file

  return node_data;
}
