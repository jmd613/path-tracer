#pragma once

#include <memory>
#include <optional>

#include "Ray.h"
#include "Vec3.h"

class Material;

struct HitRecord
{
   math::Vec3 point;
   math::Vec3 normal;
   double dist;
   std::shared_ptr<Material> mat;
};

class IHittable
{
public:
   virtual ~IHittable() = default;
   virtual std::optional<HitRecord> Hit(const math::Ray &ray, double min_dist,
                                        double max_dist) const = 0;
};