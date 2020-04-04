![ZigZag image](https://raw.githubusercontent.com/AartOdding/ZigZag/master/ZigZag_04-04-2020.gif)
# ZigZag
ZigZag is a node based programming language that you can use to create interactive graphics in an intuitive and fun way. You create a network of "operators", that perform different steps on the data flowing through them. Each frame all the operators in the network are executed once, which results in a smooth video as output. Because the rendering happens in realtime on the graphics card, interactivity can be added easily by coupling parameters of the network to external signals such as audio levels or sensor data.

ZigZag is designed with customizability and user extensibility in mind. You can create your own operators, data types, and views in C++, and use them from within ZigZag. This allows you to both be very productive, by working in a high level of abstraction, and gives you full customizability where you need by creating new operators and data types in the C++ API.

# Building
Unfortunatly ZigZag cannot yet be downloaded as an executable, and must thus be build from source. To build from source, install the Qt framework, open ZigZag.pro with Qt Creator. Download a recent version of the glm linear algebra library, and add it to the include path. You should now be able to build ZigZag from source in Qt Creator.
