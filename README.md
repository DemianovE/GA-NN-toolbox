#  C-based Framework for Genetic Algorithms, Neural Network Training and Execution

## Overview
This project is an academic portfolio of the C language usage.

The actual purpose of toolbox is a creator/runner of the dedicated Neural Networks
(NN from here) for the purpose of linear and non-liner control and robotics in general. 
This toolbox for historical reasons also contains a PID example for comparison, but 
I think I need to delete it due to change in what the purpose is.

The toolbox was started as a possible code base for the thesis but was later stopped due 
to time limitations. For thesis MATLAB-based toolbox wes made, which is protected by
Slovak University in Bratislava (STU) IP. The current toolbox was inspired by the 
thesis but now moved much further and as such is an individual project and not just C 
version of the thesis toolbox.

### Purpose

The main idea is to create and run NN for the purpose of the control of 
 robotics. Current development is being made to introduce the avia robotics control
for academical purposes. 

***The toolbox is under active development, code is actively updated and improved***

### Models used
The toolbox supports the following types of NN:
- ***FF*** — simple feed forward NN 
- ***SD*** — NN with special Summation and Difference genes which create integral and 
derivative values
- ***RR*** — NN with recurrent layers

### Activation functions
As activation functions following functions are used:

1) ***Sigmoid*** $$
   \sigma(x) = \frac{1}{1 + e^{-x}}, \quad \sigma(x) \in (0, 1)
   $$
2) ***Tangent*** $$
   \tanh(x) = \frac{e^x - e^{-x}}{e^x + e^{-x}}, \quad \tanh(x) \in (-1, 1)
   $$

### Theoretical purpose
The project is in active development, so the usage is theoretical. The purpose is 
to use the ROS2 build in mechanisms to make a C++ code for the simulation of the 
robotics and use the following toolbox to run NN which can be used to control 
robotics in the simulation. The ROS2 code is mostly ready, but the NN toolbox is being
redone to make it robust and follow the C code standards.

### General Architecture of the Project
Currently, the project follows strict folder structure and camelCase general syntax. 
The code is split into modules based on the general idea. There are the following 
modules:
- ***data structures*** — as follows from name, the point of the all data storage interface 
storage. The strict getter/setter interface is followed for the prevention of direct
memory usage. The following structures are present:
    - ***Array*** — the generic array interface which is of the type void*. This is 
    an implementation of the dynamic array structure. The structure is the most important
    structure in the project. Due to void type of it, the wrappers are used to make
    type-specific arrays:
      - ***Array Float*** — float type array which is used in matrices and chromosomes;
    - ***Byte Heap*** — developed structure which should be used for the storage of the 
    chromosomes in one population based on fit. The heap is void also to be generic;
    It used the Array struct for saving and is basically array, as the Array holds all 
    required data. The structure uses the indexing formula to make a tree from the array
    - ***Matrix*** — a structure essential for the NN calculations. Uses the indexing formula
    to save the 2D values in 1D array;
- ***general*** — general purpose code, name says it for itself;
- ***genetic*** — all code related to genetic training and execution;
- ***neural*** — main NN code for the running and execution of the NN.

## Testing
Currently, tests are the way of checking the code and correcting it before the 
configuration-based runner is finished

The tests are made by following command using a Unity library
```shell
cmake --build build # the building of the project
ctests --test-dir build # start of all defined tests
```

Also, for the memory integrity the valgrind is used with following command
```shell
valgrind --exit-on-first-error=yes --leak-check=full ./testprogram
```

## Planned
The following points are planned to be developed or are being developed
1) Byte heap for the Chromosome storage and usage for efficiency (Developed)
2) SIMD operations for matrix math, very important for the O() efficiency (Planned)
3) Config runner to replace CLI inputs and make program "professional" :D (Developed)

## Documentation
Project is using the doxygen for the documentation of all rewritten parts. Please
 use the following command to create it from the code

```shell
doxygen
```
Then navigate to the doc folder and open the index.html file to access the 
documentation 


## Literature
The following literature is used in the project development:

1. **Simon J.D. Prince**  
   *Understanding Deep Learning*. The MIT Press, 2023.  
   URL: [http://udlbook.com](http://udlbook.com)


2. **Ivan Sekaj**  
   *Evolučné výpočty a ich využitie v praxi*. Slovensky. Iris, 2007, p. 157.  
   ISBN: 80-89018-87-4


3. **Ivan Sekaj, Ivan Kénický, and Filip Zúbek**  
   "Neuro-Evolution of Continuous-Time Dynamic Process Controllers".  
   *MENDEL*, vol. 27, no. 2 (Dec. 2021), pp. 7–11.  
   DOI: [10.13164/mendel.2021.2.007](https://doi.org/10.13164/mendel.2021.2.007)  
   URL: [https://mendel-journal.org/index.php/mendel/article/view/153](https://mendel-journal.org/index.php/mendel/article/view/153)


4. **Marc Peter Deisenroth, A. Aldo Faisal, and Cheng Soon Ong**  
   *Mathematics for Machine Learning*. Cambridge University Press, 2020.  
   ISBN: 9781108455145


5. **Thomas H. Cormen et al.**  
   *Introduction to Algorithms*. 3rd Edition. The MIT Press, 2009.  
   ISBN: 9780262033848  
   Format: Hardcover, 1292 pages


6. **MIT 6.006 Introduction to Algorithms**  
   Professors: Erik Demaine, Dr. Jason Ku, Prof. Justin Solomon  
   MIT OpenCourseWare  
   URL: [https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-spring-2020/](https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-fall-2011/)

# License
This project is licensed under the GNU General Public License v3.0 - see the 
LICENSE file for details.