#include "Exam.h"
#include <iostream>

Exam::Exam() : examID(""), appointmentID(""), diagnosis(""), notes("") {

}

Exam::Exam(const std::string& examID, const std::string& appointmentID, const std::string& diagnosis, const std::string& notes) 
    : examID(examID), appointmentID(appointmentID), diagnosis(diagnosis), notes(notes) {

}

void Exam::setPrescription(const Prescription& prescription) {
    this->prescription = prescription;
}

const std::string& Exam::getExamID() const {
    return examID;
}

const std::string& Exam::getAppointmentID() const {
    return appointmentID;
}

const std::string& Exam::getDiagnosis() const {
    return diagnosis;
}

void Exam::display() const {
    std::cout << "Exam : " << examID << std::endl;
    std::cout << "For Appointment ID: " << appointmentID << std::endl;
    std::cout << "Diagnosis: " << diagnosis << std::endl;
    std::cout << "Notes: " << notes << std::endl;

    if (!prescription.isEmpty()) {
        std::cout << "Prescription Details:" << std::endl;
        prescription.display();
    } else {
        std::cout << "No prescription associated with this exam." << std::endl;
    }
}