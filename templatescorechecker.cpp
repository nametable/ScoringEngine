#include "templatescorechecker.h"

TemplateScoreChecker::TemplateScoreChecker()
{
    this->vecScoreCheckers= new std::vector<BaseScoreChecker *>;
    this->vecBakedScoreCheckers= new std::vector<BaseScoreChecker *>;
}

void TemplateScoreChecker::checkState() //loop through checkers
{
    bool state=true;
    for (BaseScoreChecker checker:this->vecScoreCheckers)
    {
        checker.checkState();
        state = (state == checker.getState());
    }
    this->state=state;
}
