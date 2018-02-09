//
// Created by David Culley on 09.01.18.
//

#pragma once

#include <stdexcept>

class NotImplementedException : public std::logic_error {
public:
    NotImplementedException() : std::logic_error("Not yet implemented") {};
};
