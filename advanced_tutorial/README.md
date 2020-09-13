### The extended class tutorial: Superclasses, derived classes and a  tridiagonal matrix solver for a toeplitz matrix solving the Poisson equation.

This tutorial is a extension of the previous class tutorial where we implemented a simple class to solve an integral numerically using the trapezoidal rule. In many cases, though, the problems we want to solve are far more complicated and require much more code. In these cases, it's very useful to organize our codes into a more hierarchical way in the following sense:
  1. Codes that are needed for multiple purposes are only written *once*.
  2. The code project as a whole is organized in a logical way so that the codes becomes easily readable, "debuggable" and usage becomes a breeze

We showcase how one can effectively use a so-called *superclass* and *derived classes* to create a well-structured, readable and reusable code. The problem we solve is a matrix equation Av = q, where A is a tridiagonal toeplitz matrix derived from the Poisson equation using a finite difference scheme.

A couple notes on what you can expect from this tutorial:

1. We assume you've completed [project 1](http://compphysics.github.io/ComputationalPhysics/doc/Projects/2020/Project1/pdf/Project1.pdf) in FYS3150. The purpose here is that we show you an efficient and clean way to write codes so that you can compare and contrast with your own codes, and base future projects in the course on the implementations shown here.
2. We describe what a *superclass* and a *derived class* is, and how to implement them using project 1 as the example.
3. We show you how to automate tasks using python scripts using the *os* library. This is a very useful library that can perform a lot of tasks that you'd normally have to do manually.
    - You can compile and execute codes (instead of using makefiles). Using a python script is usually more flexible (and far more useful).
    - You can create directories and move files that you codes produce around.
    - And much more. More on this at the end of the tutorial.
4. We extensively use Armadillo to store values instead of pointers as these are much easier to handle in C++ and give a more readable code. We recommend you do the same in future projects.

Now that the baseline for tutorial is established, let's commence and dive into the intricacies of what lies ahead and improve our coding skills in C++!



#### How to run the codes
You can clone down the project to your computer and study the codes there. Reading the tutorial is easier online though (or through README preview in Atom).

In order to run the codes, you simply type in a Linux or macOS command line:

```terminal
python3 main.py
```

Which gives the prompts:

1.
  ```terminal
  Give number of mesh points N:
  ```
  Here you type number of points N you want.

2.
  ```terminal
    Choose algorithm: general/special:
  ```
  Type general or special.


#### Superclasses, classes and inheritance
More often than not, we want to implement a set of codes where a subset of the codes all needs to perform the same operations. This motivates the idea of creating a hierarchy of classes with the following structure:
1. A *superclass* at the very top. Its purpose is to provide variables and methods that *all* (or at least most) derived classes will need.

2. A set of *derived classes*. They inherit the variables and methods declared in the superclass.

In this particular project, we've created a superclass called *TridiagonalMatrixSolver*.
In this superclass, we've implemented:
  1. A function that initializes variables, vectors and so on that all derived classes needs.
  2. A function that can write the computed solution vector to a file.

Before we study the specific implementation, however, we ought to take a quick peak at the generic structure of a superclass:

```C++
class Superclass {
private:
  /* Variables and methods that only the superclass needs. We leave this one empty in our use case. */
protected:
/* Variables and methods that derived classes can inherit from the superclass */

public:
/* Variables and methods that will also be inhereted by are accessible from outside the superclass */
};
```
We want you to especially take note of the appearance of a new section called *protected*. Here we can declare variables that we want to be inherited, but that we do not want to be able to change from outside the class. The section is very similar to the *private* section, except that derived classes cannot inherit variables or methods declared in the private section.

So the main difference from the last tutorial is that a superclass also includes a *protected* section. But this begs the question, how do we create a derived class from a superclass? Generically, this is done in the following way:

```C++
class DerivedClass : public SuperClass{
private:
  /* private member variables and methods */

public:
  /* Public member variables and methods */
};
```
The derived class will here inherit all variables and methods that are declared in the *protected* and *public* section. Neat!

