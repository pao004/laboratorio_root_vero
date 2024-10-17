#include "class.hpp"

class Particle
{
public:
    Particle(double px, double py, double pz, char *name);

    int GetfIndex() const { return findex_; }

    double GetPulsex() const { return fPx_; }
    double GetPulsey() const { return fPy_; }
    double GetPulsez() const { return fPz_; }

    void SetP(double px, double py, double pz)
    {
        fPx_ = px;
        fPy_ = py;
        fPz_ = pz;
    }

    static void AddParticleType(const char *name, double mass, int charge, double width);

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
