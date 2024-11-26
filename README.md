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
./mandelmovie -p <num_processes> -f <num_frames> -x <x_center> -y <y_center> -s <initial_scale> -m <max_iterations>
ex: ./mandelmovie -p 4 -f 50 -x -0.5 -y 0 -s 2 -m 1000
 ## Create Movie
 ffmpeg -framerate 10 -i mandel%02d.jpg mandel_movie.mp4

## Graph Analysis
After 10 processes the change in time to complete the generation
of frames drops off dramatically.