#ifndef TEMPLATESCORECHECKER_H
#define TEMPLATESCORECHECKER_H
#include "basescorechecker.h"
class TemplateScoreChecker : public BaseScoreChecker
{
    friend class boost::serialization::access;
    //template<class Archive> void serialize(Archive &ar, const unsigned int version);
    template<class Archive> void serialize(Archive &ar, const unsigned int version)
    {
        // save/load base class information
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(BaseScoreChecker);
        ar & BOOST_SERIALIZATION_NVP(vecScoreCheckers);

    }
protected:
    std::vector<BaseScoreChecker*> *vecBakedScoreCheckers;
    std::vector<BaseScoreChecker*> *vecScoreCheckers;
public:
    TemplateScoreChecker();
    void checkState();
};

#endif // TEMPLATESCORECHECKER_H
