#ifndef WORLD_BANK_H
#define WORLD_BANK_H

#include <map>
#include <string>

namespace world_bank
{
    typedef std::map<std::string, unsigned short> projects_t;
    typedef std::map<std::string, unsigned long long> investments_t;
    typedef std::multimap<unsigned short, std::string> transposed_projects_t;
    typedef std::multimap<unsigned long long, std::string> transposed_investments_t;

    class world_bank
    {
    public:
        world_bank() : projects(), investments() {};
        virtual ~world_bank() {};
        virtual bool enumerate();
        virtual void analyse();

    protected:


    private:
        template <typename A, typename B>
        std::multimap<B, A> transpose(const std::map<A, B>& source);

    private:
        std::string format(unsigned long long value);
        std::string get_value(const std::string& line, const std::string& key);

    private:
        projects_t projects;
        investments_t investments;
    };
}

#endif // WORLD_BANK_H
