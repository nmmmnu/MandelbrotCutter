#include <cstdio>
#include <cstdint>
#include <cstdlib>

constexpr size_t ITERATIONS	= 128;
constexpr size_t SIZE		= 2048;
//constexpr size_t SIZE		= 50;

constexpr size_t SIZE_X		= SIZE;
constexpr size_t SIZE_Y		= SIZE;

constexpr double ESCAPE		= 2.0; // modul of mandelbrot escape
constexpr double ESCAPE2	= 2 * ESCAPE;

namespace{

	constexpr size_t Z(double x, double y, size_t iterations){
		double zx = 0;
		double zy = 0;

		size_t i = 0;
		for(; i < iterations; ++i){
			double zx_sq = zx * zx;
			double zy_sq = zy * zy;

			if (zx_sq + zy_sq > ESCAPE2)
				return i;

			// z = z*z + c

			zy = 2 * zx * zy + y;
			zx = zx_sq - zy_sq + x;
		}

		return i;
	}

	template<size_t Size>
	constexpr auto convert(size_t x){
		auto const p  = (ESCAPE2) / (Size - 1);
		auto const xd = static_cast<double>(x);

		return p * xd - ESCAPE;
	}

	void plotStart(){
		printf("P2\n");
		printf("%lu %lu\n", SIZE_X, SIZE_Y);
		printf("%ul\n", 255);
	}

	void plot(size_t, size_t, size_t iterations, size_t c){
		uint8_t const x = c == iterations ? 255 : 0;

		printf("%3u ", x);
	}

	void plotLn(){
		printf("\n");
	}

	constexpr void plotFinish(){
	}

	void build(size_t iterations){
		plotStart();

		for(size_t y = 0; y < SIZE_Y; ++y){
			double yr = convert<SIZE_Y>(y);

			for(size_t x = 0; x < SIZE_X; ++x){
				auto const xr = convert<SIZE_X>(x);

				plot(x, y, iterations, Z(xr, yr, iterations));
			}

			plotLn();
		}

		plotFinish();
	}

} // anonymous namespace


int main(int argc, char **argv){
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <number>\n", argv[0]);
		return 1;
	}

	size_t const iter = atol(argv[1]);

	build(iter);
}

