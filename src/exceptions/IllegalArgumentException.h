//
// Created by michael on 16.01.18.
//

#pragma once

#include <stdexcept>

class IllegalArgumentException : public std::logic_error {
public:
    IllegalArgumentException() : std::logic_error("Unexpected or illegal arguments") {};
    IllegalArgumentException(std::string error) : std::logic_error(error) {};

};
