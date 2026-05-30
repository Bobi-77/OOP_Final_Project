#include "Hospital.h"
#include <iostream>
#include <fstream>
#include <sstream>

Hospital::Hospital() {
    loadPatients("patients.txt");
    loadStaff("staff.txt");
    loadAppointments("appointments.txt");
}

Hospital::~Hospital() {
    savePatients("patients.txt");
    saveStaff("staff.txt");
    saveAppointments("appointments.txt");

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
        savePatients("patients.txt");
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
        saveStaff("staff.txt");
    } catch (const std::exception& e) {
        std::cout << "Error adding doctor: " << e.what() << std::endl;
    }
}

void Hospital::addNurse(const std::string& id, const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& dateOfBirth, const std::string& department, const std::string& shift, const std::string& assignedWard, bool canAdministerMedication) {
    try {
        Nurse* newNurse = new Nurse(id, firstName, lastName, phone, dateOfBirth, department, shift, assignedWard, canAdministerMedication);
        staffMembers.push_back(newNurse);
        std::cout << "Nurse " << newNurse->getFullName() << " added successfully!" << std::endl;
        saveStaff("staff.txt");
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

    Appointment* newAppointment = new RegularAppointment(appointmentId, patientId, doctorId, dateTime);
    appointments.push_back(newAppointment);
    patient->addAppointment(appointmentId);

    doctor->addBookedTime(dateTime);

    std::cout << "Appointment booked successfully for patient " << patient->getFullName() << " with doctor " << doctor->getFullName() << " at " << dateTime << "." << std::endl;
    saveAppointments("appointments.txt");
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
            saveAppointments("appointments.txt");
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
        savePatients("patients.txt");
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

void Hospital::savePatients(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file for saving patients: " << filename << std::endl;
        return;
    }

    for (const Patient* patient : patients) {
        file << patient->getId() << ";" << patient->getFirstName() << ";" << patient->getLastName() << ";" << patient->getPhone() << ";" << patient->getDateOfBirth() << std::endl;
    
        const std::vector<std::string>& history = patient->getMedicalHistory();
            for (size_t i = 0; i < history.size(); ++i) {
                file << history[i];
                if (i < history.size() - 1) {
                    file << "|";
                }
            }
        file << std::endl;
    }
    file.close();
}

void Hospital::saveStaff(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file for saving staff: " << filename << std::endl;
        return;
    }

    for (const Staff* staff : staffMembers) {
        if(staff->getRole() == "Doctor") {
            const Doctor* doctor = dynamic_cast<const Doctor*>(staff);
            file << "Doctor;" << doctor->getId() << ";" << doctor->getFirstName() << ";" << doctor->getLastName() << ";" << doctor->getPhone() << ";" << doctor->getDateOfBirth() << ";" << doctor->getDepartment() << ";" << doctor->getShift() << ";" << doctor->getSpeciality() << ";" << doctor->getCabinetNumber() << std::endl;
        } else if(staff->getRole() == "Nurse") {
            const Nurse* nurse = dynamic_cast<const Nurse*>(staff);
            file << "Nurse;" << nurse->getId() << ";" << nurse->getFirstName() << ";" << nurse->getLastName() << ";" << nurse->getPhone() << ";" << nurse->getDateOfBirth() << ";" << nurse->getDepartment() << ";" << nurse->getShift() << ";" << nurse->getAssignedWard() << ";" << (nurse->getCanAdministerMedication() ? "1" : "0") << std::endl;
        }
    }
    file.close();
}

void Hospital::loadPatients(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "No existing patient data found." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if(line.empty()) continue;

        std::istringstream ss(line);
        std::string id, firstName, lastName, phone, dateOfBirth, historyStr;

        std::getline(ss, id, ';');
        std::getline(ss, firstName, ';');
        std::getline(ss, lastName, ';');
        std::getline(ss, phone, ';');
        std::getline(ss, dateOfBirth, ';');
        std::getline(ss, historyStr, ';');

        if(!id.empty() && !firstName.empty() && !lastName.empty()) {
            Patient* patient = new Patient(id, firstName, lastName, phone, dateOfBirth);
            
            if (!historyStr.empty()) {
                std::istringstream historyStream(historyStr);
                std::string record;
                while (std::getline(historyStream, record, '|')) {
                    patient->addRecord(record);
                }
            }

            patients.push_back(patient);
        }
    }
    file.close();
}

