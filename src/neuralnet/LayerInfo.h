//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <string>
#include <vector>

/**
 * Contains information on a layer. If some arguments are not applicable they assume default values.
 *
 * Provides multiple constructors for ease of use.
 *
 */
//TODO: Do we need LayerInfo at all? Instead store it in specific layers, removes obsolete members in a general LayerInfo object.
class LayerInfo {
private:
    std::string type;
    std::vector<int> inputDimensions; /**! @see Wrapper for conventions of order**/
    std::vector<int> outputDimensions; /**! @see Wrapper for conventions of order**/
    int numFilters;
    std::vector<int> filterDimensions;
    int zeroPadding; //TODO: changed from design doc
    bool biased;

public:


    /**
     * Constructor for layers without weights and filters.
     *
     * e.g. Activation, Normalization, Input, Loss, FullyConnected...
     *
     * @param type
     * @param inputDimensions
     * @param outputDimensions
     */
    LayerInfo(std::string type, std::vector<int> inputDimensions, std::vector<int> outputDimensions);


    /**
     * Constructor for layer applying weights and filters
     *
     * e.g. Convolution
     *
     * @param type
     * @param inputDimensions
     * @param outputDimensions
     * @param numFilters
     * @param filterDimensions
     * @param zeroPadding
     * @param biased
     */
    LayerInfo(std::string type,
              std::vector<int> &inputDimensions,
              std::vector<int> &outputDimensions,
              int numFilters,
              std::vector<int> &filterDimensions,
              int zeroPadding,
              bool biased
    );

    /**
     * Constructor for pooling layers
     *
     * @param type
     * @param inputDimensions
     * @param outputDimensions
     * @param filterDimensions
     * @param zeroPadding
     */
    LayerInfo(std::string type,
              std::vector<int> &inputDimensions,
              std::vector<int> &outputDimensions,
              std::vector<int> &filterDimensions,
              int zeroPadding
    );

    /**
     * Returns a string containing basic information about the layer.
     *
     * For testing and debug.
     *
     * @return
     */
    std::string getInfoString();

    /**
     * Not implemented. Can be used for addtional information.
     *
     * @return
     */
    std::string getInfoJSON();


    //
    // ===============================================
    // Getter Methods
    // ===============================================
    //

    const std::string &getType() const;

    const std::vector<int> &getInputDimensions() const;

    const std::vector<int> &getOutputDimensions() const;

    int getNumFilters() const;

    const std::vector<int> &getFilterDimensions() const;

    int getZeroPadding() const;

    bool isBiased() const;


};



