#ifndef EMPTYSCORECHECKER_H
#define EMPTYSCORECHECKER_H
#include "basescorechecker.h"

class EmptyScoreChecker : public BaseScoreChecker
{
    friend class boost::serialization::access;
    //template<class Archive> void serialize(Archive &ar, const unsigned int version);
    template<class Archive> void serialize(Archive &ar, const unsigned int version)
    {
        // save/load base class information
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(BaseScoreChecker);
        //ar & street1 & street2;
    }

public:
    EmptyScoreChecker();
    void checkState();
};

#endif // EMPTYSCORECHECKER_H
