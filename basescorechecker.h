/*/////
//
//  2018
//  BaseScoreChecker is an class to derive from for score checking
//  It requires checkState to be implemented.
//
/////*/
#ifndef BASESCORECHECKER_H
#define BASESCORECHECKER_H
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <boost/regex.hpp>
//#include <QItemDelegate>
class BaseScoreChecker
{
    friend class boost::serialization::access;
    friend std::ostream & operator<<(std::ostream &os, const BaseScoreChecker &gp);
    //template<class Archive>
    //void serialize(Archive & ar, const unsigned int /* file_version */);
    template<class Archive> void serialize(Archive & ar, const unsigned int file_version )
    {
        ar  & BOOST_SERIALIZATION_NVP(state)
            & BOOST_SERIALIZATION_NVP(description)
            & BOOST_SERIALIZATION_NVP(checkerType)
            & BOOST_SERIALIZATION_NVP(points);
        if (file_version>0){
            ar & BOOST_SERIALIZATION_NVP(instructions);
        }

    }

protected:
    bool state;
    std::string description;
    std::string instructions;
    std::string checkerType;
    int points;

public:
    BaseScoreChecker();
    BaseScoreChecker(std::string description);
    bool getState();
    std::string getDescription();
    std::string getInstructions();
    std::string getCheckerType();
    int getPoints();
    void setDescription(std::string newDescription); //description of item
    void setInstructions(std::string newInstructions); //instruction or question for user
    void setPoints(int newPoints);    //points of item - negative for mistakes
    virtual void checkState()=0; //Pure Virtual - run code to see if issue has been resolved
};
//BOOST_SERIALIZATION_ASSUME_ABSTRACT(BaseScoreChecker)
BOOST_CLASS_VERSION(BaseScoreChecker, 1)
std::string exec(const char* cmd);

#endif // BASESCORECHECKER_H
