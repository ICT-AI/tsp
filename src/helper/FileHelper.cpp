#include "FileHelper.h"
#include <iostream>

const char* FileHelper::convertToResourcePath(const char *file_name) {
  string filePath(RESOURCE_DIR);
  filePath.append(file_name);

  return filePath.c_str();
}

const char* FileHelper::convertToResultPath(const char *file_name) {
  string filePath(RESULT_DIR);
  filePath.append(file_name);

  return filePath.c_str();
}

vector<vector<int>> FileHelper::readDataFile(const char *file_name) {
  ifstream in(this->convertToResourcePath(file_name));  // open data file

  // if file open failed, throw an exception.
  if (in.fail()) {
    throw invalid_argument("ERROR: Could not open the file");
  }

  vector<vector<int>> node_data;
  string line_buffer;
  vector<string> words;
  int node_num, x, y;

  // skip first 8 line
  for (int i = 0; i < 8; i++) {
    getline(in, line_buffer);
  }

  // read line by line
  while (getline(in, line_buffer)) {
    istringstream iss(line_buffer);
    if (iss.str() == "EOF") {
      break;
    }

    iss >> node_num >> x >> y;
    node_data.push_back({node_num, x, y}); // add to node data set
  }

  in.close(); // close data file

  return node_data;
}

void FileHelper::writeTourAsFile(const char *file_name, vector<Node> &tour) {
  ofstream out(this->convertToResultPath(file_name));

  for (auto node : tour) {
    out << node.index << endl;
  }

  out.close();
}
