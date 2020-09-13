"""
This python script showcases how one can automate alot of tasks using the os library.
This library allows us to run instructions in the command line from a python script like this one using the function os.system(...)
The library has functionalities that allow us to:
1. Compile and execute C/C++ codes
2. Check that directories exist and create them if they do not
3. Move files around and/or delete them.
and many more functions.

This only works if you have a Linux/Unix command line, so this particular python script
only works for Linux or macOS users, and (maybe) Windows users that utilize WSL.
"""

import os
import sys

N = int(input("Give number of mesh points N: "))
algorithm = input("Choose algorithm: general/special: ")


filename_plot = "_".join([algorithm, "solution", str(N)]) + ".pdf" #Name of figure file
filename_data = "_".join([algorithm, "N", str(N)]) + ".txt" #Name of data file.
plot_path = "/".join([".", "plots", algorithm]) #Directory to place the figure
data_path = "/".join([".", "results", algorithm]) #Directory to place the data file.

#Using *.cpp is so-called RegEx (regular expression) that searches for all files that ends with .cpp and applies the command you've written to them.
#In this case, we want to search the directory ./cpp_codes for all files that ends with .cpp
all_cpp_codes = "./cpp_codes/*.cpp"
compiler_flags = "-larmadillo" #Linker to Armadillo.

#The echo command prints everything you write after "echo". For instance writing "echo yo bro" will print out "yo bro" in the command line.
os.system("echo compiling...")
os.system("g++ -o main.out" + " " + all_cpp_codes + " " + compiler_flags) #compile codes
#You may replace the line above with os.system(" ".join(["g++", "-o main.out", all_cpp_codes, compiler_flags]))

os.system("echo executing...")
os.system("./main.out" + " " + str(N) + " " + algorithm) #Execute code

#First check if the directory exists. Otherwise, create it.
if not os.path.exists(data_path):
    os.makedirs(data_path) #Creates the directory
os.system("mv" + " " + filename_data + " " + data_path) #Move data file to results directory.

os.system("echo creating plots...")
os.system("python3 plot.py" + " " + filename_plot + " " + "/".join([data_path, filename_data])) #Call plot script.

#Check that the directory exists. If it doesn't, this creates it.
if not os.path.exists(plot_path):
    os.makedirs(plot_path)

os.system(" ".join(["mv", filename_plot, plot_path])) #Move file to correct directory.
os.system("echo done.")
