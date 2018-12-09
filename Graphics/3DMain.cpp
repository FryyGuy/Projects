#include <iostream>
#include <cstdlib>
#include <string.h>

#include "graphic_io.h"
#include "graphic_structures.h"
#include "graphic_math.h"

#include <stdio.h>
using namespace std;

string r1 = "r1";
string r2 = "r2";
string r3 = "r3";
string r4 = "r4";
string r5 = "r5";
string r6 = "r6";
string r7 = "r7";
string r8 = "r8";
string r9 = "r9";
string ra = "ra";
string rb = "rb";
string rc = "rc";
string rd = "rd";
string re = "re";
string rf = "rf";
string rg = "rg";
string rh = "rh";
string ri = "ri";
string rj = "rj";
string rk = "rk";

string g1 = "g1";
string g2 = "g2";
string g3 = "g3";
string g4 = "g4";
string g5 = "g5";
string g6 = "g6";
string g7 = "g7";
string g8 = "g8";
string g9 = "g9";
string ga = "ga";
string gb = "gb";
string gc = "gc";
string gd = "gd";
string ge = "ge";
string gf = "gf";
string gg = "gg";
string gh = "gh";
string gi = "gi";
string gj = "gj";
string gk = "gk";

string b1 = "b1";
string b2 = "b2";
string b3 = "b3";
string b4 = "b4";
string b5 = "b5";
string b6 = "b6";
string b7 = "b7";
string b8 = "b8";
string b9 = "b9";
string ba = "ba";
string bb = "bb";
string bc = "bc";
string bd = "bd";
string be = "be";
string bf = "bf";
string bg = "bg";
string bh = "bh";
string bi = "bi";
string bj = "bj";
string bk = "bk";

