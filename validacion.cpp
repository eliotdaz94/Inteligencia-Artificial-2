#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <math.h> 
using namespace std;


/*
	Evalua las instancias en X en la hipotesis presentada en thetas.
	n_examples = numero de instancias a evaluar
	n_features = numero de atributos de las instancias
	x = matriz con las instancias
	thetas = pesos de la hipotesis de regresion lineal
	eval = resultado de cada evaluacion
*/

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

/*
	Separa un string en base a un delimitador y devuelve un vector con cada palabra por separado.
	str = string a separar
	delimiter = delimitador
*/
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
	//cout << "LALALA";
	ifstream file;
	string line;
	vector<string> line_splitted;
	int n_features;
	int n_examples;
	if (argc != 2) {
		cout << "Usage: ./RegresionLineal dataFile learningRate epsilon outputFile" << endl;
		cout << endl;
		cout << "	dataFile: Archivo con el conjunto de datos de entrada." << endl;
		cout << "	learningRate: Flotante que indica la tasa de aprendizaje." << endl;
		cout << "	epsilon: Flotante que indica la cota superior del error permitido." << endl;
		// Cambiar esto abajo.
		cout << "	outputFile: Archivo con los resultados." << endl;
		return 0;
	}
	//cout << "Abriendo archivo";
	file.open(argv[1]);
	//cout << "Archivo abierto";
	getline(file, line);
	line_splitted = split(line, " ");
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
			if (std_deviation[j] != 0) { 
				x[i][j] = (x[i][j] - mean[j]) / std_deviation[j];
			}
		}
		if (std_deviation[0] != 0) { 
			y[i] = (y[i] - mean[0]) / std_deviation[0];
		}
		
	}
	double eval[n_examples];
	double thetas[20] = {4.23038e-10, -0.0717859, 0.0673145, 0.0125209, 
						 0.205262, 0.0580651, 0.10119, 0.189454, 0.230135, 
						 0.110117, -0.0195277, 0.248916, 0.216456, 0.113272, 
						 0.0895055, -0.0979455, 0.00305139, 0.000494569, 
						 0.0196825, -0.0209725};
	evaluar_hip(n_examples, n_features, x, thetas, eval);
	double error;
	double bias = 0;
	double max_deviation = 0;
	double mean_abs_deviation = 0;
	double mean_sqr_error = 0;
	for (int k = 0; k < n_examples; k++) {
		error = eval[k] - y[k];
		bias += error;
		max_deviation = abs(error) > max_deviation? error : max_deviation;
		mean_abs_deviation += abs(error);
		mean_sqr_error += pow(error, 2);  
	}
	bias /= n_examples;
	mean_abs_deviation /= n_examples;
	mean_sqr_error /= n_examples;
	cout << "Bias: " << bias << endl;
	cout << "Maxima Desviacion: " << max_deviation << endl;
	cout << "Desviacion Media Absoluta: " << mean_abs_deviation << endl;
	cout << "Error Cuadrado Medio: " << mean_sqr_error << endl;
}