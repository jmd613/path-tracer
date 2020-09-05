#pragma once

#include "../geometry/Sphere.h"
#include "Ray.h"

using math::Ray;
using math::Vec3;

class Material
{
public:
   virtual std::pair<Ray, Vec3> Scatter(const Ray &ray,
                                        const HitRecord &record) const = 0;
};
