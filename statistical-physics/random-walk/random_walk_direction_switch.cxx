#include<iostream>
#include<fstream>
#include<random>
#include<cmath>
#include<vector>

using namespace std;

int main() {
  size_t iterations = 1000;
  size_t N = 1e4;
  double norm = 1.0/N;
  vector<double> points(N, 0.0);
  vector<double> velocities(N, 0.0);
  vector<size_t> point_dist(iterations, 0);
  point_dist[iterations/2] = N;
  random_device gen;
  uniform_real_distribution<double> distribution(0.0, 1.0);

  double D = 0.0;

  ofstream expectation_values("data/expectation_values_ds.dat");
  ofstream point_distribution("data/point_distribution_ds.dat");
  for(size_t n = 0; n < N; n++) {
    double rand = distribution(gen);
    if (rand > 0.5) {
      velocities[n] = 1.0;
    } else {
      velocities[n] = -1.0;
    }
  }
  for(size_t i = 1; i < iterations; i++) {
    double mu = 0.0;
    double sigma = 0.0;
    for(size_t n = 0; n < N; n++) {
      double rand = distribution(gen);
      point_dist[points[n]+iterations/2] -= 1.0;
      if(rand < 0.1) {
        velocities[n] *= -1.0;
      }
      points[n] += velocities[n];
      point_dist[points[n]+iterations/2] += 1.0;

      mu += points[n];
      sigma += points[n]*points[n];
    }

    mu *= norm;
    sigma = sqrt(sigma*norm);
    expectation_values << i << " " << mu << " " << sigma << endl;

    D += sigma*sigma/(2*i);
    
    int center = iterations/2;
    for (int j = 0; j < iterations; j++) {
      point_distribution << j - center << " " << point_dist[j] << endl;
    }
    point_distribution << endl << endl;
  }

  D /= iterations;

  cout << "D=" << D << endl;

  return 0;
}