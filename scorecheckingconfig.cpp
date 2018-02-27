#include "scorecheckingconfig.h"
#include <boost/serialization/nvp.hpp>
ScoreCheckingConfig::ScoreCheckingConfig()
{
    vecScoreCheckers= new std::vector<BaseScoreChecker *>;
    this->checkSeconds=30;
    this->Name="A New Configuration";
    this->Description="This configuration is undescribed.";
}
template<class Archive> void ScoreCheckingConfig::serialize(Archive &ar, const unsigned int /* file_version */)
{
        //ar.template register_type<PathExistScoreChecker>();
        ar.register_type(static_cast<EmptyScoreChecker *>(NULL));
        ar.register_type(static_cast<PathExistScoreChecker *>(NULL));
        ar.register_type(static_cast<RunCommandScoreChecker *>(NULL));
        ar.register_type(static_cast<ScriptScoreChecker *>(NULL));
        ar.register_type(static_cast<ValueScoreChecker *>(NULL));
        ar & BOOST_SERIALIZATION_NVP(vecScoreCheckers)
           & BOOST_SERIALIZATION_NVP(Name)
           & BOOST_SERIALIZATION_NVP(Description)
           & BOOST_SERIALIZATION_NVP(checkSeconds);
            //& BOOST_SERIALIZATION_NVP(Scans);

}

void saveConfigXML(const ScoreCheckingConfig &s, const char * filename){ //from example code
    // make an archive
    std::ofstream ofs(filename);
    assert(ofs.good());
    boost::archive::xml_oarchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(s);
}
void loadConfigXML(ScoreCheckingConfig &s, const char * filename) //from example code
{
    // open the archive
    std::ifstream ifs(filename);
    assert(ifs.good());
    boost::archive::xml_iarchive ia(ifs);
    // restore the schedule from the archive
    ia >> BOOST_SERIALIZATION_NVP(s);
}
void saveConfigBIN(const ScoreCheckingConfig &s, const char * filename){ //from example code
    // make an archive
    std::ofstream ofs(filename);
    assert(ofs.good());
    boost::archive::binary_oarchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(s);
}
void loadConfigBIN(ScoreCheckingConfig &s, const char * filename) //from example code
{
    // open the archive
    std::ifstream ifs(filename);
    assert(ifs.good());
    boost::archive::binary_iarchive ia(ifs);
    // restore the schedule from the archive
    ia >> BOOST_SERIALIZATION_NVP(s);
}
