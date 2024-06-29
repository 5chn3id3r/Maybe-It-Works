# It-works-?

## Goals
- Make a graph neural network to have an overkill turing machine
- Fighting neural network together 

## Method
- Perceptron
- 2 states : Compute then diffusion
- Weight variable
- Add and delete perceptrons and connections
- Immutable input (reading value in memory) and output (writing value in memory) perceptrons

## Configuration
### Locating
Configuration file's location is: '../data/config.txt' from where the program is executed.
Here is the list of required data, as well as their purposes:
```
InputWeightFile: RP to the file containing information about the weight of all input connections.
LinkFile: RP to the file containing information about which neuron is linked to which.
TypeFile: RP to the file containing information about neurons' types.
Neurons: Number of neurons that make up the network.
```

Example:
```
InputWeightFile=.../data/InputWeightFile
LinkFile=../data/LinkFile
TypeFile=../data/TypeFile
Neurons=5
```

### Neuron types
Neuron with its associated neuron type. If not specified, default value (DEFAULT = 0) is set.
Here is the list of neuron types available:
```
 - DEFAULT: 0, normal neuron.
 - INPUT: 1, neuron used to input data in the system.
 - OUTPUT: 2, neuron used to output data off the system.
 - KILLER: 3, neuron that stops the processing of the network.
```

Example:
```
0 : 1
1 : 0
2 : 0
3 : 3
4 : 2
```

### Neuron links
Neuron with the input neuron sources. If no target is specified, or the neuron is not in the list, then no link is made.

Example:
```
0 :
1 : 0
2 : 0
3 : 1 2
4 : 2 3
```

### Input weights
Neuron with weight of all incoming values, ordered in the same fashion as in the links one.
Notice that a neurons noted as INPUT (here neuron 0) can have an associated weight that will be applied on the input data.

Example:
```
0 : 0.5
1 : 0.2
2 : 0.3
3 : 0.1 0.4
4 : 0.25 0.35
```

# TODO
- Perceptron
- NeuralNetwork File
