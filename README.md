LSOBIA
======

OTB Module providing Large Scale Object Based Image Analysis functionalities.

# Dependencies
* [OTB](https://www.orfeo-toolbox.org/)
* MPI (developped and validated with mpich-3.2)

# How to build it
LSOBIA can be built like any other [otb remote module](https://wiki.orfeo-toolbox.org/index.php/How_to_write_a_remote_module)
You can build it either from within OTB's sources or outside it.


# How to use it

## LSSegmentation

### Parameters
LSOBIA provides an OTBApplication, LSSegmentation (Large Scale Segmentation).

```bash
Parameters: 
        -progress                          <boolean>        Report progress 
        -io.im                             <string>         Input image path  (mandatory)
        -io.out.dir                        <string>         Output directory  (mandatory)
        -io.out.labelimage                 <string>         Label Image Name  (optional, off by default)
        -io.temp                           <string>         Directory used for temporary data  (mandatory)
        -algorithm                         <string>         Segmentation algorithm name [baatz/meanshift] (mandatory, default value is baatz)
        -algorithm.baatz.numitfirstpartial <int32>          Number of iterations for first partial segmentation  (optional, on by default, default value is 1)
        -algorithm.baatz.numitpartial      <int32>          Number of iterations for partial segmentation  (optional, on by default, default value is 1)
        -algorithm.baatz.stopping          <float>          Value for stopping criterion  (optional, on by default, default value is 40)
        -algorithm.baatz.spectralweight    <float>          Value for spectral weight  (optional, on by default, default value is 0.05)
        -algorithm.baatz.geomweight        <float>          Value for geometric (shape) weight  (optional, on by default, default value is 0.95)
        -algorithm.baatz.aggregategraphs   <string>         Aggregation of graph traces [on/off] (optional, off by default, default value is on)
        -algorithm.meanshift.maxiter       <int32>          max number of iterations  (mandatory)
        -algorithm.meanshift.spatialr      <float>          Spatial bandwidth  (optional, off by default)
        -algorithm.meanshift.spectralr     <float>          Spectral bandwidth  (optional, off by default)
        -algorithm.meanshift.threshold     <float>          Threshold  (optional, off by default)
        -algorithm.meanshift.ranger        <float>          Spectral range ramp  (optional, off by default)
        -algorithm.meanshift.modesearch    <string>         Activation of search mode [on/off] (optional, off by default, default value is on)
        -processing.memory                 <int32>          Maximum memory to be used on the main node  (mandatory)
        -processing.maxtilesizex           <int32>          Maximum size of tiles along x axis  (mandatory)
        -processing.maxtilesizey           <int32>          Maximum size of tiles along x axis  (mandatory)
        -processing.writeimages            <string>         Activation of image traces [on/off] (mandatory, default value is on)
        -processing.writegraphs            <string>         Activation of graph traces [on/off] (mandatory, default value is on)
        -inxml                             <string>         Load otb application from xml file  (optional, off by default)


```

### Monoprocessor execution

```bash
  otbcli_LSSegmentation "-io.im" "${INPUT_IMAGE}" "-io.out.dir" "${OUTPUT_DIRECTORY}" -io.out.labelimage "LabelImage" "-io.temp" "${TEMP}" "-algorithm" "baatz" "-algorithm.baatz.numitfirstpartial" "5" "-algorithm.baatz.numitpartial" "5" "-algorithm.baatz.stopping" "40" "-algorithm.baatz.spectralweight" "0.5" "-algorithm.baatz.geomweight" "0.5" "-algorithm.baatz.aggregategraphs" "on" "-processing.writeimages" "on" "-processing.writegraphs" "on" "-processing.memory" "2000" "-processing.maxtilesizex" "1000" "-processing.maxtilesizey" "1000"
```

### Multiprocessor execution

Simply add *mpirun -np ${NUM_PROC}* 

```bash
  mpirun -np 4 otbcli_LSSegmentation "-io.im" "${INPUT_IMAGE}" "-io.out" "${OUTPUT_DIRECTORY}" -io.out.labelimage "LabelImage" "-io.temp" "${TEMP}" "-algorithm" "baatz" "-algorithm.baatz.numitfirstpartial" "5" "-algorithm.baatz.numitpartial" "5" "-algorithm.baatz.stopping" "40" "-algorithm.baatz.spectralweight" "0.5" "-algorithm.baatz.geomweight" "0.5" "-algorithm.baatz.aggregategraphs" "on" "-processing.writeimages" "on" "-processing.writegraphs" "on" "-processing.memory" "2000" "-processing.maxtilesizex" "250" "-processing.maxtilesizey" "250"
```

This produces an image output containing labels of the Baatz Segmentation algorithm.

## LSSmallRegionMerging

## Other binaries
You can find useful application and binaries execution examples in the unitary tests. To enable these tests, simply build the module with BUILD_TESTING=ON.


# Output Samples

## Baatz segmentation

The next image is obtained with the previous Monoprocessor command ran on a sample image

![input file](https://cloud.githubusercontent.com/assets/26165185/24074238/073c72b4-0c05-11e7-82e3-497a28d10db1.png) : 
![baatz-segmentation](https://cloud.githubusercontent.com/assets/26165185/24074247/3a061d62-0c05-11e7-9266-31a16d203afc.jpg)


# TODO
* Implement an application for small region merging algorithms
* Implement an application for polygon simplification


# Licence
Please see the license for legal issues on the use of the software.
