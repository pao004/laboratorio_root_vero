#include "Particle.hpp"
#include "ResonanceType.hpp"

#include <iostream>
#include <cmath>
#include <cstdlib>

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

    std::cout << "No match->fill!\n";
    return -1;
}

void Particle::AddParticleType(char *name, double mass, int charge, double width)
{
    // ParticleType particle(name, mass, charge);
    // ResonanceType particle2(name, mass, charge, width);

    int index = FindParticle(name);
    // std::cout << "Find eseguito" << '\n';
    std::cout << fNParticleType << '\n';
    if (index == -1 && fNParticleType < fMaxNumParticleType)
    {
        // std::cout << fNParticleType << '\n';

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

    // std::cout << "No space!\n";

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
        if (fParticleType_[i] != nullptr)
        {
            (*fParticleType_[i]).PrintProperties();
        }
        else
        {
            std::cout << "There is no particle with index:" << i << "!\n";
        }
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

int Particle::Decay2body(Particle &dau1, Particle &dau2) const
{
    if (Return_fMass() == 0.0)
    {
        printf("Decayment cannot be preformed if mass is zero\n");
        return 1;
    }

    double massMot = Return_fMass();
    double massDau1 = dau1.Return_fMass();
    double massDau2 = dau2.Return_fMass();

    if (findex_ > -1)
    { // add width effect

        // gaussian random numbers

        float x1, x2, w, y1;

        double invnum = 1. / RAND_MAX;
        do
        {
            x1 = 2.0 * rand() * invnum - 1.0;
            x2 = 2.0 * rand() * invnum - 1.0;
            w = x1 * x1 + x2 * x2;
        } while (w >= 1.0);

        w = sqrt((-2.0 * log(w)) / w);
        y1 = x1 * w;

        massMot += fParticleType_[findex_]->GetWidth() * y1;
    }

    if (massMot < massDau1 + massDau2)
    {
        printf("Decayment cannot be preformed because mass is too low in this channel\n");
        return 2;
    }

    double pout = sqrt((massMot * massMot - (massDau1 + massDau2) * (massDau1 + massDau2)) * (massMot * massMot - (massDau1 - massDau2) * (massDau1 - massDau2))) / massMot * 0.5;

    double norm = 2 * M_PI / RAND_MAX;

    double phi = rand() * norm;
    double theta = rand() * norm * 0.5 - M_PI / 2.;
    dau1.SetP(pout * sin(theta) * cos(phi), pout * sin(theta) * sin(phi), pout * cos(theta));
    dau2.SetP(-pout * sin(theta) * cos(phi), -pout * sin(theta) * sin(phi), -pout * cos(theta));

    double energy = sqrt(fPx_ * fPx_ + fPy_ * fPy_ + fPz_ * fPz_ + massMot * massMot);

    double bx = fPx_ / energy;
    double by = fPy_ / energy;
    double bz = fPz_ / energy;

    dau1.Boost(bx, by, bz);
    dau2.Boost(bx, by, bz);

    return 0;
}

void Particle::Boost(double bx, double by, double bz)
{

    double energy = Calc_total_E();

    // Boost this Lorentz vector
    double b2 = bx * bx + by * by + bz * bz;
    double gamma = 1.0 / sqrt(1.0 - b2);
    double bp = bx * fPx_ + by * fPy_ + bz * fPz_;
    double gamma2 = b2 > 0 ? (gamma - 1.0) / b2 : 0.0;

    fPx_ += gamma2 * bp * bx + gamma * bx * energy;
    fPy_ += gamma2 * bp * by + gamma * by * energy;
    fPz_ += gamma2 * bp * bz + gamma * bz * energy;
}