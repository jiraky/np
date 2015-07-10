#ifndef USERINTERFACE_H
#include <sstream>
bool PA_Verifier(std::istream &instance, std::istream &certificate);
bool PB_Verifier(std::istream &instance, std::istream &certificate);

void ReductionEasy_FromPA_ToPB(std::istream &PA_Instance, std::istream &PA_Certificate, std::ostream &PB_Output_Instance, std::ostream &PB_Output_Certificate);
void ReductionHard_FromPA_ToPB(std::istream &PA_Instance, std::istream &PB_Certificate, std::ostream &PA_Output_Certificate);
#endif