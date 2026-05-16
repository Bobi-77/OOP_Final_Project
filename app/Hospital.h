#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "Doctor.h"
#include "Nurse.h"
#include "Patient.h"
#include <vector>
#include <string>

class Hospital {
private:
    std::vector<Staff*> staffMembers;
    std::vector<Patient*> patients;

public:
    Hospital();
    ~Hospital();

    void registerPatient(const std::string& id, const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& dateOfBirth);
    void displayAllPatients() const;
    Patient* findPatientById(const std::string& id) const;

    void addDoctor(const std::string& id, const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& dateOfBirth, const std::string& department, const std::string& shift, const std::string& speciality, int cabinetNumber);
    void addNurse(const std::string& id, const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& dateOfBirth, const std::string& department, const std::string& shift, const std::string& assignedWard, bool canAdministerMedication);
    
    void displayStaffByRole(const std::string& role) const;
    void displayDoctorsBySpeciality(const std::string& speciality) const;
};


#endif
