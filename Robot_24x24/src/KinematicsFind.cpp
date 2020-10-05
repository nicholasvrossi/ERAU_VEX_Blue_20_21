#include <vector>
#include <map>
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <optional>
#include "main.h"


#define CMD_ERR_BAD_SIZE  (-1)
#define CMD_ERR_BAD_TOKEN (-2)


class Command {
    virtual char* getCommand() = 0;
};

typedef union {
    std::string* str;
    int i;
} IntOrString;

typedef void (*cmdFunct)(std::pair<int, std::vector<IntOrString>> parsed);
std::pair<std::string, std::pair<std::string, std::vector<cmdFunct>>> cmdEntry(std::string command, std::vector<cmdFunct> functs) {
    int nameIndex = command.find(" ");
    return std::make_pair(command.substr(0, nameIndex), std::make_pair(command.substr(nameIndex + 1, command.size()), functs));
}


// Command list
std::map<std::string, std::pair<std::string, std::vector<cmdFunct>>> commands = {
    cmdEntry("set [speed,pos] {port} {value}",  std::vector<cmdFunct>{
        [] (std::pair<int, std::vector<IntOrString>> parsed) {
            // set speed of the port here
        },
        [] (std::pair<int, std::vector<IntOrString>> parsed) {
            // set position of the port here
        }
    })
};


std::vector<std::string> split(std::string str, char delim) {
    std::vector<std::string> split;

    int i = 0;
    for (int j = 0; j < str.size(); j++) {
        if (str[j] == delim) {
            split.push_back(str.substr(i, j - i));
            i = j + 1;
        }
    }

    if (i != str.size()) {
        split.push_back(str.substr(i, str.size()));
    }

    return split;
}

std::optional<int> parseInt(std::string str) {
    for (char digit: str) {
        if (!std::isdigit(digit)) {
            return std::nullopt;
        }
    }

    std::optional<int> value = std::stoi(str);

    return value;
}

std::pair<int, std::vector<IntOrString>> parseCommand(std::string input, std::string command) {
    std::pair<int, std::vector<IntOrString>> parsed;
    parsed.first = 0;

    std::vector<std::string> inputSplit = split(input, ' ');
    std::vector<std::string> cmdSplit = split(command, ' ');

    std::vector<int> branchIndeces;

    if (inputSplit.size() != cmdSplit.size()) {
        parsed.first = CMD_ERR_BAD_SIZE;
    }
    else {
        for (int i = 0; i < inputSplit.size(); i++) {
            std::string inputToken = inputSplit[i];
            std::string cmdToken   = cmdSplit[i];

            switch (cmdToken[0]) {
                case '[':
                    {
                        std::string tokenListContents = cmdToken.substr(1, cmdToken.size() - 1);
                        std::vector<std::string> tokenElements = split(tokenListContents, ',');

                        for (int i = 0; i < branchIndeces.size(); i++) {
                            branchIndeces[i] *= tokenElements.size();
                        }

                        int i;
                        for (i = 0; i < tokenElements.size(); i++) {
                            if (inputToken == tokenElements[i]) {
                                IntOrString var;
                                var.str = &inputToken;
                                parsed.second.push_back(var);

                                branchIndeces.push_back(i);

                                break;
                            }
                        }

                        if (i == tokenElements.size()) {
                            parsed.first = CMD_ERR_BAD_TOKEN;
                        }
                    }
                break;
                case '{':
                    {
                        auto val = parseInt(inputToken);

                        IntOrString ios;

                        if (val == std::nullopt)
                            ios.str = &inputToken;
                        else
                            ios.i = val.value();

                        parsed.second.push_back(ios);
                    }
                break;
                default:
                    {
                        if (inputToken != cmdToken) {
                            parsed.first = CMD_ERR_BAD_TOKEN;
                        }
                        else {
                            IntOrString var;
                            var.str = &inputToken;
                            parsed.second.push_back(var);
                        }
                    }
            }
        }
    }

    for (int i: branchIndeces)
        parsed.first += i;

    return parsed;
}

void parseInput(std::string input) {
    std::string inputName = input.substr(0, input.find(" "));

    if (commands.find(inputName) == commands.end()) {
        std::cout << "Error: command not found:" << std::endl;
    }
    else {
        auto cmdParams = commands[inputName].first;
        auto inputParams = input.substr(input.find(" "), input.size());
        auto parsed = parseCommand(inputParams, cmdParams);

        switch (parsed.first) {
            case CMD_ERR_BAD_SIZE:
                std::cout << "Error: bad size: " << inputName << " " << cmdParams << std::endl;
                break;
            case CMD_ERR_BAD_TOKEN:
                std::cout << "Error: bad token: " << inputName << " " << cmdParams << std::endl;
                break;
            default:
                if (parsed.first < 0) {
                    std::cout << "Error: unhandled error: " << parsed.first << std::endl;
                }
                else {
                    commands[inputName].second[parsed.first](parsed);
                }
        }
    }


    // std::vector<std::string> command = split(input, ' ');
    //
    // if (command.size() == 0) {
    //     // no command
    // }
    // else if (command[0] == "set") {
    //     if (command.size() <= 3) {
    //         std::cout << "Use: set [speed,pos] {port} {value}" << std::endl;
    //     }
    //     else {
    //         auto port  = parseInt(command[2]);
    //         auto value = parseInt(command[3]);
    //
    //         if (port == std::nullopt) {
    //             std::cout << "Error: {port} not an integer: " << command[3] << std::endl;
    //         }
    //         else if (value == std::nullopt) {
    //             std::cout << "Error: {value} not an integer: " << command[3] << std::endl;
    //         }
    //         else if (command[1] == "speed") {
    //             // set motor at port to speed value
    //         }
    //         else if (command[1] == "pos") {
    //             // TODO tare motor at port
    //             // todo move motor to pos
    //         }
    //         else {
    //             std::cout << "Error: command not recognised: " << input << std::endl;
    //         }
    //     }
    // }
    // else {
    //     std::cout << "Error: command not recognised: " << input << std::endl;
    // }
}

void runFinder(std::vector<pros::Motor> motors) {
    std::vector<Command> commandBacklog;

    while (1) {
        // TODO display motor data to LCD

        std::string input;
        std::cin >> input;

        parseInput(input);
        // TODO do stuff with the state
    }
}
