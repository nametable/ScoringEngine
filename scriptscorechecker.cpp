#include "scriptscorechecker.h"
#include "boost/filesystem.hpp"
#include "boost/process.hpp"
ScriptScoreChecker::ScriptScoreChecker()
{
    this->description="Run script and parse output";
    this->points=1;
    this->checkerType="RunScript";
}
void ScriptScoreChecker::setScript(std::string script)
{
    this->script=script;
}
std::string ScriptScoreChecker::getScript()
{
    return this->script;
}
void ScriptScoreChecker::setSearchString(std::string searchString)
{
    this->searchString=searchString;
}
std::string ScriptScoreChecker::getSearchString()
{
    return this->searchString;
}
void ScriptScoreChecker::setDesiredState(bool state)
{
    this->desiredState=state;
}
bool ScriptScoreChecker::getDesiredState()
{
    return this->desiredState;
}
void ScriptScoreChecker::checkState()
{
    this->execute();
    boost::regex expression(this->searchString);
    this->state=(boost::regex_search(this->getOutput(),expression,boost::match_any)==this->desiredState); //logical xnor

    /*std::regex r(this->searchString); // make regex
    std::smatch m;
    std::regex_search(this->scriptOutput, m, r);
    this->state=((m.size()>0)==this->desiredState); //logical xnor
    */
    //old - non regex
    //this->state=((this->scriptOutput.find(this->searchString)!= std::string::npos)==this->desiredState); //logical xnor
}
std::string ScriptScoreChecker::getOutput()
{
    return this->scriptOutput;
}
void ScriptScoreChecker::execute()
{
    gen_scriptrun_directory();
    std::string sfilename;
    std::string file = "bash";
    std::string ScriptExtension=".sh";
    //file osfile.str();
    sfilename=boost::filesystem::current_path().string() + "/tmp/" + file + ScriptExtension;

    //std::cout << sfilename << std::endl;
    if (!std::ifstream(sfilename)) //check for existence of file
    {
        std::ofstream ofs;
        ofs.open(sfilename); //open file for writing
        ofs << this->script;
        ofs.close();
    }else{std::cerr << "bash.sh already exists- FIX!" << std::endl;} //error if there is already a file

    if (ScriptExtension==".sh")boost::process::system("chmod +x " + sfilename); //make script executable

    boost::process::ipstream output;
    boost::process::system(sfilename, boost::process::std_out > output);
    this->scriptOutput= std::string((std::istreambuf_iterator<char>(output)), std::istreambuf_iterator<char>());

    boost::filesystem::remove_all(sfilename); //removes the script now that execution is done
}
bool gen_scriptrun_directory() //creates the runs/scans directory using boost
{
    //boost::filesystem::path appPath(boost::filesystem::canonical(boost::filesystem::system_complete(argv[0])).parent_path());
    if(boost::filesystem::create_directories("tmp")) {
        //std::cout << "Success" << "\n";
        return true;
    }
    return false;
}
