# Accel
+ Make sure to include the following headerfiles :- iostream and vector
+ This class will work on C++ 14 and above

The function calcerate can perform the sequence of function n times in logarithmic time.
Class 0 sequence: a op<sub>0</sub> b op<sub>0</sub> b op<sub>0</sub> b ... op<sub>0</sub> b
Class 1 sequence: (a) op<sub>1</sub> (a op<sub>0</sub> b) op<sub>1</sub> ...
Class 2 sequence: (a) op<sub>2</sub> ((a) op<sub>1</sub> (a op<sub>0</sub> b)) ...

And so on

Conditions for the operation sequence.
The operation sequence {op<sub>0</sub>,op<sub>1</sub>,...,op<sub>n</sub>} will be accelerable if:
  
### Necessary Requirements:
  + All the operations should be associative
  + op<sub>r</sub> should be distributive over op<sub>k</sub> if r<k

### Optional Requirements
   + All the operations should have an identity element

<b>Time complexity for the computation: </b> d * comp * log(n), where d is the number of operators and comp the maximum time complexity among the operations
