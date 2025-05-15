#include "body.h"
#include "movement/basic_movement.h"
#include "movement/sequential_movement.h"
#include "movement/parallel_movement.h"


class Animate {
public:
    static Parallel_movement& step_forward(Body& body);
private:
    static std::unique_ptr<Parallel_movement> _step_forward;
};
