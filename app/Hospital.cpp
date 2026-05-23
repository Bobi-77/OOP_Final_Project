#include "Hospital.h"
#include <iostream>

Hospital::Hospital() {

}

Hospital::~Hospital() {
    for (Staff* staff : staffMembers) {
        delete staff;
    }
    staffMembers.clear();

    for (Patient* patient : patients) {
        delete patient;
    }
    patients.clear();

    for (Appointment* appointment : appointments) {
        delete appointment;
    }
    appointments.clear();
}

void Hospital::registerPatient(const std::string& id, const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& dateOfBirth) {
    
    if(findPatientById(id) != nullptr) {
        std::cout << "Patient with ID " << id << " already exists!" << std::endl;
        return;
    }

    try {
        Patient* newPatient = new Patient(id, firstName, lastName, phone, dateOfBirth);
        patients.push_back(newPatient);
        std::cout << "Patient " << newPatient->getFullName() << " registered successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error registering patient: " << e.what() << std::endl;
    }
}

void Hospital::displayAllPatients() const {
    if(patients.empty()) {
        std::cout << "No patients registered." << std::endl;
        return;
    }
    std::cout << "=== Registered Patients ===" << std::endl;
    for(const Patient* patient : patients) {
        patient->display();
    }
}

Patient* Hospital::findPatientById(const std::string& id) const {
    for (Patient* patient : patients) {
        if (patient->getId() == id) {
            return patient;
        }
    }
    return nullptr;
}

void Hospital::addDoctor(const std::string& id, const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& dateOfBirth, const std::string& department, const std::string& shift, const std::string& speciality, int cabinetNumber) {
    try {
        Doctor* newDoctor = new Doctor(id, firstName, lastName, phone, dateOfBirth, department, shift, speciality, cabinetNumber);
        staffMembers.push_back(newDoctor);
        std::cout << "Doctor " << newDoctor->getFullName() << " added successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error adding doctor: " << e.what() << std::endl;
    }
}

void Hospital::addNurse(const std::string& id, const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& dateOfBirth, const std::string& department, const std::string& shift, const std::string& assignedWard, bool canAdministerMedication) {
    try {
        Nurse* newNurse = new Nurse(id, firstName, lastName, phone, dateOfBirth, department, shift, assignedWard, canAdministerMedication);
        staffMembers.push_back(newNurse);
        std::cout << "Nurse " << newNurse->getFullName() << " added successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error adding nurse: " << e.what() << std::endl;
    }
}

