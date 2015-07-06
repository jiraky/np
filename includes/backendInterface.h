#ifndef BACKENDINTERFACE_H
#include <sstream>
#include <unordered_map>
int PA_Generate(std::ostream &instance, std::ostream &certificate, std::unordered_map<std::string, std::string> options);
bool PA_Verifier_Server(std::istream &instance, std::istream &certificate);
bool PB_Verifier_Server(std::istream &instance, std::istream &certificate);
#endif