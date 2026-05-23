#ifndef APPOINTMENTTYPES_H
#define APPOINTMENTTYPES_H

#include "Appointment.h"
#include <string>
#include <iostream>

class RegularAppointment : public Appointment {
private:
    std::string notes;

public:
    RegularAppointment(const std::string& id, const std::string& patient, const std::string& doctor, const std::string& date, const std::string& notes="") 
    : Appointment(id, patient, doctor, date), notes(notes) {}

    void display() const override {
        Appointment::display();
        std::cout << " | Type: " << getType() << " | Notes: " << notes << std::endl;
    }

    std::string getType() const override {
        return "Regular";
    }

    void setNotes(const std::string& newNotes) {
        notes = newNotes;
    }
};

class EmergencyAppointment : public Appointment {
private:
    int priorityLevel;

public:
    EmergencyAppointment(const std::string& id, const std::string& patient, const std::string& doctor, const std::string& date, const int priorityLevel=0) 
    : Appointment(id, patient, doctor, date), priorityLevel(priorityLevel) {}

    void display() const override {
        Appointment::display();
        std::cout << " | Type: " << getType() << " | Priority Level: " << priorityLevel << std::endl;
    }

    std::string getType() const override {
        return "Emergency";
    }
};

class FollowUpAppointment : public Appointment {
private:
    std::string previousAppointmentId;

public:
    FollowUpAppointment(const std::string& id, const std::string& patient, const std::string& doctor, const std::string& date, const std::string& previousAppointmentId) 
    : Appointment(id, patient, doctor, date), previousAppointmentId(previousAppointmentId) {}

    void display() const override {
        Appointment::display();
        std::cout << " | Type: " << getType() << " | Previous Appointment ID: " << previousAppointmentId << std::endl;
    }

    std::string getType() const override {
        return "Follow-Up";
    }

    const std::string& getPreviousAppointmentId() const {
        return previousAppointmentId;
    }
};
#endif
