#ifndef QUESTIONSCORECHECKER_H
#define QUESTIONSCORECHECKER_H
#include "basescorechecker.h"
enum QuestionType{
    MULTIPLE_CHOICE, SHORT_ANSWER
};

class QuestionAnswerScoreChecker : public BaseScoreChecker
{
    friend class boost::serialization::access;
    template<class Archive> void serialize(Archive &ar, const unsigned int version)
    {
        // save/load base class information
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(BaseScoreChecker);
        //ar & BOOST_SERIALIZATION_NVP(desireExist)
        //   & BOOST_SERIALIZATION_NVP(filepath);
        //ar & street1 & street2;
    }
protected:
    std::string strQuestion;
    int numAnswerMultipleChoice;
    int strAnswerShort;
public:
    QuestionAnswerScoreChecker();
    void checkState();
    void setQuestionType(QuestionType type);
    void setAnswerMultipleChoice(int);
    void setAnswerShort(std::string answer);
    std::string getAnswerShort();
    std::vector<std::string> vecAnswersMultipleChoice;
    void addPossibleAnswer(std::string);
};

#endif // QUESTIONSCORECHECKER_H
