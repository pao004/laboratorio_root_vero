#include "class.hpp"

class Particle
{
public:
    Particle(double px, double py, double pz, char *name);

    int GetfIndex() const;

    double GetPulsex() const;
    double GetPulsey() const;
    double GetPulsez() const;

    void Setfindex(int fIndex);

    void SetP(double px, double py, double pz);
    void Print_SomeProp();

    static void AddParticleType(char *name, double mass, int charge, double width = 0.);

private:
    static int FindParticle(const char *name);

    double fPx_;
    double fPy_;
    double fPz_;

    int findex_;

    static const int fMaxNumParticleType{10};

    static ParticleType *fParticleType_[fMaxNumParticleType];

    static int fNParticleType;
};

//siumm prova
