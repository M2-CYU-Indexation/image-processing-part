
/**
 * The struct represents what the user send to the application
 */
typedef struct input_struct
{
    char* input_path;
    char* output_path;
} Input;


/**
 * Fill the information of the input from the CLI.
 * This returns a 0 on success, any other number on failure.
 */
int retrieveInput(int argc, char* argv[], Input* input);
