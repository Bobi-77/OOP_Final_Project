#ifndef EXAM_H
#define EXAM_H

#include <string>
#include "Prescription.h"

class Exam {
private:
    std::string examID;
    std::string appointmentID;
    std::string diagnosis;
    std::string notes;
    Prescription prescription;

public:
    Exam();

    Exam(const std::string& examID, const std::string& appointmentID, const std::string& diagnosis, const std::string& notes);

    void setPrescription(const Prescription& prescription);

    const std::string& getExamID() const;
    const std::string& getAppointmentID() const;
    const std::string& getDiagnosis() const;

    void display() const;
};

#endif
