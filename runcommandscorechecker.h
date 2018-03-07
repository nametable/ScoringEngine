#ifndef RUNCOMMANDSCORECHECKER_H
#define RUNCOMMANDSCORECHECKER_H
#include "basescorechecker.h"
#include <regex>
class RunCommandScoreChecker : public BaseScoreChecker
{
    friend class boost::serialization::access;
    //template<class Archive> void serialize(Archive &ar, const unsigned int version);
    template<class Archive> void serialize(Archive &ar, const unsigned int version)
    {
        // save/load base class information
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(BaseScoreChecker);
        ar & BOOST_SERIALIZATION_NVP(bSearchstringexist)
           & BOOST_SERIALIZATION_NVP(command)
           & BOOST_SERIALIZATION_NVP(commandoutput)
           & BOOST_SERIALIZATION_NVP(searchstring);
        //ar & street1 & street2;
    }
protected:
    std::string command;
    std::string commandoutput;
    std::string searchstring;
    bool bSearchstringexist;
public:
    void setCommand(std::string command);
    void setSearchExist(bool exist);
    bool getSearchExist();
    void setSearchString(std::string searchstring);
    std::string getSearchString();
    std::string getCommand();
    void executeCommand();
    std::string getCommandOutput();
    RunCommandScoreChecker();
    void checkState();

};

#endif // RUNCOMMANDSCORECHECKER_H
