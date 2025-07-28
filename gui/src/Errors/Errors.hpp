/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Errors.hpp
*/

#ifndef ERRORS_H
#define ERRORS_H

#include <exception>
#include <string>

class Errors : public std::exception {
    public:
        Errors(const std::string &message, const std::string &component = "Unknown");
        const char *what() const noexcept override;
};

#endif //ERRORS_H
