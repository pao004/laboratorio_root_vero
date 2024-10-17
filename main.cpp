#include <iostream>
#include "ResonanceType.hpp"

int main()
{
    char f[] = "d";

    ParticleType particle1(f, 2, 2);

    particle1.PrintProperties();

    ResonanceType particle2(f, 3, 4, 5);

    particle2.PrintProperties();

    std::cout << particle1.Getname() << '\n';
    std::cout << particle1.Getmass() << '\n';
    std::cout << particle1.Getcharge() << '\n';

    std::cout << particle2.Getname() << '\n';
    std::cout << particle2.Getmass() << '\n';
    std::cout << particle2.Getcharge() << '\n';
    std::cout << particle2.GetWidth() << '\n';

    ParticleType *particleArray[2] = {&particle1, &particle2};

    for (int i{}; i < 2; ++i)
    {
        particleArray[i]->PrintProperties();
    }
}