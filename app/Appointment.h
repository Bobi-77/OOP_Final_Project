#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>

class Appointment {
private:
    std::string appointmentId;
    std::string patientId;
    std::string doctorId;
    std::string dateTime;
    std::string status;
public:
    Appointment(const std::string& id, const std::string& patient, const std::string& doctor, const std::string& date);
    
    virtual ~Appointment() = default;

    const std::string& getId() const;
    const std::string& getPatientId() const;
    const std::string& getDoctorId() const;
    const std::string& getDateTime() const;
    const std::string& getStatus() const;

    void cancel();

    virtual void display() const;
    virtual std::string getType() const = 0;
};

#endif
