#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "../includes/userInterface.h"
#include "../includes/backendInterface.h"

using namespace std;

struct pointType
{
	int verifierA = 0;
	int verifierB = 0;
	int reductionHard = 0;
} points;



void ReductionHard_FromPA_ToPB(std::istream &PA_Instance, std::istream &PB_Certificate, std::ostream &PA_Output_Certificate)
{

}

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

	bool result1 = false;
	

	istringstream PA_InstanceIN(PA_Instance.str());
	istringstream PA_CertificateIN(PA_Certificate.str());
	
	istringstream PA_InstanceIN_ForServer(PA_Instance.str());
	istringstream PA_CertificateIN_ForServer(PA_Certificate.str());

	if (PA_Verifier(PA_InstanceIN, PA_CertificateIN) == PA_Verifier_Server(PA_InstanceIN_ForServer, PA_CertificateIN_ForServer))
	{
		points.verifierA = 1;
	}

	istringstream PA_InstanceIN_ForEasyReduction(PA_Instance.str());
	istringstream PA_CertificateIN_ForEasyReduction(PA_Certificate.str());

	ostringstream PB_Instance;
	ostringstream PB_Certificate;

	ReductionEasy_FromPA_ToPB(PA_InstanceIN_ForEasyReduction, PA_CertificateIN_ForEasyReduction, PB_Instance, PB_Certificate);

	istringstream PB_InstanceIN(PB_Instance.str());
	istringstream PB_CertificateIN(PB_Certificate.str());

	istringstream PB_InstanceIN_ForServer(PB_Instance.str());
	istringstream PB_CertificateIN_ForServer(PB_Certificate.str());

	if (PB_Verifier(PB_InstanceIN, PB_CertificateIN) == PB_Verifier_Server(PB_InstanceIN_ForServer, PB_CertificateIN_ForServer))
	{
		points.verifierB = 1;
	}


	istringstream PA_InstanceIN_ForHardReduction(PA_Instance.str());
	istringstream PB_CertificateIN_ForHardReduction(PB_Certificate.str());

	ostringstream PA_Certificate_FromHardReduction;
	
	ReductionHard_FromPA_ToPB(PA_InstanceIN_ForHardReduction, PB_CertificateIN_ForHardReduction, PA_Certificate_FromHardReduction);

	istringstream PA_InstanceIN_PostHardReduction(PA_Instance.str());
	istringstream PA_CertificateIN_PostHardReduction(PA_Certificate_FromHardReduction.str());

	istringstream PA_InstanceIN_PostHardReduction_ForServer(PA_Instance.str());
	istringstream PA_CertificateIN_PostHardReduction_ForServer(PA_Certificate_FromHardReduction.str());

	if (PA_Verifier(PA_InstanceIN_PostHardReduction, PA_CertificateIN_PostHardReduction) == PA_Verifier_Server(PA_InstanceIN_PostHardReduction_ForServer, PA_CertificateIN_PostHardReduction_ForServer))
	{
		points.reductionHard = 1;
	}

	/*ifstream instance(istance);
	ifstream certificate(certificateFile);
	*/


	//bool result = PB_Verifier(instance, certificate);
}