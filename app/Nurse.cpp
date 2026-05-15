#include "Nurse.h"
#include <iostream>

Nurse::Nurse() : Staff(), assignedWard(""), canAdministerMedication(false) {

}

Nurse::Nurse(const std::string& id, const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& dateOfBirth, const std::string& department, const std::string& shift, const std::string& assignedWard, bool canAdministerMedication) 
    : Staff(id, firstName, lastName, phone, dateOfBirth, department, shift), assignedWard(assignedWard), canAdministerMedication(canAdministerMedication) {

}

const std::string& Nurse::getAssignedWard() const {
    return assignedWard;
}

bool Nurse::getCanAdministerMedication() const {
    return canAdministerMedication;
}

void Nurse::setAssignedWard(const std::string& newAssignedWard) {
    assignedWard = newAssignedWard;
}

void Nurse::setCanAdministerMedication(bool newCanAdministerMedication) {
    canAdministerMedication = newCanAdministerMedication;
}

void Nurse::display() const {
    Staff::display();
    std::cout << " | Assigned Ward: " << assignedWard << " | Can Administer Medication: " << (canAdministerMedication ? "Yes" : "No") << std::endl;
}

std::string Nurse::serialize() const {
    return "Nurse;" + getId() + ";" + getFirstName() + ";" + getLastName() + ";" + getPhone() + ";" + assignedWard + ";" + (canAdministerMedication ? "1" : "0");
}

std::string Nurse::getRole() const {
    return "Nurse";
}

void Nurse::assistApointment(const std::string& appointmentId) const {
    std::cout << "Nurse " << getFullName() << " is assisting with Appointment ID: " << appointmentId << std::endl;
}