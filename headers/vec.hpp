/* **************************************************************************************************** */

#pragma once

/* **************************************************************************************************** */

#include "../headers/types.hpp"

/* **************************************************************************************************** */

namespace mage {
    class vec3 {
        public:
            vec3();
            vec3(const real, const real, const real);

            void invert();
            real magnitude();
            real squareMagnitude();
            void normalize();

            void operator*=(const real);
            vec3 operator*(const real) const;

            real x;
            real y;
            real z;
        protected:

        private:
            real pad;
    };
};

/* **************************************************************************************************** */