#### Declaration of superclass and derived classes for project 1

We now return to the specific declaration of the superclass, which we list below.

```C++
class TridiagonalMatrixSolver {
protected:
  int m_N;
  double m_stepsize;
  vec m_q, m_x, m_v;
  ofstream m_ofile;

public:
  void initialize(int N, double f(double x));
  void write_to_file(string filename);
};
```
Let's break the code down (and the motivation for all its content):
1. Notice that in the superclass, we've declared member variables as *protected* instead of *private*.
    - But why? From the previous tutorial, we declared the variables as private.
    - The reason is that derived classes can *only* inherit variables and methods that are declared as *protected* or *public*. Thus, we must avoid using *private* unless the variables are only needed by the superclass.
    - Yes, we mentioned this above, but we want to stress the point :-)
2. The protected member variables are variables that are needed by *all* or *most* derived classes. Otherwise, the variables should be declared in the derived class instead.
    - Here we've declared a set of variables that all derived classes will use:
        1. *m_N* is the size of the vectors.
        2. *m_q* is the RHS of the matrix equation studied here.
        3. *m_x* is the mesh points which is computed using *m_stepsize*.
        4. *m_v* is the solution vector of the matrix equation Av=q.
    - Notice, however, that *m_stepsize* is declared as private in the superclass since this member variable is only used by the superclass and so inheritance by derived classes is unnecessary.
3. The public methods should be needed by every (or more than one) derived class, or else it should be declared in the derived class instead.
4. The *initialize* method should only contain code that *all* or *most* derived classes need.
5. The *write_to_file* method is there because every derived class will need to write their result to file. This too should be implemented in such a way that every derived class can use it.
6. As a final note: the reason why we want a superclass is to avoid writing the exact same lines of code in all other classes that needs it (this would be utterly wasteful - why would you want to write the same code over and over again when it can simply be written once?). It's simply much tidier to write it once for re-usage and readability.

Moving on, we'll first list the declaration of the superclass and its derived classes in the header file *tridiagonalmatrixsolver.hpp* :

```C++
#ifndef TridiagonalMatrixSolver_HPP
#define TridiagonalMatrixSolver_HPP
#include <fstream>
#include <armadillo>

using namespace std;
using namespace arma;

class TridiagonalMatrixSolver {
protected:
  int m_N;
  double m_stepsize;
  vec m_q, m_x, m_v;
  ofstream m_ofile;

public:
  void initialize(int N, double f(double x));
  void write_to_file(string filename);
};


class ThomasSolver : public TridiagonalMatrixSolver {
private:
  vec m_a, m_b, m_c;
  void forward_substitution();
  void backward_substitution();
public:
  void init(int N, double f(double x));
  void solve();
};

class SpecialThomasSolver : public TridiagonalMatrixSolver {
private:
  void forward_substitution();
  void backward_substitution();
public:
  void init(int N, double f(double x));
  void solve();
};

#endif

```
The way we've declared the derived classes *ThomasSolver* and *SpecialThomasSolver*, gives us the ability to use *initialize* and *write_to_file* from *TridiagonalMatrixSolver* while simultaneously defining member variables and methods specific to the derived classes.
1. Although both *ThomasSolver* and *SpecialThomasSolver* both contain private methods called *forward_substitution* and *backward_substitution*¸ the specific implementations of these methods are different and unique to the specific derived classes. But more on this later, we just want to stress that even though these have the same names, they do not contain the same code.
2. The public methods *init* and *solve* are also named identically. But these too will contain different codes specific to the derived class.
3. The reason we use the same naming scheme is that the usage of both classes will be identical. This simplifies the usage of the derived classes.

