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
  vector<double> points_random_step(N, 0.0);
  vector<size_t> point_dist(iterations, 0);
  point_dist[iterations/2] = N;
  vector<size_t> point_dist_random_step(iterations, 0);
  point_dist_random_step[iterations/2] = N;
  random_device gen;
  uniform_real_distribution<double> distribution(0.0, 1.0);

  double D = 0.0;

  ofstream expectation_values("data/expectation_values.dat");
  ofstream point_distribution("data/point_distribution.dat");
  ofstream expectation_values_random_step("data/expectation_values_random_step.dat");
  ofstream point_distribution_random_step("data/point_distribution_random_step.dat");
  for(size_t i = 1; i <= iterations; i++) {
    double mu = 0.0;
    double mu_random_step = 0.0;
    double sigma = 0.0;
    double sigma_random_step = 0.0;
    for(size_t n = 0; n < N; n++) {
      double rand = distribution(gen);
      double step = distribution(gen);
      point_dist[points[n]+iterations/2] -= 1;
      point_dist_random_step[static_cast<int>(floor(points_random_step[n]))+iterations/2] -= 1;
      if (rand > 0.5) {
        points[n] += 1;
        points_random_step[n] += step;
      } else {
        points[n] -= 1;
        points_random_step[n] -= step;
      }
      point_dist[points[n]+iterations/2] += 1;
      point_dist_random_step[static_cast<int>(floor(points_random_step[n]))+iterations/2] += 1;

      mu += points[n];
      sigma += points[n]*points[n];
      mu_random_step += points_random_step[n];
      sigma_random_step += points_random_step[n]*points_random_step[n];
    }

    mu *= norm;
    mu_random_step *= norm;
    sigma = sqrt(sigma*norm);
    sigma_random_step = sqrt(sigma_random_step*norm);
    D += sigma_random_step*sigma_random_step/(2*i);
    expectation_values << i << " " << mu << " " << sigma << endl;
    expectation_values_random_step << i << " " << mu_random_step << " " << sigma_random_step << endl;
    
    int center = iterations/2;
    for (int j = 0; j < iterations; j++) {
      point_distribution << j - center << " " << point_dist[j] << endl;
      point_distribution_random_step << j - center << " " << point_dist_random_step[j] << endl;
    }
    point_distribution << endl << endl;
    point_distribution_random_step << endl << endl;
  }


  D /= iterations;

  cout << "D=" << D << endl;

  return 0;
}