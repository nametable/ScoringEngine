/*/////
//  2018
//  BaseScoreChecker holds the basic information for all issues to be fixed
//  This class is later used in derived classes
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
    std::cerr << "Warning: Please use a derived class instead of BaseScoreChecker.\n";
}
bool BaseScoreChecker::getState()
{
    return this->state;
}
std::string BaseScoreChecker::getDescription()
{
    return this->description;
}
std::string BaseScoreChecker::getInstructions(){
    return this->instructions;
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
void BaseScoreChecker::setInstructions(std::string newInstructions){
    this->instructions = newInstructions;
}
void BaseScoreChecker::setPoints(int newPoints) //has built in max of 100 and min of -100
{
    if (newPoints>10)
    {
        this->points=100;
    }
    else if (newPoints<-10)
    {
        this->points=-100;
    }else
    {
        this->points=newPoints;

    }
}

//used as a boost process replacement for Windows - from https://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c-using-posix
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}
