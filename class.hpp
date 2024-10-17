#ifndef PROGETTO_HPP
#define PROGETTO_HPP

class ParticleType
{
public:
    ParticleType(char *fName, double fMass, int fCharge);

    char Getname() const;
    double Getmass() const;
    int Getcharge() const;

    virtual void PrintProperties() const;

private:
    const char *fName_;
    const double fMass_;
    const int fCharge_;
};

#endif