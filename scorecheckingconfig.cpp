#include "scorecheckingconfig.h"
#include <boost/serialization/nvp.hpp>
#include <iostream>
#include <fstream>
#include <time.h>       /* time_t, struct tm, time, localtime, strftime */
#ifdef __linux__
#include "boost/process.hpp"
#endif
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
           & BOOST_SERIALIZATION_NVP(Passphrase)
           & BOOST_SERIALIZATION_NVP(scoreTotal);
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
    std::string stringTable;
    int possiblePoints=0;
    int possibleIssues=0;
    int scoreNew=0;
    this->fixedTotal=0;

    //**** Get the current time and next score check time
    time_t rawtime;
    time_t nexttime;
      struct tm * timeinfo;
      char buffer [80];
    time (&rawtime);
    nexttime = rawtime + this->checkSeconds;
    timeinfo = localtime (&nexttime);
    //      Sep 5, 2018 15:37:25
    strftime (buffer,80,"%b %d, %Y %T",timeinfo);
    std::string stringtime(buffer);
    //****

    stringReport+="<center><h1>"+ this->Name +"</h1><h2 id=\"timeleft\">Checking ...</h2>";
    stringTable+="<table>";
    for (int i=0; i< this->vecScoreCheckers->size(); i++ )
    {
        vecScoreCheckers->at(i)->checkState();
        if (vecScoreCheckers->at(i)->getState())
        {
            scoreNew+=vecScoreCheckers->at(i)->getPoints();
            this->fixedTotal++;
            if ( vecScoreCheckers->at(i)->getPoints()>=0)
            {
                stringTable+= "<tr><td>Fixed: " + vecScoreCheckers->at(i)->getDescription() + "</td><td>" + std::to_string( vecScoreCheckers->at(i)->getPoints()) + "pt(s)</td>\n";
            }else {
                stringTable+= "<tr style='color:red'><td>Penalty: " + vecScoreCheckers->at(i)->getDescription() + "</td><td>" + std::to_string( vecScoreCheckers->at(i)->getPoints()) + "pt(s)</td>\n";
            }
        }
        if (vecScoreCheckers->at(i)->getPoints()>0) //if this is a good issue
        {
            possiblePoints+=vecScoreCheckers->at(i)->getPoints();
            possibleIssues++;
        }
    }
    stringTable+="</table>";
    stringReport+="<h2>"+ std::to_string(this->fixedTotal) +"/"+ std::to_string(possibleIssues) +" issues ("+std::to_string(this->fixedTotal*100/possibleIssues) +"%) | "+std::to_string(scoreNew) + "/"+std::to_string(possiblePoints)+" pts ("+ std::to_string(scoreNew*100/possiblePoints)+ "%)</h2>";
    stringReport+=stringTable;
    stringReport+=""
                  ""
                  ""
                  ""
                  ""
                  ""
                  ""
                  ""
                  "<br><br><b>Copyright 2018 Logan Bateman</b></center>"
                  "<script> var countDownDate = new Date(\"" + stringtime +"\").getTime();var x = setInterval(function() {var now = new Date().getTime();var distance = countDownDate - now;if (distance <= 1000) {location.reload();};document.getElementById(\"timeleft\").innerHTML = \"Refresh in \" + (Math.floor(distance/1000)) + \" seconds\";}, 1000);</script>";
    fileout.open(this->Filename);
    fileout << stringReport;
    fileout.close();
    #ifdef __linux__ //no aplay or usable boost in windows
    if (scoreNew> this->scoreTotal){ boost::process::system("aplay SoundFX/win.wav");} //QSound::play("://SoundFX/win.wav");}
    else if (scoreNew< this->scoreTotal) {boost::process::system("aplay SoundFX/lose.wav");}
    #endif
    this->scoreTotal=scoreNew;
}
