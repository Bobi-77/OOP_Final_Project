#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
private:
    std::string id;
    std::string firstName;
    std::string lastName;
    std::string phone;
    std::string dateOfBirth;

public:
    Person();
    Person(const std::string& id, const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& dateOfBirth);

    virtual ~Person() = default;

    const std::string& getId() const;
    const std::string& getFirstName() const;
    const std::string& getLastName() const;
    std::string getFullName() const;
    const std::string& getPhone() const;
    const std::string& getDateOfBirth() const;

    void setPhone(const std::string& phone);
    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);

    virtual void display() const = 0;

    virtual std::string serialize() const = 0;
    virtual std::string getRole() const = 0;

};


#endif
