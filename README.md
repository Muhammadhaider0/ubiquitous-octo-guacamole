# ubiquitous-octo-guacamole
For my Object-Oriented Programming (OOP) homework, I developed a Big Number calculator in C++ to handle large-scale computations, particularly useful in fields like cryptocurrency and cryptography where standard data types are insufficient. The project involved creating a BigNum class that can represent and operate on extremely large integers, far exceeding the limits of built-in data types like int or long.

Key Features:
Big Number Representation:
The BigNum class dynamically stores digits of large numbers using a std::vector<char>, allowing for efficient memory management and operations on arbitrarily large values.

Arithmetic Operations:
The class supports fundamental arithmetic operations such as addition, subtraction, multiplication, division, and modulus. Each operation is carefully implemented to handle carry, borrow, and digit-by-digit computation, ensuring correctness even with massive numbers.

Function Overloading:
Several methods in the class use function overloading, enabling operations between BigNum objects and integers. For example, both add(const BigNum& bigNum) and add(int num) are supported, providing flexibility in usage.

File I/O:
The class includes functionality for reading large numbers from files and writing the results of operations back to files. This ensures that the calculator can handle persistent data and large datasets.

Helper Functions:
Functions like removeLeadingZeros() and clear() ensure that the class maintains efficiency and correctness, removing unnecessary data and handling memory management internally.

General Object-Oriented Design:
The project emphasizes OOP principles like encapsulation, abstraction, and modularity. Each method is designed to operate independently, making the class reusable and extendable for future enhancements, such as adding support for floating-point big numbers.

This Big Number calculator is highly relevant to fields like cryptography, financial computations, and cryptocurrency, where large number arithmetic is essential.
