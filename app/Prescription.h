#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

#include <string>
#include <vector>
#include <iostream>

class Prescription {
private:
    std::string prescriptionID;
    std::vector<std::string> medications;
    std::string dosage;
    std::string duration;
    std::string date;

public:
    Prescription();

    Prescription(const std::string& prescriptionID, const std::string& dosage, const std::string& duration, const std::string& date);

    void addMedication(const std::string& medication);
    void display() const;

    bool isEmpty() const;
};

#endif