int main(int argc, char **argv)
{
	int min_x_vp = 0, min_y_vp = 0, max_x_vp = 499, max_y_vp = 499;
	double x_prp = 0.0, y_prp = 1.0, z_prp = 1.0, x_vrp = 0.0, y_vrp = 0.0, z_vrp = 0.0;
	double x_vpn = 0.0, y_vpn = 0.0, z_vpn = -1.0, x_vup = 0.0, y_vup = 1.0, z_vup = 0.0;
	double u_min_vrc = -0.7, v_min_vrc = -0.7, u_max_vrc = 0.7, v_max_vrc = 0.7;
	bool parallel_proj = false;

	// this is for z-cuing and z-buffering
	double front = 0.6, back = -0.6;

	string *poly1 = nullptr, *poly2 = nullptr, *poly3 = nullptr;

	vector< string > *reds = new vector<string>();
	vector< string > *greens = new vector<string>();
	vector< string > *blues = new vector<string>();

	reds->push_back(r1);
	reds->push_back(r2);
	reds->push_back(r3);
	reds->push_back(r4);
	reds->push_back(r5);
	reds->push_back(r6);
	reds->push_back(r7);
	reds->push_back(r8);
	reds->push_back(r9);
	reds->push_back(ra);
	reds->push_back(rb);
	reds->push_back(rc);
	reds->push_back(rd);
	reds->push_back(re);
	reds->push_back(rf);
	reds->push_back(rg);
	reds->push_back(rh);
	reds->push_back(ri);
	reds->push_back(rj);
	reds->push_back(rk);

	blues->push_back(b1);
	blues->push_back(b2);
	blues->push_back(b3);
	blues->push_back(b4);
	blues->push_back(b5);
	blues->push_back(b6);
	blues->push_back(b7);
	blues->push_back(b8);
	blues->push_back(b9);
	blues->push_back(ba);
	blues->push_back(bb);
	blues->push_back(bc);
	blues->push_back(bd);
	blues->push_back(be);
	blues->push_back(bf);
	blues->push_back(bg);
	blues->push_back(bh);
	blues->push_back(bi);
	blues->push_back(bj);
	blues->push_back(bk);

	greens->push_back(g1);
	greens->push_back(g2);
	greens->push_back(g3);
	greens->push_back(g4);
	greens->push_back(g5);
	greens->push_back(g6);
	greens->push_back(g7);
	greens->push_back(g8);
	greens->push_back(g9);
	greens->push_back(ga);
	greens->push_back(gb);
	greens->push_back(gc);
	greens->push_back(gd);
	greens->push_back(ge);
	greens->push_back(gf);
	greens->push_back(gg);
	greens->push_back(gh);
	greens->push_back(gi);
	greens->push_back(gj);
	greens->push_back(gk);

	if (argc < 3)
	{
		cout << "Error: improper call." << endl;
		cout << "Proper call format is as follows:" << endl;
		cout << "arg[1]: -f <model1>" << endl;
		cout << "arg[2]: -g <model2>" << endl;
		cout << "arg[3]: -i <model3>" << endl;
		cout << "arg[4]: -j <min_x_vp>" << endl;
		cout << "arg[5]: -k <min_y_vp>" << endl;
		cout << "arg[6]: -o <max_x_vp>" << endl;
		cout << "arg[7]: -p <max_y_vp>" << endl;
		cout << "arg[8]: -x <x_prp>" << endl;
		cout << "arg[9]: -y <y_prp>" << endl;
		cout << "arg[10]: -z <z_prp>" << endl;
		cout << "arg[11]: -X <x_vrp>" << endl;
		cout << "arg[12]: -Y <y_vrp>" << endl;
		cout << "arg[13]: -Z <z_vrp>" << endl;
		cout << "arg[14]: -q <x_vpn>" << endl;
		cout << "arg[15]: -r <y_vpn>" << endl;
		cout << "arg[16]: -w <z_vpn>" << endl;
		cout << "arg[17]: -Q <x_vup>" << endl;
		cout << "arg[18]: -R <y_vup>" << endl;
		cout << "arg[19]: -W <z_vup>" << endl;
		cout << "arg[20]: -u <u_min_vrc>" << endl;
		cout << "arg[21]: -v <v_min_vrc>" << endl;
		cout << "arg[22]: -U <u_max_vrc>" << endl;
		cout << "arg[23]: -V <v_max_vrc>" << endl;
		cout << "arg[24]: -P <parallel_projection> [optional]" << endl;
	}
	else
	{
		for (int i = 0; i < argc; i++)
		{
			if (strcmp("-f", argv[i]) == 0)
				poly1 = new string(argv[i + 1]);
			if (strcmp("-g", argv[i]) == 0)
				poly2 = new string(argv[i + 1]);
			if (strcmp("-i", argv[i]) == 0)
				poly3 = new string(argv[i + 1]);
			else if (strcmp("-j", argv[i]) == 0)
				min_x_vp = strtod(argv[i + 1], argv);
			else if (strcmp("-k", argv[i]) == 0)
				min_y_vp = strtod(argv[i + 1], argv);
			else if (strcmp("-o", argv[i]) == 0)
				max_x_vp = strtod(argv[i + 1], argv);
			else if (strcmp("-p", argv[i]) == 0)
				max_y_vp = strtod(argv[i + 1], argv);
			else if (strcmp("-x", argv[i]) == 0)
				x_prp = strtof(argv[i + 1], argv);
			else if (strcmp("-y", argv[i]) == 0)
				y_prp = strtof(argv[i + 1], argv);
			else if (strcmp("-z", argv[i]) == 0)
				z_prp = strtof(argv[i + 1], argv);
			else if (strcmp("-X", argv[i]) == 0)
				x_vrp = strtof(argv[i + 1], argv);
			else if (strcmp("-Y", argv[i]) == 0)
				y_vrp = strtof(argv[i + 1], argv);
			else if (strcmp("-Z", argv[i]) == 0)
				z_vrp = strtof(argv[i + 1], argv);
			else if (strcmp("-q", argv[i]) == 0)
				x_vpn = strtof(argv[i + 1], argv);
			else if (strcmp("-r", argv[i]) == 0)
				y_vpn = strtof(argv[i + 1], argv);
			else if (strcmp("-w", argv[i]) == 0)
				z_vpn = strtof(argv[i + 1], argv);
			else if (strcmp("-Q", argv[i]) == 0)
				x_vup = strtof(argv[i + 1], argv);
			else if (strcmp("-R", argv[i]) == 0)
				y_vup = strtof(argv[i + 1], argv);
			else if (strcmp("-W", argv[i]) == 0)
				z_vup = strtof(argv[i + 1], argv);
			else if (strcmp("-u", argv[i]) == 0)
				u_min_vrc = strtof(argv[i + 1], argv);
			else if (strcmp("-v", argv[i]) == 0)
				v_min_vrc = strtof(argv[i + 1], argv);
			else if (strcmp("-U", argv[i]) == 0)
				u_max_vrc = strtof(argv[i + 1], argv);
			else if (strcmp("-V", argv[i]) == 0)
				v_max_vrc = strtof(argv[i + 1], argv);
			else if (strcmp("-P", argv[i]) == 0)
				parallel_proj = true;
			else if (strcmp("-F", argv[i]) == 0)
				front = strtof(argv[i + 1], argv);
			else if (strcmp("-B", argv[i]) == 0)
				back = strtof(argv[i + 1], argv);
		}
	}
	char r = 'r', g = 'g', b = 'b';
	std::cout << poly1->c_str() << endl;
	std::cout << poly2->c_str() << endl;
	std::cout << poly3->c_str() << endl;

	string smf_data1(poly1->c_str());
	string smf_data2(poly2->c_str());
	string smf_data3(poly3->c_str());

	SmfIO ps(smf_data1, smf_data2, smf_data3);
	/*SmfIO ps(smf_data3);*/

	Shape *shapes = ps.read();
	WorldWindow *ww = new WorldWindow(min_x_vp, min_y_vp, max_x_vp, max_y_vp, x_prp, y_prp, z_prp, x_vrp, y_vrp, z_vrp,
		x_vpn, y_vpn, z_vpn, x_vup, y_vup, z_vup, u_min_vrc, v_min_vrc, u_max_vrc, v_max_vrc, parallel_proj, front, back, shapes, reds, greens, blues);

	ww->colors[0] = r;
	ww->colors[1] = g;
	ww->colors[2] = b;
	
	XpmIO xpm_writer("3DTest.xpm");
	xpm_writer.write(ww);
	
	return 0;
}