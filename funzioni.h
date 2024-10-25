#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T> T calc_media(vector<T> v);
template <typename T> T calc_media_optm(vector<T> v); //calcolo media ottimizzato

template <typename T> T calc_varianza(vector<T> v);
template <typename T> T calc_varianza_optm(vector<T> v); //calcolo media ottimizzato

template <typename T> T calc_mediana(vector<T> v);

template <typename T> vector<T> carica_da_file(const char* filename);

template <typename T> void Print(const char* filename, vector<T> v);
template <typename T> void Print(vector<T> v);

//-----------------------------//

double calc_s_q(double q, vector<double> v);
double calc_deriv(double q, vector<double> v);

//-----------------------------//

//=============================//
//       IMPLEMENTATION	       //
//=============================//

template <typename T> vector<T> carica_da_file(const char* filename){
	vector<T> v;
	ifstream input_file(filename);

	if (input_file.fail()) {
		cout<<"Error to load file \""<<filename<<"\"\n";
		exit(1);
	} else {
		while (!input_file.eof()) {
			T temp;
			input_file>>temp;
			v.push_back(temp);
		}
	}

	input_file.close();
	return v;
}

template <typename T> T calc_media(vector<T> v){
	T media=0;
	if (v.size()==0) return media;
	for (int i=0; i<v.size(); ++i) {
		media += v[i];
	}
	media = media/(T)(v.size());
	return media;
}

template <typename T> T calc_media_optm(vector<T> v){
	T media=0;
	if (v.size()==0) return media;
	for (int i=0; i<v.size(); ++i) {
		media = (T)i/(T)(i+1) * media + (T)1/(T)(i+1)*v[i];
	}
	return media;
}


template <typename T> T calc_varianza(vector<T> v){
	T varianza=0;
	if (v.size()==0) return varianza;
	T media=calc_media(v);
	for (int i=0; i<v.size(); ++i) {
		varianza+=pow((media-v[i]),2);
	}
	varianza=varianza/(T)(v.size()-1);
	return varianza;
}

template <typename T> T calc_varianza_optm(vector<T> v){
	T varianza=0;
	if (v.size()==0) return varianza;
	T media=calc_media(v);
	for (int i=0; i<v.size(); ++i) {
		varianza=(T)i/(T)(i+1) * varianza + (T)1/T(i+1) * pow(media-v[i],2);
	}
	varianza = varianza * (T)v.size()/(T)(v.size()-1);
	return varianza;
}

template <typename T> T calc_mediana(vector<T> v){
	T mediana = 0;
	if (v.size()==0) return mediana;
	if (v.size()%2==0) {
		mediana=(v[v.size()/2-1]+v[v.size()/2])/2;
	} else {
		mediana=v[v.size()/2];
	}
	return mediana;
}

template <typename T> void Print(const char* filename, vector<T> v){
	ofstream output_file(filename);
	for (int i=0; i<v.size(); ++i) output_file<<v[i]<<endl;
	output_file.close();
	return;
}

template <typename T> void Print(vector<T> v){
	for (int i=0; i<v.size(); ++i) cout<<v[i]<<endl;
	return;
}

//-----------------------------//

double calc_s_q(double q, vector<double> v){
	double sum=0;
	for (double charge : v) {
		int k = (int)(charge/q+0.5);
		sum += pow((charge/k-q),2);
	}
	return sum;
}

double calc_deriv(double q, vector<double> v){
	double sum=0;
	for (double charge : v) {
		int k = (int)(charge/q+0.5);
		sum += charge/k;
	}
	return sum/v.size();
}

//-----------------------------//
