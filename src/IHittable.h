#pragma once

#include <optional>

#include "Ray.h"
#include "Vec3.h"

struct HitRecord
{
   math::Vec3 point;
   math::Vec3 normal;
   double dist;
};

class IHittable
{
public:
   virtual ~IHittable() = default;
   virtual std::optional<HitRecord> Hit(const math::Ray &ray, double min_dist,
                                        double max_dist) const = 0;
};