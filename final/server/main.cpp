#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "includes/userInterface.h"
#include "includes/backendInterface.h"

using namespace std;

static struct pointType
{
	int verifierA = 0;
	int verifierB = 0;
	int reductionHard = 0;
} points;

int k = 1;

int main()
{
		
	string PA_InstanceFileName;
	string PA_CertificateFileName;

	string PB_InstanceFileName;
	string PB_CertificateFileName;


	for (int i = 0; i < k; ++i)
	{
		ostringstream PA_Instance;
		ostringstream PA_Certificate;
		std::unordered_map<std::string, std::string> PA_options({ { "type", "hanoi" }, { "num_nodes", "11" } });

		PA_Generate(PA_Instance, PA_Certificate, PA_options);



		istringstream PA_InstanceIN(PA_Instance.str());
		istringstream PA_CertificateIN(PA_Certificate.str());

		istringstream PA_InstanceIN_ForServer(PA_Instance.str());
		istringstream PA_CertificateIN_ForServer(PA_Certificate.str());

		if (PA_Verifier(PA_InstanceIN, PA_CertificateIN) == PA_Verifier_Server(PA_InstanceIN_ForServer, PA_CertificateIN_ForServer))
		{
			points.verifierA = 1;
		}
		else
		{
			points.verifierA = 0;
			break;
		}
	}

	for (int i = 0; i < k; ++i)
	{
		ostringstream PA_Instance;
		ostringstream PA_Certificate;
		std::unordered_map<std::string, std::string> PA_options({ { "type", "hanoi" }, { "num_nodes", "11" } });

		PA_Generate(PA_Instance, PA_Certificate, PA_options);

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
		else
		{
			points.verifierB = 0;
			break;
		}
	}

	ostringstream PA_Instance;
	ostringstream PA_Certificate;
	std::unordered_map<std::string, std::string> PA_options({ { "type", "hanoi" }, { "num_nodes", "11" } });

	PA_Generate(PA_Instance, PA_Certificate, PA_options);

	istringstream PA_InstanceIN_ForEasyReduction(PA_Instance.str());
	istringstream PA_CertificateIN_ForEasyReduction(PA_Certificate.str());

	ostringstream PB_Instance;
	ostringstream PB_Certificate;

	ReductionEasy_FromPA_ToPB(PA_InstanceIN_ForEasyReduction, PA_CertificateIN_ForEasyReduction, PB_Instance, PB_Certificate);

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
}