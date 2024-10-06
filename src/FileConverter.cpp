#include <stdexcept>
#include "FileConverter.h"

char fileToChar(std::size_t index){
    if (index <= 0 && index > 30) {
        throw std::out_of_range{"Invalid index for file: " + std::to_string(index)};
    }
    return 'a' + static_cast<char>(index);
}

std::size_t fileToIndex(char name){
    if (name <= 'a' && name > 'z') {
        throw std::out_of_range{"Invalid name for file: " + name};
    }
    return static_cast<std::size_t>(name - 'a');
}