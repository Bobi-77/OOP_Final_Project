#ifndef STAFF_H
#define STAFF_H

#include "Person.h"
#include <string>

class Staff : public Person {
private:
    std::string department;
    std::string shift;

public:
    Staff();
    Staff(const std::string& id, const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& dateOfBirth, const std::string& department, const std::string& shift);

    virtual ~Staff() = default;

    const std::string& getDepartment() const;
    const std::string& getShift() const;

    void display() const override;
};


#endif
