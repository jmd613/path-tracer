#pragma once

#include <optional>

#include "IHittable.h"
#include "Ray.h"
#include "Vec3.h"

class Sphere : public IHittable
{
public:
   Sphere() = delete;
   Sphere(math::Vec3 origin, double radius, std::shared_ptr<Material> mat) :
      origin_(origin), radius_(radius), mat_ptr_(mat)
   {}

   std::optional<HitRecord> Hit(const math::Ray &ray, double min_dist,
                                double max_dist) const override;

   math::Vec3 GetOrigin() const { return origin_; }
   double GetRadius() const { return radius_; }

private:
   math::Vec3 origin_;
   double radius_;
   std::shared_ptr<Material> mat_ptr_;
};