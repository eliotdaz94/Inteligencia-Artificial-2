#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <math.h> 
using namespace std;

void evaluar_hip(int n_examples, int n_features, double** x, double thetas[],
				 double eval[]) {
	double result;
	for (int i = 0; i < n_examples; i++) {
		result = 0;
		for (int j = 0; j < n_features; j++) {
			result += thetas[j] * x[i][j];
		}
		eval[i] = result;
	}
}

double * gradient_descent(int n_examples, int n_features, double** x, double y[], 
						  double learning_rate, double epsilon, const char* out_file) {
	double new_thetas[n_features];
	double old_thetas[n_features];
	double eval[n_examples];
	double error[n_examples];
	double f_costo;
	double sumatoria;
	double norma2 = epsilon + 1.0;
	int iter = 1;
	ofstream o_file;
	o_file.open(out_file);
	o_file << "Iteracion" << " " << "FuncionCosto" << endl;
	//cout << n_features << endl;
	for (int k = 0; k < n_features; k++) {
		new_thetas[k] = 0.1;
	}
	while (norma2 >= epsilon) {
		//cout << "JAJA" << endl;
		evaluar_hip(n_examples, n_features, x, new_thetas, eval);
		//cout << n_features << endl;
		/*
		for (int i = 0; i < n_examples; i++) {
			cout << eval[i] << endl;
		}
		*/
		for (int i = 0; i < n_features; i++) {
			old_thetas[i] = new_thetas[i];
		}
		for (int j = 0; j < n_examples; j++) {
			error[j] = eval[j] - y[j];
		}
		for (int l = 0; l < n_features; l++) {
			sumatoria = 0;
			for (int m = 0; m < n_examples; m++) {
				//cout << eval[m] << " " << y[m] << " " << x[m][l] << endl;
				sumatoria += error[m] * x[m][l]; 
			}
			//cout << learning_rate/n_examples << " " << sumatoria << endl;
			new_thetas[l] -= (learning_rate/n_examples) * sumatoria; 
			//cout << "########################################################";
		}
		if (iter % 1 == 0) {
			f_costo = 0;
			for (int n = 0; n < n_features; n++) {
				f_costo += pow(error[n], 2);
			}	
			f_costo /= (2 * n_examples);
			o_file << iter << " " << f_costo << endl;	
		}
		// Calculo de la norma 2 de la resta de los vectores que contienen los 
		// parametros thetas.
		norma2 = 0;
		//cout << "+JAJA" << endl;
		//cout << n_features << endl;
		for (int b = 0; b < n_features; b++) {
			//cout << "+JAJA" << endl;
			old_thetas[b] = new_thetas[b] - old_thetas[b];
			//cout << old_thetas[b] << endl;
			norma2 += pow(old_thetas[b],2);
			//cout << norma2 << endl;
		}
		//cout << endl;
		//cout << norma2;
		norma2 = sqrt(norma2);
		iter++;
	}
	o_file.close();
	for (int i = 0; i < n_features; i++) {
			cout << new_thetas[i];
			cout << " ";
	}
	cout << endl;
}

vector<string> split(string str, string delimiter) {
	vector<string> str_splitted;
	size_t pos = 0;
	size_t n_delim = delimiter.length();
	string token;

	while ((pos = str.find(delimiter)) != -1) {
    	token = str.substr(0, pos);
    	str_splitted.push_back(token);
    	str.erase(0, pos + n_delim);
	}
    str_splitted.push_back(str);
	return str_splitted;
}

int main(int argc, const char **argv){
	ifstream file;
	string line;
	vector<string> line_splitted;
	int n_features;
	int n_examples;
	double learning_rate;
	double epsilon;
	if (argc != 5) {
		cout << "Usage: ./RegresionLineal dataFile learningRate epsilon outputFile" << endl;
		cout << endl;
		cout << "	dataFile: Archivo con el conjunto de datos de entrada." << endl;
		cout << "	learningRate: Flotante que indica la tasa de aprendizaje." << endl;
		cout << "	epsilon: Flotante que indica la cota superior del error permitido." << endl;
		// Cambiar esto abajo.
		cout << "	outputFile: Archivo con los resultados." << endl;
		return 0;
	}
	file.open(argv[1]);
	getline(file, line);
	line_splitted = split(line, " ");
	for (int i = 0; i < line_splitted.size(); i++) {
		cout << line_splitted[i] << endl;
	}
	n_features = atoi(line_splitted[0].c_str()) - 1;
	n_examples = atoi(line_splitted[1].c_str());
	double** x;
	double y[n_examples];
	double mean[n_features];
	double std_deviation[n_features];
	x = new double *[n_examples];
	for (int j = 0; j < n_features; j++) { 
		std_deviation[j] = (mean[j] = 0);
	}
	for (int i = 0; i < n_examples; i++) {
		x[i] = new double [n_features];
		getline(file, line);
		line_splitted = split(line, " ");
		x[i][0] = 1;
		for (int j = 1; j < n_features; j++) { 
			mean[j] += (x[i][j] = atof(line_splitted[j].c_str()));
		}
		mean[0] += (y[i] = atof(line_splitted[n_features].c_str())); 
	}
	file.close();
	// Calculo de la media para cada feature.
	for (int j = 0; j < n_features; j++) { 
		mean[j] /= n_examples;
	}
	// Calculo de la desviacion estandar para cada feature.
	for (int i = 0; i < n_examples; i++) {
		for (int j = 1; j < n_features; j++) { 
			std_deviation[j] += pow((x[i][j] - mean[j]),2);
		}
		std_deviation[0] += pow(y[i] - mean[0],2);
	}
	for (int j = 0; j < n_features; j++) { 
		std_deviation[j] = sqrt((std_deviation[j] / (n_examples - 1)));
	}
	// Normalizacion de los datos.
	for (int i = 0; i < n_examples; i++) {
		for (int j = 1; j < n_features; j++) { 
			x[i][j] = (x[i][j] - mean[j]) / std_deviation[j];
		}
		y[i] = (y[i] - mean[0]) / std_deviation[0];
	}
	learning_rate = strtod(argv[2], NULL);
	epsilon = strtod(argv[3], NULL);
	gradient_descent(n_examples, n_features, x, y, learning_rate, epsilon, argv[4]); 
	
	for (int j = 0; j < n_features; j++) { 
		cout << mean[j] << " " << std_deviation[j] << endl;
	}
	/*
	for (int i = 0; i < n_examples; i++) {
		for (int j = 1; j < n_features; j++) {
			cout << x[i][j];
			cout << " " ;
		}
		cout << y[i] << endl;
	}
	*/
}