#include "class.hpp"

class ResonanceType : public ParticleType
{
public:
    ResonanceType(char *fName, double fMass, int fCharge, double fWidth);

    double GetWidth() const { return fWidth_; }

    void PrintProperties() const;

private:
    const double fWidth_;
};