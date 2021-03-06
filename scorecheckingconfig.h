#ifndef SCORECHECKINGCONFIG_H
#define SCORECHECKINGCONFIG_H
#include "basescorechecker.h"
#include "pathexistscorechecker.h"
#include "emptyscorechecker.h"
#include "runcommandscorechecker.h"
#include "scriptscorechecker.h"
#include "valuescorechecker.h"
#include "questionanswerscorechecker.h"
#include "templatescorechecker.h"
#include <vector>
class ScoreCheckingConfig
{
    friend class boost::serialization::access;
    friend std::ostream & operator<<(std::ostream &os, const BaseScoreChecker &gp);
    template<class Archive>
    void serialize(Archive & ar, const unsigned int /* file_version */);

public:
    std::string Name;
    std::string Filename;
    std::string Description;
    std::string Passphrase;
    std::string ScoreReportPath;
    unsigned int checkSeconds;
    ScoreCheckingConfig();
    std::vector<BaseScoreChecker *> * vecScoreCheckers;
    void GenerateScoreReport();
private:
    bool bFixedChanged;
    int scoreTotal;
    int fixedTotal;
};

void saveConfigXML(const ScoreCheckingConfig &s, const char * filename);
void loadConfigXML(ScoreCheckingConfig &s, const char * filename);
void saveConfigBIN(const ScoreCheckingConfig &s, const char * filename);
void loadConfigBIN(ScoreCheckingConfig &s, const char * filename);

#endif // SCORECHECKINGCONFIG_H
