#include "runcommandscorechecker.h"
#include <boost/process.hpp>
RunCommandScoreChecker::RunCommandScoreChecker()
{
    this->description="Command Output Checker";
    this->points=1;
    this->checkerType="RunCommand";
}
void RunCommandScoreChecker::setCommand(std::string command)
{
    this->command=command;
}
std::string RunCommandScoreChecker::getCommand()
{
    return this->command;
}
std::string RunCommandScoreChecker::getCommandOutput()
{
    return this->commandoutput;
}
void RunCommandScoreChecker::executeCommand()
{
    //INSERT BOOST CODE HERE
    boost::process::ipstream output;
    std::string output1;
    boost::process::system(this->command, boost::process::std_out > output);
    //output.
    this->commandoutput= std::string((std::istreambuf_iterator<char>(output)), std::istreambuf_iterator<char>());
    //this->commandoutput= output.
}
void RunCommandScoreChecker::checkState()
{
    executeCommand();
    std::regex r(this->searchstring); // make regex
    std::smatch m;
    std::regex_search(this->commandoutput, m, r);
    this->state=((m.size()>0)==this->bSearchstringexist); //logical xnor
    //old non regex
    //this->state=((this->commandoutput.find(this->searchstring)!= std::string::npos)==this->bSearchstringexist); //logical xnor
}
void RunCommandScoreChecker::setSearchExist(bool exist)
{
    this->bSearchstringexist=exist;
}
bool RunCommandScoreChecker::getSearchExist()
{
    return bSearchstringexist;
}
void RunCommandScoreChecker::setSearchString(std::string searchstring)
{
    this->searchstring=searchstring;
}
std::string RunCommandScoreChecker::getSearchString()
{
    return this->searchstring;
}

