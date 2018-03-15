/*/////
//  Copyright Logan Bateman 2018
//
//
/////*/
#include "basescorechecker.h"
//#include "pathexistscorechecker.h"
BaseScoreChecker::BaseScoreChecker()
{
    this->state=false;
    this->description="Base score checker";
}
BaseScoreChecker::BaseScoreChecker(std::string description)
{
    this->state=false;
    this->description=description;
}
void BaseScoreChecker::checkState(){
    std::cout << "Please use a derived class.\n";
}
bool BaseScoreChecker::getState()
{
    return this->state;
}
std::string BaseScoreChecker::getDescription()
{
    return this->description;
}
std::string BaseScoreChecker::getCheckerType()
{
    return this->checkerType;
}
int BaseScoreChecker::getPoints()
{
    return this->points;
}
void BaseScoreChecker::setDescription(std::string newDescription)
{
    this->description=newDescription;
}
void BaseScoreChecker::setPoints(int newPoints) //has built in max of 10 and min of -10
{
    if (newPoints>10)
    {
        this->points=10;
    }
    else if (newPoints<-10)
    {
        this->points=-10;
    }else
    {
        this->points=newPoints;
    }
}

