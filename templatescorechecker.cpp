#include "templatescorechecker.h"

TemplateScoreChecker::TemplateScoreChecker()
{
    this->vecScoreCheckers= new std::vector<BaseScoreChecker *>;
    this->vecBakedScoreCheckers= new std::vector<BaseScoreChecker *>;
    this->description="Template checker";
    this->points=1;
    this->checkerType="Template";
}
void TemplateScoreChecker::checkState() //loop through checkers
{
    bool state=true;

    for (int i=0;i< this->vecBakedScoreCheckers->size(); i++)
    {
        this->vecBakedScoreCheckers->at(i)->checkState();
        state = (state == this->vecBakedScoreCheckers->at(i)->getState());
    }
    this->state=(state==getDesiredState());
}
void TemplateScoreChecker::setDesiredState(bool state)
{
    this->desiredState=state;
}
bool TemplateScoreChecker::getDesiredState()
{
    return this->desiredState;
}
