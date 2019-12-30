#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "world_bank.h"

#define ACTIVE              "Active"
#define CLOSED              "Closed"

#define QUOTE               '\"'
#define DELIMITER           ","
#define SEPARATOR           " : "

#define STATUS              "\"status\""
#define REGION_NAME         "\"regionname\""
#define LEND_PROJECT_COST   "\"lendprojectcost\""

#define INPUT_FILE_NAME     "world_bank.json"

bool world_bank::world_bank::enumerate()
{
    try
    {
        std::string line;
        std::ifstream ifstream(INPUT_FILE_NAME);
        if (!ifstream.is_open())
        {
            std::ostringstream ostringstream;
            ostringstream << __FILE__ << " | " << __FUNCTION__ << " | " << __LINE__ << ": " << "failed to open input '" << INPUT_FILE_NAME << "' file" << std::endl;
            throw std::runtime_error(ostringstream.str());
        }
        while (std::getline(ifstream, line))
        {
            std::string status = get_value(line, STATUS);
            if (status.empty())
            {
                std::ostringstream ostringstream;
                ostringstream << __FILE__ << " | " << __FUNCTION__ << " | " << __LINE__ << ": " << "empty value of STATUS has been found" << std::endl;
                throw std::runtime_error(ostringstream.str());
            }
            std::string region_name = get_value(line, REGION_NAME);
            if (region_name.empty())
            {
                std::ostringstream ostringstream;
                ostringstream << __FILE__ << " | " << __FUNCTION__ << " | " << __LINE__ << ": " << "empty value of REGION_NAME has been found" << std::endl;
                throw std::runtime_error(ostringstream.str());
            }
            std::string lend_project_cost = get_value(line, LEND_PROJECT_COST);
            if (lend_project_cost.empty())
            {
                std::ostringstream ostringstream;
                ostringstream << __FILE__ << " | " << __FUNCTION__ << " | " << __LINE__ << ": " << "empty value of LEND_PROJECT_COST has been found" << std::endl;
                throw std::runtime_error(ostringstream.str());
            }
            if (status.compare(ACTIVE) == 0 || status.compare(CLOSED) == 0)
            {
                if (projects.find(region_name) == projects.end())
                {
                    projects[region_name] = 0;
                }
                if (investments.find(region_name) == investments.end())
                {
                    investments[region_name] = 0;
                }
                projects[region_name] += 1;
                investments[region_name] += atoll(lend_project_cost.c_str());
            }
        }
        ifstream.close();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

void world_bank::world_bank::analyse()
{
    int counter = 0;
    const int limit = 10;
    transposed_projects_t transposed_projects = transpose(projects);
    transposed_investments_t transposed_investments = transpose(investments);
    std::cout << "Projects per Region: " << std::endl << std::endl;
    for (transposed_projects_t::reverse_iterator iterator = transposed_projects.rbegin();
        iterator != transposed_projects.rend() && counter < limit; ++iterator, ++counter)
    {
        std::cout << iterator->second << ":  " << iterator->first << std::endl;
    }
    counter = 0;
    std::cout << std::endl << std::endl << "Investments per Region: " << std::endl << std::endl;
    for (transposed_investments_t::reverse_iterator iterator = transposed_investments.rbegin();
        iterator != transposed_investments.rend() && counter < limit; ++iterator, ++counter)
    {
        std::cout << iterator->second << ":  " << format(iterator->first) << std::endl;
    }
}

template <typename A, typename B>
std::multimap<B, A> world_bank::world_bank::transpose(const std::map<A, B>& source)
{
    std::multimap<B, A> destination;
    for (typename std::map<A, B>::const_iterator iterator = source.begin(); iterator != source.end(); ++iterator)
    {
        destination.insert(std::pair<B, A>(iterator->second, iterator->first));
    }
    return destination;
}

std::string world_bank::world_bank::format(unsigned long long value)
{
    char buffer[128];
    char *p = buffer + 128;
    unsigned char count = 0;
    *(--p) = '\0';
    while (value != 0)
    {
        *(--p) = '0' + (value % 10);
        value /= 10;
        if (++count == 3)
        {
            count = 0;
            *(--p) = ' ';
        }
    }
    return std::string(p);
}

std::string world_bank::world_bank::get_value(const std::string& line, const std::string& key)
{
    size_t begin;
    std::string value;
    if ((begin = line.find(key)) != std::string::npos)
    {
        begin += key.length() + std::string(SEPARATOR).length();
        if (begin != line.npos)
        {
            size_t end = line.find(DELIMITER, begin);
            if (end != std::string::npos)
            {
                value = line.substr(begin, end - begin);
                value.erase(std::remove(value.begin(), value.end(), QUOTE), value.end());
            }
        }
    }
    return value;
}
