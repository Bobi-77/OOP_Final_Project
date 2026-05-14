#include "Person.h"
#include <stdexcept>

Person::Person() : id(0), firstName(""), lastName(""), phone(""){

}

Person::Person(int id, const std::string& firstName, const std::string& lastName, const std::string& phone) 
    : id(id), firstName(firstName), lastName(lastName) {

    setPhone(phone);
}

int Person::getId() const {
    return id;
}

const std::string& Person::getFirstName() const {
    return firstName;
}

const std::string& Person::getLastName() const {
    return lastName;
}

std::string Person::getFullName() const {
    return firstName + " " + lastName;
}

const std::string& Person::getPhone() const {
    return phone;
}

void Person::setPhone(const std::string& newPhone){
    if (newPhone.length() != 10) {
        throw std::invalid_argument("Invalid phone number! It must be 10 symblos");
    }

    for(int i = 0; i < newPhone.length(); i++){
        char current = newPhone[i];

        if(current < '0' || current > '9') {
            throw std::invalid_argument("Invalid phone number! It must contain only numbers");
        }
    }

    phone = newPhone;
}