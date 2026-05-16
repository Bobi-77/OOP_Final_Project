#include "Hospital.h"
#include <iostream>

Hospital::Hospital() {

}

Hospital::~Hospital() {
    for (Staff* staff : staffMembers) {
        delete staff;
    }
    staffMembers.clear();
    for (Patient* patient : patients) {
        delete patient;
    }
    patients.clear();
}

void Hospital::registerPatient(const std::string& id, const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& dateOfBirth) {
    
    if(findPatientById(id) != nullptr) {
        std::cout << "Patient with ID " << id << " already exists!" << std::endl;
        return;
    }

    try {
        Patient* newPatient = new Patient(id, firstName, lastName, phone, dateOfBirth);
        patients.push_back(newPatient);
        std::cout << "Patient " << newPatient->getFullName() << " registered successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error registering patient: " << e.what() << std::endl;
    }
}

void Hospital::displayAllPatients() const {
    if(patients.empty()) {
        std::cout << "No patients registered." << std::endl;
        return;
    }
    std::cout << "=== Registered Patients ===" << std::endl;
    for(const Patient* patient : patients) {
        patient->display();
    }
}

Patient* Hospital::findPatientById(const std::string& id) const {
    for (Patient* patient : patients) {
        if (patient->getId() == id) {
            return patient;
        }
    }
    return nullptr;
}

void Hospital::addDoctor(const std::string& id, const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& dateOfBirth, const std::string& department, const std::string& shift, const std::string& speciality, int cabinetNumber) {
    try {
        Doctor* newDoctor = new Doctor(id, firstName, lastName, phone, dateOfBirth, department, shift, speciality, cabinetNumber);
        staffMembers.push_back(newDoctor);
        std::cout << "Doctor " << newDoctor->getFullName() << " added successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error adding doctor: " << e.what() << std::endl;
    }
}

void Hospital::addNurse(const std::string& id, const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& dateOfBirth, const std::string& department, const std::string& shift, const std::string& assignedWard, bool canAdministerMedication) {
    try {
        Nurse* newNurse = new Nurse(id, firstName, lastName, phone, dateOfBirth, department, shift, assignedWard, canAdministerMedication);
        staffMembers.push_back(newNurse);
        std::cout << "Nurse " << newNurse->getFullName() << " added successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error adding nurse: " << e.what() << std::endl;
    }
}

void Hospital::displayStaffByRole(const std::string& role) const {
    bool found = false;
    std::cout << "=== Staff Members with Role: " << role << " ===" << std::endl;
    for (const Staff* staff : staffMembers) {
        if (staff->getRole() == role) {
            staff->display();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No staff members found with role: " << role << std::endl;
    }
}

void Hospital::displayDoctorsBySpeciality(const std::string& speciality) const {
    bool found = false;
    std::cout << "=== Doctors with Speciality: " << speciality << " ===" << std::endl;
    for (const Staff* staff : staffMembers) {
        if (staff->getRole() == "Doctor") {
            const Doctor* doctor = dynamic_cast<const Doctor*>(staff);
            if (doctor && doctor->getSpeciality() == speciality) {
                doctor->display();
                found = true;
            }
        }
    }
    if (!found) {
        std::cout << "No doctors found with speciality: " << speciality << std::endl;
    }
}