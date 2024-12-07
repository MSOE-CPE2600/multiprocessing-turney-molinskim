#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

//function prototypes
void parse_arguments(int argc, char *argv[], int *num_processes, int *num_frames, double *x_center, double *y_center, double *initial_scale, int *max_iterations, int *num_threads);
void generate_frame(int fram_num, double x_center, double y_center, double scale, int max_iterations, const char *output_file, int num_threads);
void manage_processes(int num_processes, int num_frames, double x_center, double y_center, double initial_scale, int max_iterations, int num_threads);

int main(int argc, char *argv[]) {
    //default parameters
    int num_processes = 1;          
    int num_frames = 50;
    double x_center = -0.5;
    double y_center = 0;
    double initial_scale = 2.0;
    int max_iterations = 1000;
    int num_threads = 1;

    parse_arguments(argc, argv, &num_processes, &num_frames, &x_center, &y_center, &initial_scale, &max_iterations, &num_threads);

    manage_processes(num_processes, num_frames, x_center, y_center, initial_scale, max_iterations, num_threads);

    printf("All frames generated successfully.\n");
    return 0;
}

void parse_arguments(int argc, char *argv[], int *num_processes, int *num_frames, double *x_center, double *y_center, double *initial_scale, int *max_iterations, int *num_threads) {
    int opt;
    while((opt = getopt(argc, argv, "p:f:x:y:s:m:t:")) != -1) {
        switch (opt) {
            case 'p': //# of processes
                *num_processes = atoi(optarg);
                break;
            case 'f': // # of frames
                *num_frames = atoi(optarg);
                break;
            case 'x': // X center coord
                *x_center = atof(optarg);
                break;
            case 'y': // Y center coord
                *y_center = atof(optarg);
                break;
            case 's': // initial scale
                *initial_scale = atof(optarg);
                break;
            case 'm': //max iterations
                *max_iterations = atoi(optarg);
                break;
            case 't': //# of threads
                *num_threads = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s -p <num_processes> -f <num_frames>\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
}

//function to generate a single frame
void generate_frame(int frame_num, double x_center, double y_center, double scale, int max_iterations, const char *output_file, int num_threads) {
    //construct mandel command
    char command[256];
    snprintf(command, sizeof(command),
        "./mandel -x %.61f -y %.61f -s %.61f -m %d -o %s -t %d",
        x_center, y_center, scale, max_iterations, output_file, num_threads);

    system(command);
}

//function to manage processes and generate frames
void manage_processes(int num_processes, int num_frames, double x_center, double y_center, double initial_scale, int max_iterations, int num_threads) {
    int active_processes = 0; //active child processes
    double scale = initial_scale; 

    for (int frame = 0; frame < num_frames; frame++) {
        //wait for processes
        if (active_processes >= num_processes) {
            wait(NULL); //wait for child to finish
            active_processes--;
        }

        //fork new process
        pid_t pid = fork();
        if (pid == 0) { //child process
            char output_file[20];
            snprintf(output_file, sizeof(output_file), "mandel%02d.jpg", frame);
            //adjust scale for zoom
            double current_scale = scale / (1 + 0.05*frame);
            //generate frame
            generate_frame(frame, x_center, y_center, current_scale, max_iterations, output_file, num_threads);
            exit(0);//child process exits after generating
        } else if (pid > 0) { // parent process
            active_processes++;
        } else { //fork failed
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }
    //wait for remainign processes to finish
    while (active_processes > 0) {
        wait(NULL);
        active_processes--;
    }
}