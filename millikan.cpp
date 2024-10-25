#include <cfloat>
#include <iostream>
#include <vector>
#include <cmath>

#include "funzioni.h"
#include "TH1F.h"
#include "TApplication.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TLine.h"

using namespace std;

#define MIN 1.400e-19
#define MAX 1.800e-19
#define INCR 0.001e-19/4

#define ELECTRON_CHARGE 1.602e-19

int main(int argc, char** argv){
	if (argc<2) {
		cout<<"utilizzo del programma: "<<argv[0]<<" <filename>\n";
		exit(-1);
	}
	const char* prog_name=argv[0];
	char* filename = argv[1];

	vector<double> v=carica_da_file<double>(filename);

	cout<<cout.precision(4);
	
	TApplication app(0,0,0);
	TCanvas can1 ;
	can1.cd();
	TH1F histo("cariche","Charges distribution", 100, 0 , 20E-19);
	for (double charge : v) histo.Fill(charge);
	histo.Draw();
	histo.GetXaxis()->SetTitle("Charge [C]");

	TGraph g;
	double qmin;
	double sqmin=DBL_MAX;
	int counter=0;

	//Print(v);
	vector<double> S_q_v;
	for (double i=MIN; i<=MAX; i+=INCR) {
		double S= calc_s_q(i, v);
		g.SetPoint(counter, i, S);
		if (S<sqmin) { sqmin=S; qmin=i; }
		++counter;
	}
	cout<<"Valore approssimato del minimo: "<<qmin<<endl;

	TCanvas can2;
	can2.cd();

	g.Draw("ALP");
	g.SetMarkerStyle(20);
	g.SetMarkerSize(0.5);
	g.SetTitle("Best charge value");
	g.GetXaxis()->SetTitle("Charge (C)") ;
	g.GetYaxis()->SetTitle("S(q) (C^{2})") ;

	TLine l = TLine(ELECTRON_CHARGE, sqmin, ELECTRON_CHARGE, 15e-39);
	l.SetLineColor(kRed);
	l.Draw();

	double mycharge = calc_deriv(qmin, v);
	double uncert = sqrt( calc_s_q(mycharge, v) / (v.size()*(v.size()-1)));
	cout<<"Carica misurata = "<<mycharge<<" ± " <<uncert<<" C"<<endl;
	cout<<"Differenza percentuale = "<<(mycharge-ELECTRON_CHARGE)/mycharge*100<<"%"<<endl;
	double percent_2 = mycharge*2/100;
	cout<<"2% di carica = "<<percent_2<<" C"<<endl;
	double sigma = sqrt(pow(uncert,2)+pow(percent_2,2));
	cout<<"Sigma tot = ±"<<sigma<<" C"<<endl;
	cout<<"Intervallo = ("<<mycharge-sigma<<";"<<mycharge+sigma<<") C"<<endl;
	//Print(S_q);
	
	app.Run();

	return 0;
}
