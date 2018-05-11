#include "pathexistscorechecker.h"

PathExistScoreChecker::PathExistScoreChecker()
{
    this->filepath="/home/logan/";
    this->points=1;
    this->desireExist=true;
    this->checkerType="PathExist";
}
void PathExistScoreChecker::checkState()
{
    this->state=(boost::filesystem::exists(filepath) == this->desireExist);
    //if (this->state){this->soundWin();}else{this->soundLose();}
    //no need to play sound now
}
void PathExistScoreChecker::setFilepath(std::string newFilepath)
{
    this->filepath=newFilepath;
}
void PathExistScoreChecker::setDesireExist(bool newDesireExist)
{
    this->desireExist=newDesireExist;
}
std::string PathExistScoreChecker::getFilepath()
{
    return this->filepath;
}
bool PathExistScoreChecker::getDesireExist()
{
    return this->desireExist;
}

