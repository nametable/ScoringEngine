#include "valuescorechecker.h"
#include <fstream>
#include <cerrno>
ValueScoreChecker::ValueScoreChecker()
{
    this->description="Value in file";
    this->points=1;
    this->checkerType="ValueCheck";
}
void ValueScoreChecker::setFilepath(std::string newFilepath)
{
    this->filepath=newFilepath;
}
void ValueScoreChecker::setDesireExist(bool newDesireExist)
{
    this->desireExist=newDesireExist;
}
std::string ValueScoreChecker::getFilepath()
{
    return this->filepath;
}
bool ValueScoreChecker::getDesireExist()
{
    return this->desireExist;
}
void ValueScoreChecker::checkState()
{
    this->readFile();
    boost::regex expression(this->searchstring);
    this->state=(boost::regex_search(this->filecontent,expression,boost::match_any)==this->getDesireExist()); //logical xnor

    /*std::regex r(this->searchstring); // make regex
    std::smatch m;
    std::regex_search(this->filecontent, m, r);
    this->state=((m.size()>0)==this->getDesireExist()); //logical xnor
    */
    //this->state=((this->filecontent.find(this->searchstring)!= std::string::npos)==this->desireExist); //logical xnor
}
void ValueScoreChecker::readFile()
{
    this->filecontent=get_file_contents(this->filepath);
}
//http://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html
std::string get_file_contents(std::string filename)
{
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (!in.fail())
    {
      std::string contents;
      in.seekg(0, std::ios::end);
      contents.resize(in.tellg());
      in.seekg(0, std::ios::beg);
      in.read(&contents[0], contents.size());
      in.close();
      return(contents);
    }else
    {   std::cerr << "File doesnt exist or bad permissions" << std::endl;
        return "";}

}
void ValueScoreChecker::setSearchString(std::string searchstring)
{
    this->searchstring=searchstring;
}
std::string ValueScoreChecker::getSearchString()
{
    return this->searchstring;
}

