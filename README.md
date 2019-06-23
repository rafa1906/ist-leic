# Hello Quantum

## Overview
Hello Quantum is a simplified version of the game with the same name developed by IBM (available [here](https://helloquantum.mybluemix.net/ "Hello Quantum")). In this implementation it can be played via console by running *helloquantum.py*.

Further instructions on how to play the game and aditional trivia can be found [here](https://medium.com/qiskit/hello-quantum-2c1c00fe830c "Hello Quantum - Instructions & Trivia") (note that for simplicity reasons the CZ gate is not available).


## Running Hello Quantum
To play a game of Hello Quantum you first need to add a line of code to helloquantum.py, like so:

```python
hello_quantum("((1, -1, 0), (-1, -1, -1), (-1, 1)):4")
```

Where the first part is a tuple of tuples containing three rows of cells (0, 1 or undecided (-1)) - the **goal board** - and the second part is the **maximum number of plays**.

Further details can be found in *assignment.pdf* (in portuguese).


## Academic details
This project was developed for FP (Fundamentos da Programação) - a first year introductory programming class.

The final grade was **18.38/20.00**.
