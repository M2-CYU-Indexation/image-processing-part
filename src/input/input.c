#include "input.h"

int retrieve_input(int argc, char* argv, Input* input)
{
    if (argc < 3)
    {
        // Unsufficient number of arguments
        return 1;
    }

    input->input_path = argv[1];
    input->output_path = argv[2];

    return 0;
}