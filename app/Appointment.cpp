#include "Appointment.h"
#include <iostream>

Appointment::Appointment(const std::string& id, const std::string& patient, const std::string& doctor, const std::string& date)
    : appointmentId(id), patientId(patient), doctorId(doctor), dateTime(date), status("Scheduled") {

}

const std::string& Appointment::getId() const {
    return appointmentId;
}

const std::string& Appointment::getPatientId() const {
    return patientId;
}

const std::string& Appointment::getDoctorId() const {
    return doctorId;
}

const std::string& Appointment::getDateTime() const {
    return dateTime;
}

const std::string& Appointment::getStatus() const {
    return status;
}

void Appointment::cancel() {
    status = "Cancelled";
}

void Appointment::display() const {
    std::cout << "Appointment ID: " << appointmentId
        << " | Patient ID: " << patientId
        << " | Doctor ID: " << doctorId
        << " | Date & Time: " << dateTime
        << " | Status: " << status << std::endl;
}