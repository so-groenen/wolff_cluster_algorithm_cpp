# Real time Wolff Cluster algorithm simulation of the 2D Ising Model 

Solving the 2D Ising Model is notoriously difficult. In the most "naive" Monte-Carlo approach, the Metropolis algorithm, one considers single spin flips. As a result, lots of Monte-Carlo trials are needed to generate uncorrelated (read, visually very distinct) spin configurations. <br> One way out of this is to use **cluster algorithms**.<br>
The [Swendsen-Wang algorithm](https://github.com/so-groenen/swendsen_wang_ising) (Follow the link for some simulation result) generates multiple cluster per Monte-Carlo trial.<br>
The **Wolff algorithm** on the other hand, generates single clusters by randomly picking a spin and growing clusters by adding more spins. <br>

### Demo

[![Live demo](docs/screenshot.png)](https://so-groenen.github.io/wolff_cluster_algorithm_cpp/)


### In this C++ project you can:

* Manually seed a magnetic cluster and see how the cluster grows by flipping neighboring spins
* See how temperature affects magnetic cluster growth
* Use the automatic mode to see how large these clusters can be
* See how temperature affects the size of the clusters

### Background

I started this project one year ago using Raylib. I completly reworked the project while learning about [ImGui](https://github.com/ocornut/imgui). Not much is left from the initial project as I didn't use github back then...<br>
In the end, I created my own small C++ "interface" for ImGui, inspired by Rust egui, called [PhysGui](https://github.com/so-groenen/physgui).<br> The other goal was to use OOP to implement more complicated finite state machines.

### Bibliography:

I learned about these techniques mostly from these two sources:

* [Monte Carlo Simulations of Spin Systems](https://www.physik.uni-leipzig.de/~janke/Paper/spinmc.pdf) by *Wolfhard Janke*
* [Monte Carlo Techniques](https://hef.ru.nl/~tbudd/mct/lectures/cluster_algorithms.html) by *Timothy Budd*, containing highly pedagogical python tutorials for Monte Carlo.  