#include <iostream>
#include "ResonanceType.hpp"
#include "Particle.hpp"

int main()
{
    char f[] = "f";

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

    char g[] = "g";
    ParticleType const particle3(g, 4, 5);
    ResonanceType const particle4(g, 6, 7, 8);
    particle3.PrintProperties();
    particle4.PrintProperties();

    std::cout << particle3.Getname() << '\n';
    std::cout << particle3.Getmass() << '\n';
    std::cout << particle3.Getcharge() << '\n';

    std::cout << particle4.Getname() << '\n';
    std::cout << particle4.Getmass() << '\n';
    std::cout << particle4.Getcharge() << '\n';
    std::cout << particle4.GetWidth() << '\n';

    char h[] = "h";
    char i[] = "i";

    Particle::AddParticleType(g, 2., 1);
    Particle::AddParticleType(f, 2., 1);
    Particle::AddParticleType(f, 2., 1);
    Particle::AddParticleType(h, 2., 1);
    Particle::AddParticleType(i, 2., 1);

    Particle P(1, 1, 1, f);
    Particle P2(1, 1, 1, g);
    Particle P3(1, 1, 1, h);
    Particle P4(1, 1, 1, i);

    // F Particle P(1., 1., 1., f);

    /*


    P.AddParticleType(g, 1, 1, 0);
    P.AddParticleType(f, 2, 2);
    P.AddParticleType((char *)"Rho", 1, 1);


    char a = 'a';
    char *z = &a;
    Particle p(1., 1., 1., z);
*/
    P.Print_SomeProp();
    P2.Print_SomeProp();
    P3.Print_SomeProp();
    P4.Print_SomeProp();

}