# esp_idf_cpp_examples
This repo contains esp-idf example projects written in C++.  
The projects are written for esp-idf v5.0+ and are intended to demonstrate how to develop for esp-idf in a C++ enviroment.
The examples are organized into directories utilizing different components I have developed.

## Building and Running a Project

1. Clone the repo:  

   ```sh
   git clone https://github.com/myles-parfeniuk/esp_idf_cpp_examples.git
   ```

2. Navigate into cloned repo and run git submodule update:

   ```sh
   cd esp_idf_cpp_examples
   git submodule update --init --recursive
   ```

3. Navigate into the project directory of your choice and run the 
   build & flash commands. 

   For example:
   
   ```sh
   cd esp_idf_cpp_examples/ButtonDriver/single_button_example
   idf.py build
   idf.py flash monitor
   ```