void Hospital::loadStaff(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "No existing staff data found." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if(line.empty()) continue;

        std::istringstream ss(line);
        std::string role;
        std::getline(ss, role, ';');

        if (role == "Doctor") {
            std::string id, firstName, lastName, phone, dateOfBirth, department, shift, speciality;
            int cabinetNumber;

            std::getline(ss, id, ';');
            std::getline(ss, firstName, ';');
            std::getline(ss, lastName, ';');
            std::getline(ss, phone, ';');
            std::getline(ss, dateOfBirth, ';');
            std::getline(ss, department, ';');
            std::getline(ss, shift, ';');
            std::getline(ss, speciality, ';');
            ss >> cabinetNumber;

            Doctor* doctor = new Doctor(id, firstName, lastName, phone, dateOfBirth, department, shift, speciality, cabinetNumber);
            staffMembers.push_back(doctor);
        } else if (role == "Nurse") {
            std::string id, firstName, lastName, phone, dateOfBirth, department, shift, assignedWard;
            bool canAdministerMedication;

            std::getline(ss, id, ';');
            std::getline(ss, firstName, ';');
            std::getline(ss, lastName, ';');
            std::getline(ss, phone, ';');
            std::getline(ss, dateOfBirth, ';');
            std::getline(ss, department, ';');
            std::getline(ss, shift, ';');
            std::getline(ss, assignedWard, ';');
            ss >> canAdministerMedication;

            Nurse* nurse = new Nurse(id, firstName, lastName, phone, dateOfBirth, department, shift, assignedWard, canAdministerMedication);
            staffMembers.push_back(nurse);
        }
    }
    file.close();
}


void Hospital::saveAppointments(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file for saving appointments: " << filename << std::endl;
        return;
    }

    for(const Appointment* appointment : appointments) {
        file << appointment->getType() << ";" << appointment->getId() << ";" << appointment->getPatientId() << ";" << appointment->getDoctorId() << ";" << appointment->getDateTime() << ";" << appointment->getStatus() << std::endl;
    }
    file.close();
}

void Hospital::loadAppointments(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file for loading appointments: " << filename << std::endl;
        return;
    }

    std::string line;
    while(std::getline(file, line)) {
        if(line.empty()) continue;

        std::istringstream iss(line);
        std::string type, id, patientId, doctorId, dateTime, status;

        std::getline(iss, type, ';');
        std::getline(iss, id, ';');
        std::getline(iss, patientId, ';');
        std::getline(iss, doctorId, ';');
        std::getline(iss, dateTime, ';');
        std::getline(iss, status, ';');

        if (!status.empty() && status.back() == '\r') {
            status.pop_back();
        }

        if(!id.empty()){
            Appointment* newAppointment = nullptr;

            if(type == "Regular") {
                newAppointment = new RegularAppointment(id, patientId, doctorId, dateTime);
            } else if(type == "Emergency") {
                newAppointment = new EmergencyAppointment(id, patientId, doctorId, dateTime);
            }
            if(newAppointment) {
                if(status == "Cancelled") {
                    newAppointment->cancel();
                }
                appointments.push_back(newAppointment);

                Patient* patient = findPatientById(patientId);
                if(patient) {
                    patient->addAppointment(id);
                }

                if(status == "Scheduled") {
                    for(Staff* staff : staffMembers) {
                        if(staff->getRole() == "Doctor" && staff->getId() == doctorId) {
                            Doctor* doctor = dynamic_cast<Doctor*>(staff);
                            if(doctor) {
                                doctor->addBookedTime(dateTime);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    file.close();
}