void Hospital::displayStaffByRole(const std::string& role) const {
    bool found = false;
    std::cout << "=== Staff Members with Role: " << role << " ===" << std::endl;
    for (const Staff* staff : staffMembers) {
        if (staff->getRole() == role) {
            staff->display();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No staff members found with role: " << role << std::endl;
    }
}

void Hospital::displayDoctorsBySpeciality(const std::string& speciality) const {
    bool found = false;
    std::cout << "=== Doctors with Speciality: " << speciality << " ===" << std::endl;
    for (const Staff* staff : staffMembers) {
        if (staff->getRole() == "Doctor") {
            const Doctor* doctor = dynamic_cast<const Doctor*>(staff);
            if (doctor && doctor->getSpeciality() == speciality) {
                doctor->display();
                found = true;
            }
        }
    }
    if (!found) {
        std::cout << "No doctors found with speciality: " << speciality << std::endl;
    }
}

void Hospital::bookRegularAppointment(const std::string& appointmentId, const std::string& patientId, const std::string& doctorId, const std::string& dateTime) {
    Patient* patient = findPatientById(patientId);
    if (!patient) {
        std::cout << "Patient with ID " << patientId << " not found!" << std::endl;
        return;
    }

    Doctor* doctor = nullptr;
    for (Staff* staff : staffMembers) {
        if (staff->getRole() == "Doctor" && staff->getId() == doctorId) {
            doctor = dynamic_cast<Doctor*>(staff);
            break;
        }
    }

    if (!doctor) {
        std::cout << "Doctor with ID " << doctorId << " not found!" << std::endl;
        return;
    }

    if (!doctor->isAvailable(dateTime)) {
        std::cout << "Doctor " << doctor->getFullName() << " is not available at " << dateTime << "." << std::endl;
        return;
    }

    Appointment* newAppointment = new RegularAppointment(appointmentId, patientId, doctorId, dateTime);
    appointments.push_back(newAppointment);
    patient->addAppointment(appointmentId);
    std::cout << "Appointment booked successfully for patient " << patient->getFullName() << " with doctor " << doctor->getFullName() << " at " << dateTime << "." << std::endl;
}

void Hospital::cancelAppointment(const std::string& appointmentId) {
    for (Appointment* appointment : appointments) {
        if (appointment->getId() == appointmentId) {
            if(appointment->getStatus() == "Cancelled") {
                std::cout << "Appointment with ID " << appointmentId << " is already cancelled!" << std::endl;
                return;
            }
            appointment->cancel();
            std::cout << "Appointment with ID " << appointmentId << " has been cancelled." << std::endl;
            return;
        }
    }
    std::cout << "Appointment with ID " << appointmentId << " not found!" << std::endl;
}

void Hospital::displayAppointments() const {
    if(appointments.empty()) {
        std::cout << "No appointments scheduled." << std::endl;
        return;
    }
    std::cout << "=== Appointments ===" << std::endl;
    for (const Appointment* appointment : appointments) {
        appointment->display();
    }
}

void Hospital::conductExam(const std::string& examId, const std::string& appointmentId, const std::string& diagnosis, const std::string& notes, bool issuePrescription) {
    Appointment* currentAppointment = nullptr;
    for (Appointment* appointment : appointments) {
        if (appointment->getId() == appointmentId) {
            currentAppointment = appointment;
            break;
        }
    }

    if(!currentAppointment) {
        std::cout << "Appointment with ID " << appointmentId << " not found!" << std::endl;
        return;
    }

    if(currentAppointment->getStatus() != "Scheduled") {
        std::cout << "Error: Only scheduled appointments can be examined. Current status: " << currentAppointment->getStatus() << std::endl;
        return;
    }

    Exam* newExam = new Exam(examId, appointmentId, diagnosis, notes);

    if(issuePrescription) {
        std::string prescriptionId = "RX-" + examId;
        std::string dosage, duration, medication;

        std::cout << "--- Issuing Prescription (" << prescriptionId << ") ---" << std::endl;

        std::cout << "Enter dosage instructions: ";
        std::getline(std::cin, dosage);

        std::cout << "Enter duration: ";
        std::getline(std::cin, duration);

        Prescription prescription(prescriptionId, dosage, duration, currentAppointment->getDateTime());

        std::cout << "Enter medications (type 'done' to finish): " << std::endl;
        while (true) {
            std::cout << "Medication: ";
            std::getline(std::cin, medication);
            if (medication == "done" || medication == "Done" || medication.empty()) {
                break;
            }
            prescription.addMedication(medication);
        }

        newExam->setPrescription(prescription);
        std::cout << "Prescription generated successfully!" << std::endl;
    }

    std::cout << "Exam conducted successfully for Appointment ID: " << appointmentId << std::endl;
    newExam->display();

    Patient* patient = findPatientById(currentAppointment->getPatientId());
    if (patient) {
        std::string record = "Exam ID: " + examId + " | Diagnosis: " + diagnosis + " | Notes: " + notes + " | Date: " + currentAppointment->getDateTime();

        if(issuePrescription) {
            record += " | Prescription ID: RX-" + newExam->getExamID();
        }

        patient->addRecord(record);
    } else {
        std::cout << "Warning: Patient with ID " << currentAppointment->getPatientId() << " not found. Unable to update medical history." << std::endl;
    }
}

void Hospital::displayPatientHistory(const std::string& patientId) const {
    Patient* patient = findPatientById(patientId);
    if (!patient) {
        std::cout << "Patient with ID " << patientId << " not found!" << std::endl;
        return;
    }

    const std::vector<std::string>& history = patient->getMedicalHistory();
    
    std::cout << "\n=== MEDICAL HISTORY FOR PATIENT: " << patient->getFullName() << " ===" << std::endl;
    if (history.empty()) {
        std::cout << "No medical history records found." << std::endl;
        return;
    }

    for (size_t i = 0; i < history.size(); ++i) {
        std::cout << i + 1 << ". " << history[i] << std::endl;
    }
}

