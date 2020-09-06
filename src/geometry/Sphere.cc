#include "Sphere.h"

#include <cmath>

using namespace math;

std::optional<HitRecord> Sphere::Hit(const Ray &ray, double min_dist,
                                     double max_dist) const
{
   auto oc = ray.GetOrigin() - origin_;
   const auto a = ray.GetDirection().LengthSquared();
   const auto b = oc.Dot(ray.GetDirection());
   const auto c = oc.LengthSquared() - radius_ * radius_;
   const auto determinant = b * b - a * c;
   if (determinant < 0) return {};

   double minus_dist = (-b - sqrt(determinant)) / a;
   double plus_dist = (-b + sqrt(determinant)) / a;
   if ((minus_dist < min_dist && plus_dist < min_dist) || minus_dist > max_dist)
      return {};

   double dist = minus_dist > min_dist ? minus_dist : plus_dist;
   auto point = ray.PositionAt(dist);
   return {HitRecord{point, (point - origin_).Normal(), dist, mat_ptr_}};
}