Moving forward, let's look at the specific implementation of the superclass found in *tridiagonalmatrixsolver.cpp*.
```C++
#include "tridiagonalmatrixsolver.hpp"

void TridiagonalMatrixSolver::initialize(int N, double f(double x))
{
  m_N = N;
  m_stepsize = 1./(m_N+1);
  m_q = vec(m_N);
  m_v = vec(m_N);
  m_x = linspace(m_stepsize, 1-m_stepsize, m_N);
  double hh = m_stepsize*m_stepsize;

  for (int i = 0; i < m_N; i++){
    m_q(i) = hh*f(m_x(i));
  }
}

void TridiagonalMatrixSolver::write_to_file(string filename)
{
  m_ofile.open(filename);
  for (int i = 0; i < m_N; i++){
    m_ofile << m_x(i) << " " << m_v(i) << endl;
  }
  m_ofile.close();
}
```
Let's break down the content here:

1. We must include the header file.
2. The *initialize* method only contains code that is needed by all derived classes:
    - We specify the parameter m_N (which is the length of the vectors in the class).
    - We use this parameter to specify:
      * The stepsize *m_stepsize*
      * The solution vector *m_v*
      * The mesh point vector *m_x*
      * The right hand side vector *m_q*.
3. The *write_to_file* contains code that writes the mesh points *m_x* and the solution vector *m_v* to a given file named *filename*
    - This is needed by all derived classes.

It should be clear now, that the superclass only contain methods that are generic enough that they can be used by any derived class. Even though the derived classes we've created (which we'll study shortly) implement different algorithms, they all need to initialize certain variables and they all need to write their results to a file.

#### The derived classes
We've called the first derived class *ThomasSolver*. This class contains variables and methods needed specifically to use the generalized Thomas algorithm. We've shown the declaration of it in the header file, but let's look at it's specification found in *thomas.cpp* :

```C++
#include "tridiagonalmatrixsolver.hpp"

void ThomasSolver::init(int N, double f(double x))
{
  initialize(N, f);  //ThomasSolver inherited this from TridiagonalMatrixSolver, so we can freely use it here.
  m_a = vec(m_N).fill(-1.);
  m_b = vec(m_N).fill(2.);
  m_c = vec(m_N).fill(-1);
  m_v = vec(m_N).fill(0.);
}

void ThomasSolver::solve()
{
  forward_substitution();
  backward_substitution();
}

void ThomasSolver::forward_substitution()
{
  for (int i = 1; i < m_N; i++){
    m_b(i) = m_b(i) - m_a(i-1)*m_c(i-1)/m_b(i-1);
    m_q(i) = m_q(i) - m_a(i-1)*m_q(i-1)/m_b(i-1);
  }
}

void ThomasSolver::backward_substitution()
{
  m_v(m_N-1) = m_q(m_N-1)/m_b(m_N-1);
  for (int i = m_N-2; i >= 0; i--){
    m_v(i) = (m_q(i) - m_c(i)*m_v(i+1))/m_b(i);
  }
}

```

Breakdown time (no crying though, this is all fun):
1. Again, we've included the header file at the top.
2. The *init* method:
    - First of all, it calls the *initialize* method inherited from the superclass *TridiagonalMatrixSolver*.
        * This is to initialize the member variables that are generically implemented in the superclass, but is simultaneously needed by the derived class before anything else can be done.
    - Then it initializes details specific to itself.
        * We initialize the upper off-diagonal vector *m_a* with values -1.
        * We initialize the diagonal vector *m_b* with values 2.
        * We initialize the lower off-diagonal vector *m_c* with values -1.
        * Finally, we intialize the solution vector *m_v* with zeros.
3. The *forward_substitution* method implements the generalized forward substitution algorithm.
4. The *backward_substitution* method implements the generalized backward substitution algorithm
5. Note that both *forward_substitution* and *backward_substitution* are declared as *private* functions in the header file.
  - This is because both of these methods are only called by *solve* which is the public method we have access to outside of the class.
  - Methods that are called by other methods in this way are called *subroutines*.
    * Why bother with this sort of decomposition of methods? Why not just place the codes for both *forward_substitution* and *backward_substitution* directly into *solve*?
    * The motivation for this is two-fold:
      1. The code becomes more readable, since the subroutines describe specifically which part of the algorithm is performed.
      2. The decomposition gives us an easier way to debug our code. This is because we can remove function calls to isolate issues instead of manually removing large code blocks.

