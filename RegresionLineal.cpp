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
	Efectua descenso de gradiente sobre una matriz de intancias X con output Y
	n_examples = numero de instancias a evaluar
	n_features = numero de atributos de las instancias
	x = matriz con las instancias
	y = vector de resultados asociados a las instancias en X
	learning_rate = tasa de aprendizaje del descenso de gradiente
	epsilon = epsilon para detener el descenso de gradiente en base al cambio de norma
	out_file = handler al archivo de salida de la iteracion y j(0)
*/
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
	for (int k = 0; k < n_features; k++) {
		new_thetas[k] = 0.1;
	}
	while (norma2 >= epsilon) {
		evaluar_hip(n_examples, n_features, x, new_thetas, eval);
		for (int i = 0; i < n_features; i++) {
			old_thetas[i] = new_thetas[i];
		}
		for (int j = 0; j < n_examples; j++) {
			error[j] = eval[j] - y[j];
		}
		for (int l = 0; l < n_features; l++) {
			sumatoria = 0;
			for (int m = 0; m < n_examples; m++) {
				sumatoria += error[m] * x[m][l]; 
			}
			new_thetas[l] -= (learning_rate/n_examples) * sumatoria; 
		}
		if (iter % 100 == 0) {
			f_costo = 0;
			for (int n = 0; n < n_features; n++) {
				f_costo += pow(error[n], 2);
			}	
			f_costo /= (2 * n_examples);
			o_file << iter << " " << f_costo << endl;	
		}
		norma2 = 0;
		for (int b = 0; b < n_features; b++) {
			old_thetas[b] = new_thetas[b] - old_thetas[b];
			norma2 += pow(old_thetas[b],2);
		}
		norma2 = sqrt(norma2);
		iter++;
	}
	o_file.close();
	cout << "[";
	for (int i = 0; i < n_features; i++) {
			cout << new_thetas[i];
			cout << ", ";
	}
	cout << "]" << endl;
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

/*
	Manejo de la entrada y normalizacion de los datos.
*/
int main(int argc, const char **argv){
	ifstream file;
	string line;
	vector<string> line_splitted;
	int n_features;
	int n_examples;
	double learning_rate;
	double epsilon;
	if (argc != 5) {
		cout << "Uso: ./" << argv[0] << " dataFile learningRate epsilon outputFile" << endl;
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
}