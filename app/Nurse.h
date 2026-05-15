#ifndef NURSE_H
#define NURSE_H

#include "Staff.h"
#include <string>

class Nurse : public Staff {
private:
    std::string assignedWard;
    bool canAdministerMedication;

public:
    Nurse();
    Nurse(const std::string& id, const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& dateOfBirth, const std::string& department, const std::string& shift, const std::string& assignedWard, bool canAdministerMedication);

    const std::string& getAssignedWard() const;
    bool getCanAdministerMedication() const;

    void setAssignedWard(const std::string& assignedWard);
    void setCanAdministerMedication(bool canAdministerMedication);

    void display() const override;
    std::string serialize() const override;
    std::string getRole() const override;

    void assistApointment(const std::string& appointmentId) const;

};


#endif
