#include <iostream>
#include <chrono>
#include "transformaty.hpp"

struct Timer {
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<double> duration;

	Timer() {
		start = std::chrono::high_resolution_clock::now();
	}

	~Timer() {
		this->endTook();
	}

	double endTook() {
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;

		//std::cout << "Timer took: " << duration.count() << " sek" << std::endl;
		return duration.count();
	}

	void reset() {
		start = std::chrono::high_resolution_clock::now();
	}
};

void wypis(const std::vector<std::complex<double>>& wyniki, const std::string& napis) {
	std::cout << "----------- " << napis << " -----------" << std::endl;
	for (auto& item : wyniki)
		std::cout << item << std::endl;
	std::cout << "----------- KONIEC -----------" << std::endl;
}

std::ostream& operator<<(std::ostream& out, std::complex<double>& item) {
	out << "(" << item.real();
	out << ";" << item.imag();
	out << "j)";
	return out;
}

int main()
{
	const int max = 1;
	const bool przelacznik = false;
	const bool czyWypisac = false;

	for (size_t o = 1; o <= max; o++) {
		const int N = 1 << o;
		std::cout << "N=" << N << std::endl;

		std::vector<double> f {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8};
		/*for (size_t k = 0; k < N; k++)
			f.emplace_back(k / static_cast<double>(N));*/

		Timer timer;
		std::vector<std::complex<double>> cDFT = dft(f);
		double timeOperation = timer.endTook();
		std::cout << "Czas operacji dla DFT: " << timeOperation << " sek" << std::endl;
		/*for (auto& item : cDFT)
			std::cout << item << std::endl;*/

		timer.reset();
		std::vector<std::complex<double>> cFFT = fft(f);
		timeOperation = timer.endTook();
		std::cout << "Czas operacji dla FFT: " << timeOperation << " sek" << std::endl;
		for (auto& item : cFFT)
			std::cout << item << std::endl;
		
		std::cout << "Sredni modul roznic: " << roznicaModulow(cDFT, cFFT) << std::endl;

		if (czyWypisac) {
			if (przelacznik)
				wypis(cDFT, "DFT");
			else
				wypis(cFFT, "FFT");
		}
		std::cout << std::endl;
	}
}

