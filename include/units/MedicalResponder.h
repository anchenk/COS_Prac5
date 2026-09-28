#ifndef CAMPUSGUARD_MEDICALRESPONDER_H
#define CAMPUSGUARD_MEDICALRESPONDER_H

#include "ResponseUnit.h"

class MedicalResponder : public ResponseUnit
{
public:
    MedicalResponder(const std::string &name, IIncidentMediator *mediator);

    void dispatch(const std::string &location) override;
    void recall() override;
    std::string getStatus() const override;

private:
    bool deployed = false;
    std::string location;
};

#endif