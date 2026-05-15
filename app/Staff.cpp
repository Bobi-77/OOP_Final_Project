#include "Staff.h"
#include <iostream>

Staff::Staff() : Person(), department(""), shift("") {

}

Staff::Staff(const std::string& id, const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& dateOfBirth, const std::string& department, const std::string& shift) 
    : Person(id, firstName, lastName, phone, dateOfBirth), department(department), shift(shift) {

}

const std::string& Staff::getDepartment() const {
    return department;
}

const std::string& Staff::getShift() const {
    return shift;
}

void Staff::setDepartment(const std::string& newDepartment) {
    department = newDepartment;
}

void Staff::setShift(const std::string& newShift) {
    shift = newShift;
}

void Staff::display() const {
    std::cout << "ID: " << getId() << " | Name: " << getFullName()
    << " | Phone: " << getPhone() << " | DOB: " << getDateOfBirth()
    << " | Department: " << department << " | Shift: " << shift << std::endl;
}