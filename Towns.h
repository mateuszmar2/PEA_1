#ifndef TOWNS_H_
#define TOWNS_H_

#include <vector>

class Towns
{
private:
    std::vector<std::vector<int>> towns;

public:
    void loadDataFromFile(const char *filename);
    void printData();
    std::vector<std::vector<int>> getTowns();
};

#endif /* TOWNS_H_ */
