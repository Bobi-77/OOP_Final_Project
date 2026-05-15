#include "Patient.h"
#include <iostream>

Patient::Patient() : Person() {

}

Patient::Patient(const std::string& id, const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& dateOfBirth)
    : Person(id, firstName, lastName, phone, dateOfBirth) {
}

void Patient::display() const {
    std::cout << "ID: " << getId() << " | Name: " << getFullName()
        << " | Phone: " << getPhone() << " | DOB: " << getDateOfBirth() << "|Records: " << medicalHistory.size() << "|Appointments: " << activeAppointments.size() << std::endl;
}

std::string Patient::serialize() const {
    return "Patient;" + getId() + ";" + getFirstName() + ";" + getLastName() + ";" + getPhone() + ";" + getDateOfBirth();
}

std::string Patient::getRole() const {
    return "Patient";
}

void Patient::addRecord(const std::string& record) {
    medicalHistory.push_back(record);
}

void Patient::addAppointment(const std::string& appointmentId) {
    activeAppointments.push_back(appointmentId);
}

const std::vector<std::string>& Patient::getMedicalHistory() const {
    return medicalHistory;
}

const std::vector<std::string>& Patient::getActiveAppointments() const {
    return activeAppointments;
}
