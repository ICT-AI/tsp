#ifndef TSP_FILEHELPER_H
#define TSP_FILEHELPER_H

#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include "../model/Node.h"

using namespace std;

/**
 * Define below directories.
 */
#define RESOURCE_DIR "../resource/"
#define RESULT_DIR "../result/"

class FileHelper {
 private:
  /**
   * Convert resource data file name to absolute file path.
   *
   * @param file_name
   * @return
   */
  string convertToResourcePath(const char *file_name);

  /**
   * Convert result data file name to absolute file path.
   *
   * @param file_name
   * @return
   */
  string convertToResultPath(const char *file_name);

 public:
  /**
   * Read the node data set from data file.
   *
   * @param file_name
   * @return
   */
  vector<vector<int>> readDataFile(const char *file_name);

  void writeTourAsFile(const char *file_name, vector<Node> &tour);
};

#endif //TSP_FILEHELPER_H
