#include <fstream>
#include <string>
#include <sstream>
#include "../../includes/graph.h"
#include <iostream>
#include <queue>
#include <list>
#include <unordered_map>

using namespace std;


class Hanoi_Triangle {
public:
	int h = 0;
	int s = 0;
	int d = 0;

	Hanoi_Triangle(int h, int s, int d) {
		this->d = d;
		this->h = h;
		this->s = s;
	}

	Hanoi_Triangle()
	{
		
	}
};

int N = 0;

int Hanoi(std::ostream &instance, std::ostream &certificate, int num_nodes)
{

	int hanoi_size = (int) floor(pow((float)num_nodes, 1.0f / 3.0f));

	

	int exp = hanoi_size-1;
	int call = (int)pow(3.0, exp);

	int rand_nodes = num_nodes - (int)pow(3.0, hanoi_size);
	
	if (call < 3)
		return -1;

	int edges = (int) ((int)3 * ((pow(3.0, hanoi_size)- 1))/ 2)+ rand_nodes;
	instance << num_nodes << ' ' << edges << '\n';
	
	int tmp1 = N;
	int tmp2 = N + 1;
	int tmp3 = N + 2;

	vector<Hanoi_Triangle> v;
	while (call != 0) {
		string str = "";
		int h = 0, s = 0, d = 0;
		vector<int> arr;
		arr.resize(6);

		N += 3;
		str += to_string(tmp1) + " " + to_string(tmp2) + '\n';
		str += to_string(tmp2) + " " + to_string(tmp3) + '\n';
		str += to_string(tmp3) + " " + to_string(tmp1) + '\n';

		arr[0] = tmp2;
		h = tmp1;
		arr[1] = tmp3;
		tmp1 = N;
		tmp2 = N + 1;
		tmp3 = N + 2;

		str += to_string(tmp1) + " " + to_string(tmp2) + '\n';
		str += to_string(tmp2) + " " + to_string(tmp3) + '\n';
		str += to_string(tmp3) + " " + to_string(tmp1) + '\n';

		N += 3;
		arr[2] = tmp1;
		arr[3] = tmp3;
		s = tmp2;
		tmp1 = N;
		tmp2 = N + 1;
		tmp3 = N + 2;

		str += to_string(tmp1) + " " + to_string(tmp2) + '\n';
		str += to_string(tmp2) + " " + to_string(tmp3) + '\n';
		str += to_string(tmp3) + " " + to_string(tmp1) + '\n';

		N += 3;
		arr[4] = tmp1;
		arr[5] = tmp2;
		d = tmp3;
		str += to_string(arr[0]) + " " + to_string(arr[2]) + '\n';
		str += to_string(arr[1]) + " " + to_string(arr[4]) + '\n';
		str += to_string(arr[3]) + " " + to_string(arr[5]) + '\n';

		tmp1 = N;
		tmp2 = N + 1;
		tmp3 = N + 2;
		call -= 3;
		v.push_back(Hanoi_Triangle(h, s, d));

		instance << str;
	}
	int n_trian = v.size();
	while (v.size() != 1) {
		Hanoi_Triangle x = v[0];
		Hanoi_Triangle y = v[1];
		Hanoi_Triangle z = v[2];
		instance << x.s << " " << y.h << '\n' << x.d << " " << z.h << '\n' << y.d << " " << z.s << "\n";
		v.erase(v.begin());
		v.erase(v.begin());
		v.erase(v.begin());
		v.push_back(Hanoi_Triangle(x.h, y.s, z.d));
	}

	int certSize = n_trian * 6;

	certificate << certSize;

	for (int i = 0; i < N; ++i)
	{
		if (i % 3 != 0)
			certificate << " " << i;
	}

	int max = N;

	while(N < num_nodes)
	{
		int last = N++;
		int choose;
		while ((choose = rand() % max) % 3 == 0) {};

		instance << last << ' ' << choose << '\n';
	}

	return 0;
}

int PA_Generate(std::ostream &instance, std::ostream &certificate, std::unordered_map<std::string, std::string> options)
{
	if (options["type"] == "hanoi")
	{
		return Hanoi(instance, certificate, atoi(options["num_nodes"].c_str()));
	}
}


#ifndef INCLUDED_SRC
int main()
{
	string absolutePath = "D:\\Development\\NP\\VC-Generator\\VC-Generator\\resources\\";
	string instanceFile = absolutePath + "instances\\instance_01.txt";
	string certificateFile = absolutePath + "certificates\\certificate_01.txt";
	ofstream instance(instanceFile);
	ofstream certificate(certificateFile);
	std::unordered_map<std::string, std::string> options({ { "type", "hanoi" }, { "num_nodes", "11" } });
	PA_Generate(instance, certificate, options);
}
#endif


