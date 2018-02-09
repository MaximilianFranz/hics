//
// Created by Maximilian Franz on 12.01.18.
//

#ifndef HICS_NAIVELAYER_H
#define HICS_NAIVELAYER_H


#include "layers/Layer.h"

/**
 * Naive Layers do not have a Layerfunction, because they don't perform logic,
 * they are simple forms of control-flow layers
 */
class NaiveLayer : public Layer{

};


#endif //HICS_NAIVELAYER_H