We've implemented the specialized Thomas algorithm in a similar way. The code is found in *special_thomas.cpp* and is listed below:

```C++
#include "tridiagonalmatrixsolver.hpp"


void SpecialThomasSolver::init(int N, double f(double x)){
  initialize(N, f);
}

void SpecialThomasSolver::solve()
{
  forward_substitution();
  backward_substitution();
}

void SpecialThomasSolver::forward_substitution()
{
  for (int i = 1; i < m_N; i++){
    m_q(i) = m_q(i) + 1.*i/(i+1)*m_q(i-1);
  }
}

void SpecialThomasSolver::backward_substitution()
{

  m_v(m_N-1) = ((double) m_N/(m_N+1))*m_q(m_N-1);
  for (int i = m_N-2; i >= 0; i--){
    m_v(i) = ((double) (i+1)/(i+2))*(m_q(i)+m_v(i+1));
  }
}
```

This code has the exact same structure as the *ThomasSolver*. Here *forward_substitution* and *backward_substitution* are also private methods. But the details of the implementations are different from those found in *ThomasSolver*. Using the same names for all the methods are useful since the usage of the different derived classes become identical although they implement different algorithms. This is the reason we've chosen the same naming schemes (Yeah, yeah.. We mentioned this above, but again we want to stress the usefulness of structuring the code in this way).

This concludes the discussion of the most important parts of the hierarchical structure of classes and how these can efficiently be used to create a readable, reusable and well-structured code.
Any other questions about them can easily be directed to us at our computer labs. But now, we want to introduce you to one more important and immensely useful tool that is overlooked in most introductory courses to Python.

#### Automating (super tedious) tasks with python scripts
Finally, we want to introduce you to automation of what most would call *tedious* tasks using python. This will only work if you have a Linux or macOS command line (or if you use WSL in Windows since you're effectively using a Linux command line there as well). We want to introduce this because this isn't typically taught as part of an introductory course in python. Nor is it specifically taught in FYS3150, and it's something most must discover and learn on their own. But we think this is essential to any developer's/computational scientist's toolkit and we'll thus give you a quick introduction to it here.

- In python, there's a library called *os*. This library gives you the ability to use a python script to run commands that you'd typically run manually in the command line. These include:
  1. Compiling and executing C++ codes.
  2. Checking that directories exists and create them if they do not.
  3. Moving or deleting files/directories.
  4. Printing out feedback on what part of the script is currently being performed.
  5. It has many more uses, but for now we'll restrict ourselves to the four mentioned above. With the tools presented here, you'll easily be able to discover solutions to any needs you have on your own.

##### Replacing makefiles with compilation and execution of codes using python

Say we have a set of C++ files in our directory and we want to compile them. We can then use the *os* library to compile them in the following way:

```python
import os
os.system("c++ -o main.out main.cpp class_code1.cpp class_code2.cpp")
```
We can do this more effectively by using what is known as RegEx commands (RegEx = regular expressions). This can be done by

```python
import os
os.system("c++ -o main.out *.cpp")
```
From now on, we'll exclude the import of *os*, but this library must always be imported! The RegEx part of the command is
```terminal
*.cpp
```
which tells the compiler to search for *all* files that ends with .cpp and compile them. When you have several C++ files that ends with .cpp and you want to compile them, this type of RegEx command saves you alot of unnecessary explicit typing of names of .cpp files. If only you knew this sooner, right?

In many cases, it's convenient to place all C++ files in a subdirectory to get a cleaner and more structured project folder. Say we place all the C++ files in a folder called "cpp_files". In order to run the same compilation command as above using python, we'd then instead write
```python
os.system("c++ -o main.out ./cpp_files/*.cpp")
```
which tells the computer to search for all files ending with .cpp in the directory "cpp_files". This is even better!

##### Checking if a directory exists and create it if doesn't exist.
In many cases, we want to move files to certain directories. But if they do not yet exist, we want to create them so that files can be moved there.
Say we want to move a file *filename* to a directory called *directory*. Then we can check if it exists and create it if it yet doens't using the following python code:
```python
path = "./directory"
if not os.path.exists(path): #Checks is path = "./directory" exists
  os.makedirs(path) #If it doesn't exists, we create it using this command.
```
Note that we define
```python
path = "./directory"
```
instead of
```python
path = "/directory"
```
to tell the computer to search for the directory from the current directory we're in. Writing "./" before the name of the directory tells the computer to search for the directory from the current directory we're in. Generally "." means the current directory. The *technical term* for this is called *relative path*. When using *os.makedirs(...)*, you should always use the relative path of the directory as explained above.

##### Moving files from the current directory to subdirectories
Say we've executed some code that produces some file that contains data from the performed computations. It's then common that we'd move the file to a some directory that we'll for our purposes call *results*. Say the file is called *data.txt* so that filename = "data.txt". To move it to a subdirectory, we'll first need to check whether the subdirectory exists (and create it if it doesn't) and move it there. This can be done by the following python code:

