#include "templatescorechecker.h"

TemplateScoreChecker::TemplateScoreChecker()
{
    this->vecScoreCheckers= new std::vector<BaseScoreChecker *>;
    this->vecBakedScoreCheckers= new std::vector<BaseScoreChecker *>;
}

void TemplateScoreChecker::checkState() //loop through checkers
{
    bool state=true;

    for (int i=0;i< this->vecScoreCheckers->size(); i++)
    {
        this->vecScoreCheckers->at(i)->checkState();
        state = (state == this->vecScoreCheckers->at(i)->getState());
    }
    this->state=state;
}
