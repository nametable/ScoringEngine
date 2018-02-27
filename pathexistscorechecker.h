#ifndef FILEEXISTSCORECHECKER_H
#define FILEEXISTSCORECHECKER_H
#include "basescorechecker.h"
#include <boost/filesystem.hpp>

class PathExistScoreChecker : public BaseScoreChecker
{
    friend class boost::serialization::access;
    //void serialize<boost::archive::xml_oarchive>(boost::archive::xml_oarchive&, unsigned int);
    //template<class Archive> void serialize(Archive &ar, const unsigned int version);
    template<class Archive> void serialize(Archive &ar, const unsigned int version)
    {
        // save/load base class information

        //ar & boost::serialization::base_object<BaseScoreChecker>(*this);
        //& BOOST_SERIALIZATION_NVP(state)
        //ar.template register_type< BaseScoreChecker >();
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(BaseScoreChecker);
        ar & BOOST_SERIALIZATION_NVP(desireExist)
           & BOOST_SERIALIZATION_NVP(filepath);
        //ar & street1 & street2;
    }
protected:
    std::string filepath;
    bool desireExist;
public:
    void setFilepath(std::string newFilepath);
    std::string getFilepath();
    void setDesireExist(bool newDesireExist);
    bool getDesireExist();
    PathExistScoreChecker();
    void checkState();

};
//BOOST_CLASS_EXPORT(PathExistScoreChecker)
//BOOST_SERIALIZATION_ASSUME_ABSTRACT(BaseScoreChecker)
//BOOST_CLASS_EXPORT_GUID(PathExistScoreChecker, "PathExistScoreChecker")

#endif // FILEEXISTSCORECHECKER_H
