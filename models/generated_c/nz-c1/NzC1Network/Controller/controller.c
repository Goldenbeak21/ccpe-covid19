#include "controller.h"

// Controller Initialisation function
void ControllerInit(Controller* me) {
    // Initialise State
    me->state = CONTROLLER_PRE_L_D;

    // Initialise Outputs
    me->r0 = 0;
    me->level = 0;

    // Initialise Internal Variables
    me->t = 0;
}

// Controller Execution function
void ControllerRun(Controller* me) {
    // Create intermediary variables
    enum ControllerStates state_u = me->state;
    double r0_u = me->r0;
    double level_u = me->level;

    double t_u = me->t;


    // Run the state machine for transition logic
    // This will only be inter-location transitions, with intra-location transitions happening later
    switch(me->state) {
        case CONTROLLER_PRE_L_D: // Logic for state PreLD
            if(me->t >= 6) {
                t_u = 0;

                // Next state is LD
                state_u = CONTROLLER_LD;
            }
            break;
        case CONTROLLER_LD: // Logic for state LD
            break;
    }

    // Update from intermediary variables
    me->state = state_u;
    me->r0 = r0_u;
    me->level = level_u;

    me->t = t_u;


    // Intra-location logic for every state
    switch(me->state) {
        case CONTROLLER_PRE_L_D: // Intra-location logic for state PreLD
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 2.5;
            level_u = 0;

            if(t_u < 6 && me->t > 6) {
                // Need to saturate t to 6
                t_u = 6;
            }

            break;
        case CONTROLLER_LD: // Intra-location logic for state LD
            t_u = me->t + 1 * STEP_SIZE;

            r0_u = 0.316;
            level_u = 4;

            break;
    }

    // Update from intermediary variables
    me->r0 = r0_u;
    me->level = level_u;

    me->t = t_u;

}