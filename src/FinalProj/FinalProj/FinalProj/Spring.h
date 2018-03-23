#include <Physics1.h>

class Spring                                    // An Object To Represent A Spring With Inner Friction Binding Two Masses. The Spring
{                                       // Has A Normal Length (The Length That The Spring Does Not Exert Any Force)
public:
	Mass * mass1;                                // The First Mass At One Tip Of The Spring
	Mass* mass2;                                // The Second Mass At The Other Tip Of The Spring

	float springConstant;                           // A Constant To Represent The Stiffness Of The Spring
	float springLength;                         // The Length That The spring Does Not Exert Any Force
	float frictionConstant;                         // A Constant To be Used For The Inner Friction Of The Spring

	Spring(Mass* mass1, Mass* mass2,
		// Constructor
		float springConstant, float springLength, float frictionConstant)
	{
		this->springConstant = springConstant;               // Set The springConstant
		this->springLength = springLength;               // Set The springLength
		this->frictionConstant = frictionConstant;           // Set The frictionConstant

		this->mass1 = mass1;                     // Set mass1
		this->mass2 = mass2;                     // Set mass2
	}

	void solve()                                // solve() Method: The Method Where Forces Can Be Applied
	{
		Vector3D springVector = mass1->pos - mass2->pos;      // Vector Between The Two Masses

		float r = springVector.length();                // Distance Between The Two Masses

		Vector3D force;                         // Force Initially Has A Zero Value

		if (r != 0)                         // To Avoid A Division By Zero... Check If r Is Zero
											// The Spring Force Is Added To The Force      
			force += -(springVector / r) * (r - springLength) * springConstant;

			force += -(mass1->vel - mass2->vel) * frictionConstant;       // The Friction Force Is Added To The force
																		  // With This Addition We Obtain The Net Force Of The Spring
		mass1->applyForce(force);                    // Force Is Applied To mass1
		mass2->applyForce(-force);                   // The Opposite Of Force Is Applied To mass2
	}                                   // Void Solve() Ends Here
}