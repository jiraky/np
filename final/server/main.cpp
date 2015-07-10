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

	int max_verifierA = 1;
	int max_verifierB = 1;
	int max_reductionHard = 5;
} points;

static int k = 1;

string PA = "3-SAT";
string PB = "K-MIN-VC";

int main()
{
	cout << "NP Completeness Prover" << endl;
	cout << "Version: 0.1 (Alpha release)" << endl;
	cout << "Problem A: " << PA << endl;
	cout << "Problem B: " << PB << endl;

	cout << "----------------------" << endl;
	cout << "Phase 1: '" << PA << "' Validation" << endl;
	cout << " - Round:      " << k << endl;
	cout << " - Max Points: " << points.max_verifierA << endl;
	cout << " - Validation: " << PA << "-User-Verifier == " << PA << "-Server-Verifier" << endl;
	cout << "Please wait... ";
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
	cout << "DONE" << endl;
	cout << "Result: " << points.verifierA << "/" << points.max_verifierA << endl;

	cout << "----------------------" << endl;
	cout << "Phase 2: " << PA << "<=" << PB << " Easy Reduction" << endl;
	cout << " - Round:      " << k << endl;
	cout << " - Max Points: " << points.max_verifierB << endl;
	cout << " - Validation: " << PB << "-User-Verifier == " << PB << "-Server-Verifier" << endl;
	cout << "Please wait... ";
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
	cout << "DONE" << endl;
	cout << "Result: " << points.verifierB << "/" << points.max_verifierB << endl;

	cout << "----------------------" << endl;
	cout << "Phase 3: " << PA << "<=" << PB << " Hard Reduction" << endl;
	cout << " - Round:      1" << endl;
	cout << " - Max Points: " << points.max_reductionHard << endl;
	cout << " - Validation: " << PA << "-User-Verifier == " << PA << "-Server-Verifier" << endl;
	cout << "          AND  " << PB << "-User-Verifier == " << PB << "-Server-Verifier" << endl;
	cout << "Please wait... ";
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
		points.reductionHard = 5;
	}
	
	cout << "DONE" << endl;
	cout << "Result: " << points.reductionHard << "/" << points.max_reductionHard << endl << endl;

	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		system("pause");
	#endif
}