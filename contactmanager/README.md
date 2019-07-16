# Contact Manager

## Overview
Contact Manager is a simple system that allows the user to **store people's contact information** using a command line interface.

The program enables the user to store relevant contact data -- an **email** and a **phone number**, which will be stored in association with a **name**. This specific version has **no limit** for the amount of stored contacts, though the best performance can only be guaranteed for numbers in the range of the **tens of thousands** (expanded upon in the **Efficiency** section).


## Running Contact Manager
As was briefly mentioned in the **Overview** section, interaction with Contact Manager happens through a terminal. The program can be compiled using *gcc* and then run in a standard command line. Contact Manager commands will look something like:

```console
a Rick-Sanchez ricksanchez@schwifty.dub 137-132
```

Where the first character determines the requested action and the rest of the command holds the necessary data (dependent on command).

A detailed overview of possible actions and input format can be found in *assignment.md* (in portuguese).


## Efficiency
The main purpose of this project was to familiarize students with the use of **data structures** as a way to **improve performance**. Therefore, a big part of the development process involved deciding what worked best with the possible commands. Since search commands were quite frequent, the main data structure chosen to ensure efficiency was a **hash table**.

As briefly mentioned in the **Overview** section, this hash table only ensures efficiency for a number of contacts in the **tens of thousands**. However, the solution is **scalable**, given that the **hash table dimension** can be easily edited in the code without jeopardizing **memory consumption**.

In any case, for the test cases provided (between 20 000 and 30 000 contacts with frequent search requests) execution times were about **0.02s** and memory consumption **ranged between 5MB-8MB** (tested on a Linux machine with a quad-core i5 and 8GB of RAM).


## Academic details
This project was developed for IAED (Introdução aos Algoritmos e Estruturas de Dados) - a first year introductory programming class about algorithms and data structures.

The final grade was **20.00/20.00**.
