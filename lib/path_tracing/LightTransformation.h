//
// Created by Leonard on 2025-01-25.
//

#ifndef LIGHTTRANSFORMATION_H
#define LIGHTTRANSFORMATION_H



class LightTransformation {
private:
    explicit LightTransformation(double);

public:
    static const LightTransformation IDENTITY;

    double intensity_factor;

    LightTransformation combine(const LightTransformation&) const;

    static LightTransformation of_factor(double);
};




#endif //LIGHTTRANSFORMATION_H
