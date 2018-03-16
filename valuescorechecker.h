#ifndef VALUESCORECHECKER_H
#define VALUESCORECHECKER_H
#include "basescorechecker.h"
class ValueScoreChecker : public BaseScoreChecker
{
    friend class boost::serialization::access;
    //template<class Archive> void serialize(Archive &ar, const unsigned int version);
    template<class Archive> void serialize(Archive &ar, const unsigned int version)
    {
        // save/load base class information
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(BaseScoreChecker);
        ar & BOOST_SERIALIZATION_NVP(desireExist)
           & BOOST_SERIALIZATION_NVP(filepath)
           & BOOST_SERIALIZATION_NVP(filecontent)
           & BOOST_SERIALIZATION_NVP(searchstring);
        //ar & street1 & street2;
    }
protected:
    std::string filepath;
    bool desireExist;
    std::string filecontent;
    std::string searchstring;
public:
    void readFile();
    void setFilepath(std::string newFilepath);
    std::string getFilepath();
    void setDesireExist(bool newDesireExist);
    bool getDesireExist();
    void setSearchString(std::string searchstring);
    std::string getSearchString();
    void checkState();
    ValueScoreChecker();
};
std::string get_file_contents(std::string filename);
#endif // VALUESCORECHECKER_H
