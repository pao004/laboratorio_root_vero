#include "Particle.hpp"
#include <iostream>

Particle::Particle(double px, double py, double pz, char *name) : fPx_{px}, fPy_{py}, fPz_{pz}, findex_{FindParticle(name)} { fPx_ = 0,
                                                                                                                              fPy_ = 0,
                                                                                                                              fPz_ = 0; };

ParticleType *Particle::fParticleType_[Particle::fMaxNumParticleType];

int Particle::FindParticle(const char *name)
{
    for (int i = 0; i < fMaxNumParticleType; ++i)
    {
        if (fParticleType_[i]->Getname() == *name)
        {
            return i;
        }
    }
    std::cout << "Error: no match!\n";
    return -1;
}

/*void Particle::AddParticleType(const char *name, double mass, int charge, double width)
{
    int index = FindParticle(name);

    fParticleType_[index] = new ParticleType(*name, mass, charge);
}*/