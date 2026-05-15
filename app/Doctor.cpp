#include "Doctor.h"
#include <iostream>

Doctor::Doctor() : Staff(), speciality(""), cabinetNumber(0) {

}

Doctor::Doctor(const std::string& id, const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& dateOfBirth, const std::string& department, const std::string& shift, const std::string& speciality, int cabinetNumber) 
    : Staff(id, firstName, lastName, phone, dateOfBirth, department, shift), speciality(speciality), cabinetNumber(cabinetNumber) {

}

const std::string& Doctor::getSpeciality() const {
    return speciality;
}

int Doctor::getCabinetNumber() const {
    return cabinetNumber;
}

void Doctor::setSpeciality(const std::string& newSpeciality) {
    speciality = newSpeciality;
}

void Doctor::setCabinetNumber(int newCabinetNumber) {
    cabinetNumber = newCabinetNumber;
}

void Doctor::display() const {
    Staff::display();
    std::cout << " | Speciality: " << speciality << " | Cabinet Number: " << cabinetNumber;
}

std::string Doctor::serialize() const {
    return "Doctor;" + getId() + ";" + getFirstName() + ";" + getLastName() + ";" + getPhone() + ";" + getSpeciality();
}

std::string Doctor::getRole() const {
    return "Doctor";
}

bool Doctor::isAvailable(const std::string& dt) const {
    return true;
}