```python
path = "./results"
filename = "data.txt"
if not os.path.exists(path):
  os.makedirs(path)
os.system(" ".join(["mv", filename, path]))
```
This may look a bit complicated, so let's break it down. The part
```python
" ".join(["mv", filename, path])
```
results in the string
```python
"mv data.txt ./results"
```
To break it down. " ".join(list_of_strings) tells python to stitch together all the elements of the list ["mv", filename, path] separated by a space. As an example of a different usage, say we'd want to stitch together a set of strings separated by an underscore "_" instead, then we'd write:
```python
"_".join(["strings1", "string2", "strings3", ..., "stringn"])
```
which would result in the following *concatenated* string
```python
"string1_string2_string3_..._stringn"
```
This gives us a powerful method to stitch together strings that contain directory names, filenames etc. Names of directories, filenames and so on may even be sent in by the command line and can be generically combined into commands like the ones above to automate everything.

##### Printing out feedback using the command *echo*
Although you can use the *print* function in python to give yourself feedback about what the python script is doing at a particular time, you can also use the *echo* function provided by any Linux/Unix command line.
Say we want to print that we're compiling the code and the output we want printed to the command line is "compiling...", then we can write the following in a python script:
```python
echo compiling...
```
which results in a printout of "compiling..." to the command line.

##### The python script that automates this project
Below we list the python script which automates the usage of all the classes in this project.

```python
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

```
This is used together with the *main.cpp* code
```C++
#include "tridiagonalmatrixsolver.hpp"
#include <cmath>
#include <string>
#include <time.h>

double f(double x);

int main(int argc, char const *argv[]) {

  clock_t start, end;
  double timeused;
  int N = atoi(argv[1]);
  string algorithm = string(argv[2]);
  string filename = algorithm + "_N_" + to_string(N) + ".txt";

  if (algorithm == "general"){
    ThomasSolver my_solver;
    my_solver.init(N, f);
    start = clock();
    my_solver.solve();
    end = clock();
    timeused = (double) (end-start)/CLOCKS_PER_SEC;
    my_solver.write_to_file(filename);
  }

  if (algorithm == "special"){
    SpecialThomasSolver my_solver;
    my_solver.init(N, f);
    start = clock();
    my_solver.solve();
    end = clock();
    timeused = (double) (end-start)/CLOCKS_PER_SEC;
    my_solver.write_to_file(filename);
  }

  return 0;
}

double f(double x){
  return 100.*exp(-10*x);
}

```

#### Final recommendations

Always use Python for data analysis, plotting and so on. Only use C++ to perform the expensive computations of the projects you solve, and use Python for everything else. This includes:
  1. Compilation and execution of codes
  2. Moving plots, results etc and creating directories..
    * Never again will you do this manually, eh? :)
  3. Data analysis like computing relative error and so on.


##### That's all for now! We hope this tutorial illustrates how useful it is to use superclasses combined with derived classes, and how powerful it is to use Python as a tool for automation with the help from the library *os*.
