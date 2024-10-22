#include "Particle.hpp"
#include "ResonanceType.hpp"

#include <iostream>
#include <cmath>

Particle::Particle(double px, double py, double pz, char *name) : fPx_{px}, fPy_{py}, fPz_{pz}, findex_{FindParticle(name)} {
                                                                      /*
                                                                      std::cout << "Inizio costruttore Particle..." << std::endl;
                                                                      findex_ = FindParticle(name);

                                                                      if (findex_ == -1)
                                                                      {
                                                                          std::cout << "Particella non trovata, findex_ = -1." << std::endl;
                                                                      }
                                                                      else
                                                                      {
                                                                          std::cout << "Particella trovata, findex_ = " << findex_ << std::endl;
                                                                      }

                                                                      std::cout << "Fine costruttore Particle." << std::endl;
                                                                      */
                                                                  };

ParticleType *Particle::fParticleType_[Particle::fMaxNumParticleType] = {nullptr};
int Particle::fNParticleType = 0;

int Particle::GetfIndex() const { return findex_; }

double Particle::GetPulsex() const { return fPx_; }
double Particle::GetPulsey() const { return fPy_; }
double Particle::GetPulsez() const { return fPz_; }

void Particle::Setfindex(int fIndex) { findex_ = fIndex; }

void Particle::SetP(double px, double py, double pz)
{
    fPx_ = px;
    fPy_ = py;
    fPz_ = pz;
}

int Particle::FindParticle(const char *name)
{
    // std::cout << "Inizio FindParticle" << std::endl;
    // std::cout << "Numero di particelle: " << fNParticleType << std::endl;

    for (int i = 0; i < fMaxNumParticleType; ++i)
    {
        // std::cout << i << " iterazione" << std::endl;

        if (fParticleType_[i] != nullptr)
        {
            //  std::cout << "Controllando particella con indice " << i << " e nome " << fParticleType_[i]->Getname() << std::endl;

            if (fParticleType_[i]->Getname() == *name)
            {

                //   std::cout << "Trovata particella: " << name << " con indice " << i << std::endl;

                return i;
            }
        }
    }

    std::cout << "Error: no match!\n";
    return -1;
}

void Particle::AddParticleType(char *name, double mass, int charge, double width)
{
    // ParticleType particle(name, mass, charge);
    // ResonanceType particle2(name, mass, charge, width);

    int index = FindParticle(name);
    // std::cout << "Find eseguito" << '\n';

    if (index == -1 && fNParticleType < fMaxNumParticleType)
    {
        if (width <= 0)
        {
            ParticleType *newParticle = new ParticleType(name, mass, charge);
            fParticleType_[fNParticleType] = newParticle;

            // fParticleType_[fNParticleType] = &particle;
            // std::cout << fParticleType_[0]->Getname() << std::endl;
        }
        else
        {
            ResonanceType *newResonance = new ResonanceType(name, mass, charge, width);
            fParticleType_[fNParticleType] = newResonance;
            // fParticleType_[fNParticleType] = &particle2;
        }
        ++fNParticleType;
    }
    // std::cout << fParticleType_[0]->Getname() << std::endl;
}

void Particle::Print_SomeProp()
{
    std::cout << "Index = " << findex_ << std::endl;
    std::cout << "name = " << fParticleType_[findex_]->Getname() << '\n';
    std::cout << "(Px,Py,Pz) = ( " << fPx_ << " , " << fPy_ << " , " << fPz_ << " )" << std::endl;
}

void Particle::Print_fParticleType()
{
    //(*fParticleType_[0]).ParticleType::PrintProperties();
    for (int i{0}; i < fMaxNumParticleType; ++i)
    {
        (*fParticleType_[i]).PrintProperties();
    }
}

double Particle::Return_fMass() const
{ // provare a passare sia un resonance che un particle type
    int Index = this->GetfIndex();
    return (*fParticleType_[Index]).Getmass();
}

double Particle::Calc_total_E() const
{
    double m_2 = (this->Return_fMass()) * (this->Return_fMass());
    double p_2 = (this->GetPulsex()) * (this->GetPulsex()) + (this->GetPulsey()) * (this->GetPulsey()) + (this->GetPulsez()) * (this->GetPulsez());
    return sqrt(m_2 + p_2);
}

double Particle::InvariantMass(Particle &p)
{
    double E_2 = (p.Calc_total_E() + this->Calc_total_E()) * (p.Calc_total_E() + this->Calc_total_E());
    double p_2_x = (p.GetPulsex() + this->GetPulsex()) * (p.GetPulsex() + this->GetPulsex());
    double p_2_y = (p.GetPulsey() + this->GetPulsey()) * (p.GetPulsey() + this->GetPulsey());
    double p_2_z = (p.GetPulsex() + this->GetPulsez()) * (p.GetPulsez() + this->GetPulsez());
    double p_2 = p_2_x + p_2_y + p_2_z;
    return sqrt(E_2 - p_2);
}