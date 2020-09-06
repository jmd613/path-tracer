#pragma once

#include <optional>

#include "Ray.h"
#include "Vec3.h"

struct HitRecord;

class Material
{
public:
   virtual std::optional<std::pair<math::Ray, math::Vec3>> Scatter(
      const math::Ray &ray, const HitRecord &record) const = 0;

   virtual ~Material() {}
};

class Lambertian : public Material
{
public:
   Lambertian(const math::Vec3 &color) : albedo_(color) {}

   virtual std::optional<std::pair<math::Ray, math::Vec3>> Scatter(
      const math::Ray &ray, const HitRecord &record) const override;

private:
   math::Vec3 albedo_;
};

class Metal : public Material
{
public:
   Metal(const math::Vec3 &color, double fuzz) : albedo_(color), fuzz_(fuzz) {}

   virtual std::optional<std::pair<math::Ray, math::Vec3>> Scatter(
      const math::Ray &ray, const HitRecord &record) const override;

private:
   math::Vec3 albedo_;
   double fuzz_;
};
