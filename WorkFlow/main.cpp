#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "../includes/userInterface.h"
#include "../includes/backendInterface.h"

using namespace std;

int main()
{
	string absolutePath = "C:\\Users\\stefano\\Documents\\nigoro\\np\\3SAT-Verifier\\3SAT-Verifier\\resources\\";
	/*string istance = absolutePath + "instances\\instance_01.txt";
	string certificateFile = absolutePath + "certificates\\certificate_01.txt";*/
	
	string PA_InstanceFileName;
	string PA_CertificateFileName;

	string PB_InstanceFileName;
	string PB_CertificateFileName;

	ostringstream PA_Instance;
	ostringstream PA_Certificate;
	std::unordered_map<std::string, std::string> PA_options({ { "type", "hanoi" }, { "num_nodes", "11" } });


	PA_Generate(PA_Instance, PA_Certificate, PA_options);
	
	istringstream PA_InstanceIN(PA_Instance.str());
	istringstream PA_CertificateIN(PA_Certificate.str());
	
	bool result = PA_Verifier(PA_InstanceIN, PA_CertificateIN);
	
	/*ifstream instance(istance);
	ifstream certificate(certificateFile);
	*/


	//bool result = PB_Verifier(instance, certificate);
}