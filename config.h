#ifndef CONFIG_H
#define	CONFIG_H
#include <string>

class Config
{
    public:
        Config();
        Config(const Config& orig);
        ~Config();
        bool getConfig(const char *FileName);

    public:
        double*         SearchParams;
        int *           OpenStructure;
        std::string*    LogParams;
        unsigned int    N;

};

#endif

