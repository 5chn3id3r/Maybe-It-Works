#include "neurone.hpp"

float sigmoid(float x) {
    return 1 / (1 + exp(-x));
}