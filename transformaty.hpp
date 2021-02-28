#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>
#include <complex>

double roznicaModulow(const std::vector<std::complex<double>>& DFT, const std::vector<std::complex<double>>& FFT) {
	double suma = 0.0;
	for (size_t i = 0; i < DFT.size(); i++) {
		double modul = std::abs(DFT[i] - FFT[i]);
		suma += modul;
	}
	return 1 / DFT.size() * suma;
}

std::vector<std::complex<double>> dft(const std::vector<double>& f) {
	std::vector<std::complex<double>> wynik;
	size_t size = f.size();

	for (size_t k = 0; k < size; k++) {
		std::complex<double> suma{ 0.0, 0.0 };
		for (size_t l = 0; l < size; l++) {
			std::complex<double> zmienna = std::polar(1.0, 2 * M_PI * l * k / size);
			suma += f[l] * -zmienna;
		}
		wynik.emplace_back(suma);
	}

	return wynik;
}

std::vector<std::complex<double>> fft(const std::vector<double>& f) {
	if (f.size() == 1)
		return std::vector<std::complex<double>>{f[0]};
	
	size_t size = f.size();

	std::vector<double> parzyste;
	for (size_t i = 0; i < size; i += 2)
		parzyste.emplace_back(f[i]);
	
	std::vector<double> nieparzyste;
	for (size_t i = 1; i < size; i += 2)
		nieparzyste.emplace_back(f[i]);

	std::vector<std::complex<double>> parzysteWynik = fft(parzyste);
	std::vector<std::complex<double>> nieparzysteWynik = fft(nieparzyste);

	std::vector<std::complex<double>> wynik(size);
	for (size_t k = 0; k < size / 2 ; k++) {
		std::complex<double> zmienna = std::polar(1.0, -2 * M_PI * k / size) * nieparzysteWynik[k];
		wynik[k] = parzysteWynik[k] + zmienna;
		wynik[k + (size / 2)] = parzysteWynik[k] - zmienna;
	}
	
	return wynik;
}