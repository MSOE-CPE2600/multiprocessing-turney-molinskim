# System Programming Lab 11 Multiprocessing

This project generates Mandelbrot fractal images and movies using multiprocessing. The 
images and movies demonstrate different zoom 
levels and are processed in parallel for 
efficiency

## How to Build
make clean
make
./mandel -x <x_center> -y <y_center> -s <scale> -W <width> -H <height> -m <max_iterations> -o <output_file>
ex: ./mandel -x -0.5 -y 0 -s 2 -W 500 -H 500 -m 1000 -o mandel.jpg
## Generate Movie
./mandelmovie -p <num_processes> -f <num_frames> -x <x_center> -y <y_center> -s <initial_scale> -m <max_iterations> -t <num_threads>
ex: ./mandelmovie -p 4 -f 50 -x -0.5 -y 0 -s 2 -m 1000 -t 5
 ## Create Movie
 ffmpeg -framerate 10 -i mandel%02d.jpg mandel_movie.mp4

## Graph Analysis
After 10 processes the change in time to complete the generation
of frames drops off dramatically.

## Lab 13 Questions and Analysis
Threads were added to compute_image to parallelize computation of the Mandelbrot image.
The image is divided into horizontal sections and each thread is assigned
to compute one section independently.

pthread_create was used to split the image computation into smaller tasks handled by threads

pthread_join ensures that all threads complete their assigned work before the program continues to save the image.

Processes had a more significant impact on reducing runtime compared to threads.
This is evident from the data, where moving from 1 process to 2,5, or more processes showed dramatic improvements in runtime.
Processes run independently with separate memory spaces, allowing for true parallel execution and use multiple CPU cores with no interference.
Threads provided improvements, but the gains diminished as the number increased.