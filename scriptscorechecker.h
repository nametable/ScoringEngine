#ifndef SCRIPTSCORECHECKER_H
#define SCRIPTSCORECHECKER_H
#include "basescorechecker.h"

class ScriptScoreChecker : public BaseScoreChecker
{
    friend class boost::serialization::access;
    //template<class Archive> void serialize(Archive &ar, const unsigned int version);
    template<class Archive> void serialize(Archive &ar, const unsigned int version)
    {
        // save/load base class information

        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(BaseScoreChecker);
        ar & BOOST_SERIALIZATION_NVP(script)
           & BOOST_SERIALIZATION_NVP(scriptOutput)
           & BOOST_SERIALIZATION_NVP(desiredState)
           & BOOST_SERIALIZATION_NVP(searchString);
        //ar & street1 & street2;
    }
protected:
    std::string script; //bash script to be run - assuming that is available
    std::string scriptOutput; //output from the script that ran
    std::string searchString; //string to search for in script output
    bool desiredState; //whether or not string is desired in output
    void execute();
public:
    void setScript(std::string script);
    std::string getScript();
    void setSearchString(std::string searchString);
    std::string getSearchString();
    void setDesiredState(bool state);
    bool getDesiredState();
    std::string getOutput();
    void checkState();
    ScriptScoreChecker();
};
bool gen_scriptrun_directory();
#endif // SCRIPTSCORECHECKER_H
