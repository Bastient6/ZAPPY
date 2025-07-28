/*
** EPITECH PROJECT, 2024
** gui
** File description:
** Parser.hpp
*/

#ifndef PARSER_HPP
#define PARSER_HPP

#include <exception>
#include <string>
#include <utility>

class Parser {
public:
    Parser(int ac, char **av);
    void parseArgs(int ac, char **av);
    void checkPort(const std::string &port);
    void checkIp(const std::string &ip);
    int getPort() const { return _port; };
    std::string getIp() const { return _ip; };
    void help();

    class Errors : public std::exception {
    public:
        explicit Errors(std::string message, std::string component = "Unknown") : _message(std::move(message)),
        _component(std::move(component)) {};
        const char *what() const noexcept override { return "Invalid number of arguments"; };

    private:
        std::string _message;
        std::string _component;
    };

private:
    int _port;
    std::string _ip;
};



#endif //PARSER_HPP
