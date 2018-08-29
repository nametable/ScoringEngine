#include "runcommandscorechecker.h"
#ifdef __linux__
#include "boost/process.hpp"
#endif
RunCommandScoreChecker::RunCommandScoreChecker()
{
    this->description="Command Output Checker";
    this->points=1;
    this->checkerType="RunCommand";
    this->bSearchstringexist=true;
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
    #ifdef _WIN32
    this->commandoutput=exec(this->command.c_str());
    #elif __linux__
    boost::process::ipstream output, whicherr, whichout;
    std::string output1;
    //Check from https://stackoverflow.com/questions/890894/portable-way-to-find-out-if-a-command-exists-c-c
    if (!this->command.empty() && !boost::process::system("which " + this->command.substr(0, this->command.find(" ")),boost::process::std_err > whicherr, boost::process::std_out > whichout)){
        boost::process::system(this->command, boost::process::std_out > output);
        this->commandoutput= std::string((std::istreambuf_iterator<char>(output)), std::istreambuf_iterator<char>());
    }else{
        std::cerr << "Warning: no command \"" << this->command << "\".";
        this->commandoutput="";
    }
    #endif
}
void RunCommandScoreChecker::checkState()
{
    executeCommand();
    boost::regex expression(this->searchstring);
    this->state=(boost::regex_search(this->commandoutput,expression,boost::match_any)==this->bSearchstringexist); //logical xnor

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

