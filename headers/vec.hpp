/* **************************************************************************************************** */

#pragma once

/* **************************************************************************************************** */

#include "../headers/types.hpp"

/* **************************************************************************************************** */

namespace mage {
    class vec3 {
        public:
            real x;
            real y;
            real z;

        private:
            real pad;
    };
};

/* **************************************************************************************************** */

namespace mage {
    void invert(mage::vec3&);
    real magnitude(mage::vec3&);
    real squareMagnitude(mage::vec3&);
    void normalize(mage::vec3&);

    void scale(mage::vec3&, real);

    mage::vec3 add(mage::vec3&, mage::vec3&);
    mage::vec3 sub(mage::vec3&, mage::vec3&);

    real scalarProduct(mage::vec3&, mage::vec3&);
    mage::vec3 componentProduct(mage::vec3&, mage::vec3&);
    mage::vec3 vectorProduct(mage::vec3&, mage::vec3&);
};

/* **************************************************************************************************** */