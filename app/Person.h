#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
private:
    int id;
    std::string firstName;
    std::string lastName;
    std::string phone;

public:
    Person();
    Person(int id, const std::string& firstName, const std::string& lastname, const std::string& phone);

    virtual ~Person() = default;

    int getId() const;
    const std::string& getFirstName() const;
    const std::string& getLastName() const;
    std::string getFullName() const;
    const std::string& getPhone() const;

    void setPhone(const std::string& phone);

    virtual void display() const = 0;

    virtual std::string serialize() const = 0;
    virtual std::string getRole() const = 0;

};


#endif
