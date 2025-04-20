/* **************************************************************************************************** */

#include "../headers/vec.hpp"

/* **************************************************************************************************** */

void mage::invert(mage::vec3& v){
    v.x = -v.x;
    v.y = -v.y;
    v.z = -v.z;
}

/* **************************************************************************************************** */

real mage::magnitude(mage::vec3& vec){
    return rsqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}

/* **************************************************************************************************** */

real mage::squareMagnitude(mage::vec3& vec){
    return vec.x*vec.x + vec.y*vec.y + vec.z*vec.z;
}

/* **************************************************************************************************** */

void mage::normalize(mage::vec3& vec){
    real l = magnitude(vec);

    if(l > 0){
        vec.x /= l;
        vec.y /= l;
        vec.z /= l;
    }        
}

/* **************************************************************************************************** */

void mage::scale(mage::vec3& vec, real f){
    vec.x *= f;
    vec.y *= f;
    vec.z *= f;
}

/* **************************************************************************************************** */

mage::vec3 mage::add(mage::vec3& v1, mage::vec3& v2){
    mage::vec3 result;

    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;

    return result;
}

/* **************************************************************************************************** */

mage::vec3 mage::sub(mage::vec3& v1, mage::vec3& v2){
    mage::vec3 result;

    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;

    return result;
}

/* **************************************************************************************************** */

mage::vec3 mage::componentProduct(mage::vec3& v1, mage::vec3& v2){
    mage::vec3 result;

    result.x = v1.x * v2.x;
    result.y = v1.y * v2.y;
    result.z = v1.z * v2.z;

    return result;
}

/* **************************************************************************************************** */

real mage::scalarProduct(mage::vec3& v1, mage::vec3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

/* **************************************************************************************************** */

mage::vec3 mage::vectorProduct(mage::vec3& v1, mage::vec3& v2){
    mage::vec3 result;

    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    
    return result;
}

/* **************************************************************************************************** */