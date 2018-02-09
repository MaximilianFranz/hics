//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <string>
#include <wrapper/DataWrapper.h>
#include <wrapper/WeightWrapper.h>

/**
 * ENUM to identify layers by their type.
 */
enum LayerType {
    ACTIVATION_RELU,
    NORMALIZATION_LOCALRESPONSE,
    LOSS_SOFTMAX,
    POOLING_MAX,
    CONVOLUTION,
    FULLYCONNECTED,
    INPUT,
    CONCAT
};

/**
 * Abstract class Layer defines the public interface for all layers contained in a NeuralNet.
 */
class Layer {
protected:

    Layer* previousLayer = nullptr;
    Layer* nextLayer = nullptr;
    DataWrapper* inputWrapper; //! == previousLayer.getOutputWrapper()
    DataWrapper* outputWrapper; //! == nextLayer.getInputWrapper()

    bool computed;
    bool functionSet;

    LayerType type;
    std::vector<int> inputDimensions;
    std::vector<int> outputDimensions;


public:
    /**
     * Dimension positions in the dimension vectors according to convention in 3D
     */
    const int D3_X_DIM = 2;
    const int D3_Y_DIM = 1;
    const int D3_Z_DIM = 0;


    /**
     * //TODO: Use pointers for execute() signature? Because wrappers are held as pointers!
     * Triggers the computation of the forward propagation. Takes input from inputWrapper and writes to
     * outputWrapper
     *
     * The Executor knows the size the output Wrapper needs by querying getOutputDimensions()
     *
     */
    virtual void forward() = 0;

    /**
     * Returns whether this Layer has been computed
     *
     * @return
     */
    virtual bool isComputed();

    /**
     * Sets the status of this Layer
     *
     * Is called from inside forward, when computation has worked succesfully.
     * @param status to which to set the layer
     * @return
     */
    virtual void setComputed(bool status);

    /**
     * Returns whether this Layer is ready to be computed.
     *
     * A Layer is ready iff the function has been set and previous layers are computed.
     *
     * @return
     */
    virtual bool readyToCompute();

    /**
     *
     * @return
     */
    virtual bool isLayerFunctionSet();

    /**
     * Resets the status of this layer, so that it can be reconfigured.
     */
    virtual void reset();

    /**
     * Initializes the default values of this layer
     *
     * This means: functionsSet is false
     *             computed is false
     *
     */
    virtual void init();

    /**
     * Set previous layer by giving a pointer
     *
     * @param previousLayer which to set as preceeding layer.
     */
    virtual void setPreviousLayer(Layer *previousLayer);

     /**
     * Set next layer by providing a pointer
     *
     * @param nextLayer which to append to this one.
     */
    virtual void setNextLayer(Layer *nextLayer);

    /**
     * Calculates the output dimensions of the layer given the inputDimensions of this instance and it's parameters.
     *
     * Different implementation for each layer type.
     *
     * @return the Dimensions the output Wrapper has to have.
     */
    virtual std::vector<int> calcOutputDimensions() = 0;

    /**
     * Returns the dimensions of the output wrapper.
     *
     * @return dimensions of the output Wrapper.
     */
    virtual std::vector<int> getOutputDimensions() const;

    virtual /**
     * Returns a pointer to the previous layer
     * @return a pointer to the previous layer.
     */
    Layer *getPreviousLayer() const;

    /**
     *
     * @return a pointer to the next Layer after this one.
     */
    Layer *getNextLayer() const;

    /**
     *
     * @return type enum of this layer
     */
    LayerType getType() const;

    /**
     *  Getter
     * @return dimensions of the inputWrapper to this
     */
    const std::vector<int> &getInputDimensions() const;

    DataWrapper *getInputWrapper() const;

    void setInputWrapper(DataWrapper *inputWrapper);

    DataWrapper *getOutputWrapper() const;

    void setOutputWrapper(DataWrapper *outputWrapper);

    void deleteGarbage();

};

