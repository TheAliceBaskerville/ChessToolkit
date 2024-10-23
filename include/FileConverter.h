#ifndef FILECONVERTER_H
#define FILECONVERTER_H

#include <cstddef> // For std::size_t

char fileToChar(std::size_t index);
std::size_t fileToIndex(char name);

#endif