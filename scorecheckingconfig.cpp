#include "scorecheckingconfig.h"
#include <boost/serialization/nvp.hpp>
#include <iostream>
#include <fstream>
#include <QtMultimedia/qsound.h>
ScoreCheckingConfig::ScoreCheckingConfig()
{
    vecScoreCheckers= new std::vector<BaseScoreChecker *>;
    this->checkSeconds=30;
    this->Name="A New Configuration";
    this->Description="This configuration is undescribed.";
    this->Passphrase="";
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
           & BOOST_SERIALIZATION_NVP(checkSeconds)
           & BOOST_SERIALIZATION_NVP(Passphrase);
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
void ScoreCheckingConfig::GenerateScoreReport()
{
    if(this->Filename==""){this->Filename="ScoreReport.html";}
    std::ofstream fileout;
    std::string stringReport;
    int scoreNew=0;

    stringReport+="<center><h1>ScoreReport</h1></center>\n";
    for (int i=0; i< this->vecScoreCheckers->size(); i++ )
    {
        vecScoreCheckers->at(i)->checkState();
        if (vecScoreCheckers->at(i)->getState())
        {
            scoreNew+=vecScoreCheckers->at(i)->getPoints();
            stringReport+= "Fixed " ;//<< vecScoreCheckers->at(i)->getDescription() << std::to_string( vecScoreCheckers->at(i)->getPoints());
        }
    }

                  ""
                  ""
                  ""
                  ""
                  ""
                  ""
                  ""
                  "";
    fileout.open(this->Filename);
    fileout << stringReport;
    fileout.close();
    if (scoreNew> this->scoreTotal){QSound::play("://SoundFX/win.wav");}
    else if (scoreNew< this->scoreTotal) {QSound::play("://SoundFX/lose.wav");}
}
