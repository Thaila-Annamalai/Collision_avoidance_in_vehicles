# Collision_avoidance_in_vehicles
The arduino code under the name RoverB is the code for the rover representing the vehicle in front of the vehicle that is trying to overtake or pass.
The arduino code under the name RoverC is the code for the rover representing the vehicle that is trying to overtake.

OBJECTIVE:
The project objective is to develop a collision avoidance system using vehicle to vehicle communication. The proposed system will assist the driver while overtaking other vehicles and avoids any collision that might happen because of either
speeding or vehicles passing in the blind side. This system is designed for both single and multi-lane roads. The system also monitors whether the vehicle is travelling within the lane so that it prevents the vehicle in moving into the other lane.

WORKING:
The working of the arduino program for a two lane road is explained below:
The rover A approaches in the opposite lane
The rover B moves forward in the right lane.
The rover C moves behind the B rover.

When there is enough distance before the rover B, the rover C initiates the task of overtaking and moves
into the other lane on the left side. Here there are two possible conditions to occur:
(i) When it moves to the other lane it detects the distance between itself and the rover A in the opposite lane. If this distance is more than 30cm then the rover C moves forward and then moves into the right lane before the rover B. That is, it completes the
task of overtaking.
(ii) When it moves into the left lane and the distance between itself and the rover A is less than 80cms then the rover C reduces its speed and allows the rover B to proceed forward and then moves into the right lane and merger into the traffic behind the rover B.
When the distance before the rover B is not sufficient for the rover C to overtake and proceed then it reduces the speed and follows the rover B.

For a multi Lane road:
The rover A proceeds in the rightmost lane.
The rover B proceeds behind the rover A.
The rover C moves behind the rover C

The rover C travelling behind the rover B receives the distance between the rover B and C from the ultrasonic sensor installed in it.
The rover A calculates the distance of the vehicles in the vicinity that is the distance between the rover A and B is also calculated and sent to rover C. 
Based on this information the rover C takes a decision of overtaking or not. If there is sufficient space for rover C to overtake A and pass in to the leftmost lane without colliding with the rover B then the overtaking task is initiated and the
rover C moves into the next lane.
Therefore Lane changing is done safely. While passing if the rover B unexpectedly decelerates or rover A accelerates the rover C that is
continuously monitoring the distance between the rover A and B will reduce its speed and remains in the same lane.

The detailed explanation of this prototype is included in the collision_avoidance_in_vehicles.pdf
