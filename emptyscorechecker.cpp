#include "emptyscorechecker.h"

EmptyScoreChecker::EmptyScoreChecker()
{
    this->setDescription("Select a type");
    this->points=0;
    this->checkerType="";
}
void EmptyScoreChecker::checkState()
{
    std::cout << "This is an empty checker. Please select a real one.\n";
}
