# esp_idf_cpp_examples
This repo contains esp-idf example projects written in C++.  
The projects were written for esp-idf v4.0 and are intended to demonstrate the use of custom esp-idf components I have written.

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


