#include "Prescription.h"

Prescription::Prescription() : prescriptionID(""), dosage(""), duration(""), date("") {

}

Prescription::Prescription(const std::string& prescriptionID, const std::string& dosage, const std::string& duration, const std::string& date) 
    : prescriptionID(prescriptionID), dosage(dosage), duration(duration), date(date) {

}

void Prescription::addMedication(const std::string& medication) {
    medications.push_back(medication);
}

bool Prescription::isEmpty() const {
    return prescriptionID.empty();
}

void Prescription::display() const {
    if (isEmpty()) {
        std::cout << "No prescription details available." << std::endl;
        return;
    }

    std::cout << "Prescription ID: " << prescriptionID << std::endl;
    std::cout << "Dosage: " << dosage << std::endl;
    std::cout << "Duration: " << duration << std::endl;
    std::cout << "Date: " << date << std::endl;

    if (medications.empty()) {
        std::cout << "No medications prescribed." << std::endl;
    } else {
        std::cout << "Medications:" << std::endl;
        for (const std::string& medication : medications) {
            std::cout << " - " << medication << std::endl;
        }
    }
}

