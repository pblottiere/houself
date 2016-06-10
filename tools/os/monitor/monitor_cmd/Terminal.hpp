#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <iostream>

//------------------------------------------------------------------------------
// Class
//------------------------------------------------------------------------------
class Terminal
{
public:
    Terminal();

    void run();
    void halt();

private:
    void update_prompt();
    void init_completion();
    char* get_cmd(const char *text, int32_t state);

    bool _again;
    std::string _name;
    std::string _prompt;
};

#endif
