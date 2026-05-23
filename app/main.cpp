#include <iostream>
#include "Hospital.h"
#include <string>

void displayMenu() {
    std::cout << "=== Hospital Management System ===" << std::endl;
    std::cout << "1. Register Patient" << std::endl;
    std::cout << "2. Display All Patients" << std::endl;
    std::cout << "3. Add Doctor" << std::endl;
    std::cout << "4. Add Nurse" << std::endl;
    std::cout << "5. Display Staff by Role" << std::endl;
    std::cout << "6. Display Doctors by Speciality" << std::endl;
    std::cout << "7. Edit Patient Information" << std::endl;
    std::cout << "8. Book Regular Appointment" << std::endl;
    std::cout << "9. Cancel Appointment" << std::endl;
    std::cout << "10. Display Appointments" << std::endl;
    std::cout << "11. Conduct Exam & Issue Prescription" << std::endl;
    std::cout << "12. Display Patient History" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Please select an option: ";
}

int main(){
    Hospital hospital;
    int choice;

    do {
        displayMenu();
        std::cin >> choice;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input! Please enter a number." << std::endl;
            continue;
        }
        std::cin.ignore(10000, '\n');

        switch(choice) {
            case 1: {
                std::string id, firstName, lastName, phone, dateOfBirth;
                std::cout << "Enter Patient ID: ";
                std::getline(std::cin, id);
                std::cout << "Enter First Name: ";
                std::getline(std::cin, firstName);
                std::cout << "Enter Last Name: ";
                std::getline(std::cin, lastName);
                std::cout << "Enter Phone Number(10 digits): ";
                std::getline(std::cin, phone);
                std::cout << "Enter Date of Birth (YYYY-MM-DD): ";
                std::getline(std::cin, dateOfBirth);

                hospital.registerPatient(id, firstName, lastName, phone, dateOfBirth);
                break;
            }
            case 2: {
                hospital.displayAllPatients();
                break;
            }
            case 3: {
                std::string id, firstName, lastName, phone, dateOfBirth, department, shift, speciality;
                int cabinetNumber;
                
                std::cout << "Enter Doctor ID: ";
                std::getline(std::cin, id);
                std::cout << "Enter First Name: ";
                std::getline(std::cin, firstName);
                std::cout << "Enter Last Name: ";
                std::getline(std::cin, lastName);
                std::cout << "Enter Phone Number(10 digits): ";
                std::getline(std::cin, phone);
                std::cout << "Enter Date of Birth (YYYY-MM-DD): ";
                std::getline(std::cin, dateOfBirth);
                std::cout << "Enter Department: ";
                std::getline(std::cin, department);
                std::cout << "Enter Shift: ";
                std::getline(std::cin, shift);
                std::cout << "Enter Speciality: ";
                std::getline(std::cin, speciality);
                std::cout << "Enter Cabinet Number: ";
                std::cin >> cabinetNumber;
                std::cin.ignore(10000, '\n');
                hospital.addDoctor(id, firstName, lastName, phone, dateOfBirth, department, shift, speciality, cabinetNumber);
                break;
            }
            case 4: {
                std::string id, firstName, lastName, phone, dateOfBirth, department, shift, assignedWard;
                bool canAdministerMedication;
                std::cout << "Enter Nurse ID: ";
                std::getline(std::cin, id);
                std::cout << "Enter First Name: ";
                std::getline(std::cin, firstName);
                std::cout << "Enter Last Name: ";
                std::getline(std::cin, lastName);
                std::cout << "Enter Phone Number(10 digits): ";
                std::getline(std::cin, phone);
                std::cout << "Enter Date of Birth (YYYY-MM-DD): ";
                std::getline(std::cin, dateOfBirth);
                std::cout << "Enter Department: ";
                std::getline(std::cin, department);
                std::cout << "Enter Shift: ";
                std::getline(std::cin, shift);
                std::cout << "Enter Assigned Ward: ";
                std::getline(std::cin, assignedWard);
                std::cout << "Can Administer Medication? (1 for Yes, 0 for No): ";
                std::cin >> canAdministerMedication;
                std::cin.ignore(10000, '\n');
                hospital.addNurse(id, firstName, lastName, phone, dateOfBirth, department, shift, assignedWard, canAdministerMedication);
                break;
            }
            case 5: {
                std::string role;
                std::cout << "Enter Role to Display (Doctor/Nurse): ";
                std::getline(std::cin, role);
                hospital.displayStaffByRole(role);
                break;
            }
            case 6: {
                std::string speciality;
                std::cout << "Enter Speciality to Display Doctors: ";
                std::getline(std::cin, speciality);
                hospital.displayDoctorsBySpeciality(speciality);
                break;
            }
            case 7: {
                std::string patientId, newPhone;
                std::cout << "Enter Patient ID to Edit: ";
                std::getline(std::cin, patientId);
                Patient* patient = hospital.findPatientById(patientId);
                if (patient) {
                    std::cout << "Enter new phone number (10 digits): ";
                    std::getline(std::cin, newPhone);
                    try {
                        patient->setPhone(newPhone);
                        std::cout << "Patient information updated successfully!" << std::endl;
                    } catch (const std::exception& e) {
                        std::cout << "Error updating patient information: " << e.what() << std::endl;
                    }
                } else {
                    std::cout << "Patient with ID " << patientId << " not found!" << std::endl;
                }
                break;
            }
            case 8: {
                std::string appointmentId, patientId, doctorId, dateTime;
                std::cout << "Enter Appointment ID: ";
                std::getline(std::cin, appointmentId);
                std::cout << "Enter Patient ID: ";
                std::getline(std::cin, patientId);
                std::cout << "Enter Doctor ID: ";
                std::getline(std::cin, doctorId);
                std::cout << "Enter Date & Time (YYYY-MM-DD HH:MM): ";
                std::getline(std::cin, dateTime);
                hospital.bookRegularAppointment(appointmentId, patientId, doctorId, dateTime);
                break;
            }
            case 9: {
                std::string appointmentId;
                std::cout << "Enter Appointment ID to Cancel: ";
                std::getline(std::cin, appointmentId);
                hospital.cancelAppointment(appointmentId);
                break;
            }
            case 10: {
                hospital.displayAppointments();
                break;
            }
            case 11: {
                std::string examId, appointmentId, diagnosis, notes;
                bool issuePrescription;

                std::cout << "Enter Exam ID: ";
                std::getline(std::cin, examId);
                std::cout << "Enter Appointment ID: ";
                std::getline(std::cin, appointmentId);
                std::cout << "Enter Diagnosis: ";
                std::getline(std::cin, diagnosis);
                std::cout << "Enter Notes: ";
                std::getline(std::cin, notes);
                std::cout << "Issue Prescription? (1 for Yes, 0 for No): ";
                std::cin >> issuePrescription;
                std::cin.ignore(10000, '\n');

                hospital.conductExam(examId, appointmentId, diagnosis, notes, issuePrescription);
                break;
            }
            case 12: {
                std::string patientId;
                std::cout << "Enter Patient ID to Display History: ";
                std::getline(std::cin, patientId);
                hospital.displayPatientHistory(patientId);
                break;
            }
            case 0: {
                std::cout << "Exiting ..." << std::endl;
                break;
            }
            default: {
                std::cout << "Invalid option! Please try again." << std::endl;
            }
        }
    } while (choice != 0);

    return 0;
}