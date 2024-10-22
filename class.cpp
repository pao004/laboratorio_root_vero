#include "class.hpp"
#include <iostream>

ParticleType::ParticleType(char *fName, double fMass, int fCharge) : fName_{fName}, fMass_{fMass}, fCharge_{fCharge} {};

    char ParticleType::Getname() const { return *fName_; }
    double ParticleType::Getmass() const { return fMass_; }
    int ParticleType::Getcharge() const { return fCharge_; }

void ParticleType::PrintProperties() const
{
    std::cout << "Name: " << Getname() << '\n';
    std::cout << "Massa: " << Getmass() << '\n';
    std::cout << "Charge: " << Getcharge() << '\n';
}
