#ifndef TEMPLATESCORECHECKER_H
#define TEMPLATESCORECHECKER_H
#include "basescorechecker.h"
#include <QMetaType>
class TemplateScoreChecker : public BaseScoreChecker
{
    friend class boost::serialization::access;
    //template<class Archive> void serialize(Archive &ar, const unsigned int version);
    template<class Archive> void serialize(Archive &ar, const unsigned int version)
    {
        // save/load base class information
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(BaseScoreChecker);
        ar & BOOST_SERIALIZATION_NVP(desiredState)
                & BOOST_SERIALIZATION_NVP(vecScoreCheckers);
    }
protected:
    std::vector<BaseScoreChecker*> *vecBakedScoreCheckers;
    std::vector<BaseScoreChecker*> *vecScoreCheckers;
    bool desiredState;

public:
    TemplateScoreChecker();
    void checkState();
    void setDesiredState(bool state);
    bool getDesiredState();
    void bakeScoreCheckers(std::vector<int> checkerIndex={});
};
Q_DECLARE_METATYPE(TemplateScoreChecker*)
#endif // TEMPLATESCORECHECKER_H
