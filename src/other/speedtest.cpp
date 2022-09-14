#include <chrono>
#include <random>
#include <string>

#include "path/path.h"
#include "path/pathbuilder.h"

int main()
{
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_real_distribution<double> dist(-1.8, 1.8);

  double sum = 0;
  int iterations = 100;
  int numPoints = 10000;
  std::vector<Waypoint> points(numPoints);
  for (int i = 0; i < iterations; ++i)
  {
    for (int i = 0; i < numPoints; ++i)
      points[i] = {dist(rng), dist(rng)};

    auto start = std::chrono::high_resolution_clock::now();
    const Path path = PathBuilder(true, 1.5, 1, 3)
                          .addPoints(points)
                          .build();
    const std::chrono::duration<double, std::micro> time =
        std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - start);

    sum += time.count();

    //std::cout << "Iteration " << i << "/" << iterations << "...\n";
  }

  
  pros::lcd::print("Average time (" + std::to_string(iterations) + " iterations, " + std::to_string(numPoints) + " points): " + std::to_string(sum / iterations) + " microseconds\n");

  //std::cout << "Average time (" << iterations << " iterations, " << numPoints << " points): " << sum / iterations << " microseconds\n";
}
