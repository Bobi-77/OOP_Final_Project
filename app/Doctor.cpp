#include "Doctor.h"
#include <iostream>
#include <sstream>

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
    std::cout << " | Speciality: " << speciality << " | Cabinet Number: " << cabinetNumber << std::endl;
}

std::string Doctor::serialize() const {
    return "Doctor;" + getId() + ";" + getFirstName() + ";" + getLastName() + ";" + getPhone() + ";" + getSpeciality();
}

std::string Doctor::getRole() const {
    return "Doctor";
}

bool Doctor::isAvailable(const std::string& dateTime) const {
    for(const std::string& booked : bookedTimes) {
        if (booked == dateTime) {
            std::cout << "Doctor " << getFullName() << " is already booked at " << dateTime << "." << std::endl;
            return false;
        }
    }

    size_t spacePos = dateTime.find(' ');
    if (spacePos != std::string::npos && spacePos + 1 < dateTime.size()) {
        std::string timePart = dateTime.substr(spacePos + 1, 2);

        try {
            int hour = std::stoi(timePart);
            
            std::string currentShift = getShift();
            if (currentShift == "Morning") {
                if(hour < 8 || hour >= 14) {
                    std::cout << "Doctor " << getFullName() << " is not on shift at " << dateTime << "." << std::endl;
                    return false;
                }
            } else if (currentShift == "Afternoon") {
                if(hour < 14 || hour >= 20) {
                    std::cout << "Doctor " << getFullName() << " is not on shift at " << dateTime << "." << std::endl;
                    return false;
                }
            } else if (currentShift == "Night") {
                if(hour < 20 && hour >= 8) {
                    std::cout << "Doctor " << getFullName() << " is not on shift at " << dateTime << "." << std::endl;
                    return false;
                }
            }
        } catch (const std::exception& e) {
            std::cout << "Invalid time format in dateTime: " << dateTime << ". Expected format: YYYY-MM-DD HH:MM" << std::endl;
            return false;
        }
    } else {
        std::cout << "Invalid dateTime format: " << dateTime << ". Expected format: YYYY-MM-DD HH:MM" << std::endl;
        return false;
    }

    return true;

}