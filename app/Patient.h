#ifndef PATIENT_H
#define PATIENT_H

#include "Person.h"
#include <string>
#include <vector>

class Patient : public Person {
private:
    std::vector<std::string> medicalHistory;
    std::vector<std::string> activeAppointments;
    
public:
    Patient();
    Patient(const std::string& id, const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& dateOfBirth);

    void display() const override;
    std::string serialize() const override;
    std::string getRole() const override;

    void addRecord(const std::string& record);
    void addAppointment(const std::string& appointmentId);

    const std::vector<std::string>& getMedicalHistory() const;
    const std::vector<std::string>& getActiveAppointments() const;

};


#endif
