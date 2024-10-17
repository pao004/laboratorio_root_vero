#include "ResonanceType.hpp"
#include <iostream>

ResonanceType::ResonanceType(char *fName, double fMass, int fCharge, double fWidth) : ParticleType(fName, fMass, fCharge), fWidth_{fWidth} {};

void ResonanceType::PrintProperties() const
{
    ParticleType::PrintProperties();
    std::cout << "Width:" << fWidth_ << '\n';
}
