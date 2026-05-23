#ifndef DOCTOR_H
#define DOCTOR_H

#include "Staff.h"
#include <string>
#include <vector>

class Doctor : public Staff {
private:
    std::string speciality;
    int cabinetNumber;
    std::vector<std::string> bookedTimes;

public:
    Doctor();
    Doctor(const std::string& id, const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& dateOfBirth, const std::string& department, const std::string& shift, const std::string& speciality, int cabinetNumber);

    const std::string& getSpeciality() const;
    int getCabinetNumber() const;

    void setSpeciality(const std::string& speciality);
    void setCabinetNumber(int cabinetNumber);

    void display() const override;

    std::string serialize() const override;
    std::string getRole() const override;

    void addBookedTime(const std::string& dateTime) {
        bookedTimes.push_back(dateTime);
    }
    bool isAvailable(const std::string& dateTime) const;
};


#endif
