/* **************************************************************************************************** */

#pragma once

/* **************************************************************************************************** */

#include "../headers/types.hpp"

/* **************************************************************************************************** */

namespace mage {
    class vec3 {
        public:
            vec3();
            vec3(real, real, real);

            void invert();
            real magnitude();
            real squareMagnitude();
            void normalize();

            void operator*=(real);
            vec3 operator*(real);

            void operator+=(vec3&);
            vec3 operator+(vec3&);

            void operator-=(vec3&);
            vec3 operator-(vec3&);

            void addScaledVec(vec3&, real);

            vec3 componentProduct(vec3&);
            void componentProductUpdate(vec3&);

            real scalarProduct(vec3& other);
            real operator*(vec3& other) = delete;

            real x;
            real y;
            real z;
        protected:

        private:
            real pad;
    };
};

/* **************************************************************************************************** */