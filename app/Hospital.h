#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "Doctor.h"
#include "Nurse.h"
#include "Patient.h"
#include "Appointment.h"
#include "AppointmentTypes.h"
#include "Exam.h"
#include <vector>
#include <string>

class Hospital {
private:
    std::vector<Staff*> staffMembers;
    std::vector<Patient*> patients;
    std::vector<Appointment*> appointments;

public:
    Hospital();
    ~Hospital();

    void registerPatient(const std::string& id, const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& dateOfBirth);
    void displayAllPatients() const;
    Patient* findPatientById(const std::string& id) const;

    void addDoctor(const std::string& id, const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& dateOfBirth, const std::string& department, const std::string& shift, const std::string& speciality, int cabinetNumber);
    void addNurse(const std::string& id, const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& dateOfBirth, const std::string& department, const std::string& shift, const std::string& assignedWard, bool canAdministerMedication);
    
    void displayStaffByRole(const std::string& role) const;
    void displayDoctorsBySpeciality(const std::string& speciality) const;
    void bookRegularAppointment(const std::string& appointmentId, const std::string& patientId, const std::string& doctorId, const std::string& dateTime);
    void cancelAppointment(const std::string& appointmentId);
    void displayAppointments() const;
    void conductExam(const std::string& examId, const std::string& appointmentId, const std::string& diagnosis, const std::string& notes, bool issuePrescription);
    void displayPatientHistory(const std::string& patientId) const;

    void savePatients(const std::string& filename) const;
    void saveStaff(const std::string& filename) const;
    void loadPatients(const std::string& filename);
    void loadStaff(const std::string& filename);
};



#endif
